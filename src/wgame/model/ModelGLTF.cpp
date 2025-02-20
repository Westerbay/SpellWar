/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/ModelGLTF.hpp>

#include <stdexcept>
#include <iostream>


namespace wgame {

static std::string getFilePathExtension(const std::string & fileName) {
    if (fileName.find_last_of(".") != std::string::npos)
        return fileName.substr(fileName.find_last_of(".") + 1);
    return "";
}

ModelGLTF::ModelGLTF(const std::string & filename, float scale) : _scale(scale) {
    tinygltf::TinyGLTF loader;    
    tinygltf::Model model;
    std::string err, warn;

    bool ret;
    if (getFilePathExtension(filename) == GLTF_EXT) {
        ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    } else if (getFilePathExtension(filename) == GLB_EXT) {
        ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
    } else {
        std::cerr << "Wrong file format !" << err << std::endl;
        throw std::runtime_error("Wrong file format !");
    }

    if (!warn.empty()) {
        std::cout << "Warning: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "Error: " << err << std::endl;
        throw std::runtime_error("Cannot open model !");
    }
    if (!ret) {
        std::cerr << "Can't open model: " << filename << std::endl;
        throw std::runtime_error("Cannot open model !");
    }

    processSkeleton(model);
    processAnimation(model);

    _modelMesh.bind();
    process(model);
    _modelMesh.unbind();
    
    
    
    _ubo = new UniformBufferObject(_skeleton.jointMatricesByteLength, 2);
    _skeleton.update();
    Animation & a = _animations.front();
    a.setLoop(true);
}

void ModelGLTF::draw(const Shader & shader) {
    Animation & a = _animations.front();
    a.update(_skeleton);  

    _ubo -> bind();
    _ubo -> setData(_skeleton.jointMatrices.data(), _skeleton.jointMatricesByteLength);
    shader.bind();
    Matrix4D modelMatrix(1.0f);
    modelMatrix = glm::scale(modelMatrix, Vector3D(_scale, _scale, _scale));
    shader.setUniform("textureDiffuse", 0);
    shader.setUniform("model", modelMatrix);
    _modelMesh.draw(shader);
    shader.unbind();
    _ubo -> unbind();
}   

int ModelGLTF::getVBOIndex(const std::string & key) const {
    if (key.compare(POSITION) == 0) {
        return VBO_VERTEX;
    }
    if (key.compare(NORMAL) == 0) {
        return VBO_NORMAL;
    }
    if (key.compare(TEXCOORD_0) == 0) {
        return VBO_TEXCOORD_0;
    }
    if (key.compare(JOINTS) == 0) {
        return VBO_JOINTS;
    }
    if (key.compare(WEIGHTS) == 0) {
        return VBO_WEIGHTS;
    }
    return -1;
}

void ModelGLTF::process(const tinygltf::Model & model) {
    const tinygltf::Scene & scene = model.scenes[model.defaultScene];
    for (int i = 0; i < scene.nodes.size(); ++ i) {
        if (scene.nodes[i] >= 0 && scene.nodes[i] < model.nodes.size()) {
            processNodes(model, model.nodes[scene.nodes[i]]);
        }
    }
}

Matrix4D ModelGLTF::getNodeTransform(const tinygltf::Node & node) {
    Matrix4D transform(1.0f); 
    if (!node.matrix.empty()) {
        transform = glm::make_mat4(node.matrix.data());
    } else {
        Vector3D translation;
        if (node.translation.size() == 3) {
            translation.x = (float) node.translation[0];
            translation.y = (float) node.translation[1];
            translation.z = (float) node.translation[2];
        } else {
            translation = Vector3D(0.0f);
        }
        Vector3D scale;
        if (node.scale.size() == 3) {
            scale.x = (float) node.scale[0];
            scale.y = (float) node.scale[1];
            scale.z = (float) node.scale[2];
        } else {
            scale = Vector3D(1.0f);
        }
        Quaternion rotation;
        if (node.rotation.size() == 4) {
            rotation.w = (float) node.rotation[3]; 
            rotation.x = (float) node.rotation[0]; 
            rotation.y = (float) node.rotation[1];
            rotation.z = (float) node.rotation[2];
        } else {
            rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
        }
        transform = glm::translate(Matrix4D(1.0f), translation) * glm::mat4_cast(rotation) * glm::scale(Matrix4D(1.0f), scale);
    }
    return transform;
}

void ModelGLTF::processNodes(
    const tinygltf::Model & model,
    const tinygltf::Node & node, Matrix4D matrix
) {
    glm::mat4 nodeTransform = matrix * getNodeTransform(node);
    if (node.mesh >= 0 && node.mesh < model.meshes.size()) {
        processMesh(model, model.meshes[node.mesh], nodeTransform);
    }
    for (int i = 0; i < node.children.size(); ++ i) {
        if (node.children[i] >= 0 && node.children[i] < model.nodes.size()) {
            processNodes(model, model.nodes[node.children[i]], nodeTransform);
        }
    }
}

void ModelGLTF::processMesh(
    const tinygltf::Model & model,
    const tinygltf::Mesh & mesh, Matrix4D matrix
) {
    for (size_t i = 0; i < mesh.primitives.size(); ++ i) {
        const tinygltf::Primitive primitive = mesh.primitives[i];
        const tinygltf::Accessor & indexAccessor = model.accessors[primitive.indices];    
        
        std::vector<VertexBufferInfo> vboInfo;
        for (auto & attrib : primitive.attributes) {
            
            const tinygltf::Accessor accessor = model.accessors[attrib.second];
            const tinygltf::BufferView & bufferView = model.bufferViews[accessor.bufferView];
            const tinygltf::Buffer & buffer = model.buffers[bufferView.buffer];
            int byteStride = accessor.ByteStride(bufferView);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int vboIndex = getVBOIndex(attrib.first);            
            if (vboIndex >= 0) {   
                _modelMesh.setVBO(
                    accessor.bufferView, 
                    (GLsizei) bufferView.byteLength,
                    buffer.data.data() + bufferView.byteOffset
                );
                VertexBufferInfo vboData = {
                    accessor.bufferView,
                    (GLuint) vboIndex,
                    (GLuint) size,
                    (GLenum) accessor.componentType,
                    accessor.normalized ? GL_TRUE : GL_FALSE,
                    byteStride,
                    (char *)NULL + accessor.byteOffset
                };
                vboInfo.push_back(vboData);
            }
        }        

        const tinygltf::BufferView & bufferView = model.bufferViews[indexAccessor.bufferView];
        const tinygltf::Buffer & buffer = model.buffers[bufferView.buffer];
        
        _modelMesh.setEBO(
            indexAccessor.bufferView,
            (GLsizei) bufferView.byteLength,
            buffer.data.data() + bufferView.byteOffset
        );
        ElementBufferInfo elementsInfo = {
            indexAccessor.bufferView,
            (GLsizei) indexAccessor.count,
            (GLenum) primitive.mode,
            (GLenum) indexAccessor.componentType,
            (char *)NULL + indexAccessor.byteOffset
        };

        int textureID = -1;
        if (primitive.material >= 0) {
            const tinygltf::Material & mat = model.materials[primitive.material];
            int textureIndex = mat.pbrMetallicRoughness.baseColorTexture.index;
            if (textureIndex < 0) {
                textureIndex = mat.emissiveTexture.index;
            }
            if (textureIndex >= 0) {
                const tinygltf::Texture & texture = model.textures[textureIndex];
                int imageIndex = texture.source;
                if (textureIndex >= 0) {
                    const tinygltf::Image & image = model.images[imageIndex];
                    _modelMesh.setTexture0(
                        imageIndex, image.width, image.height, 
                        image.component, image.image.data()
                    );
                    textureID = imageIndex;
                }
            }                
        } 
        ModelSubMeshInfo subMesh = {
            matrix,
            textureID,
            elementsInfo,
            vboInfo
        };
        _modelMesh.addSubMesh(subMesh);
    }    
}

void ModelGLTF::processSkeleton(const tinygltf::Model & model) {
    if (model.skins.size() == 0) {
        return;
    }
    if (model.skins.size() > 1) {
        std::cerr << "Model have more than 1 skin!" << std::endl;
        throw std::runtime_error("Cannot load model animations!");
    }
    
    const tinygltf::Skin & skin = model.skins[0];
    if (skin.inverseBindMatrices < 0) {
        return;
    }

    size_t size = skin.joints.size();
    _skeleton.joints.resize(size);
    _skeleton.jointMatrices.resize(size);
    _skeleton.jointMatricesByteLength = size * sizeof(Matrix4D);
    
    const Matrix4D * inverseBindMatrices;
    {
        loadAccessor<Matrix4D>(
            model,
            model.accessors[skin.inverseBindMatrices],
            inverseBindMatrices
        );
    }

    for (int i = 0; i < size; i ++) {
        Joint & joint = _skeleton.joints[i];
        joint.nodeIndex = skin.joints[i];
        joint.inverseBindMatrix = inverseBindMatrices[i];

        const tinygltf::Node & node = model.nodes[joint.nodeIndex];
        if (node.translation.size() == 3) {
            joint.translation = glm::make_vec3(node.translation.data());
        }
        else {
            joint.translation = Vector3D(0.0f);
        }
        if (node.rotation.size() == 4) {
            joint.rotation = glm::make_quat(node.rotation.data());
        }
        else {
            joint.rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
        }
        if (node.scale.size() == 3) {
            joint.scale = glm::make_vec3(node.scale.data());
        }
        else {
            joint.scale = Vector3D(1.0f);
        }
        if (node.matrix.size() == 16) {
            joint.undeformedMatrix = glm::make_mat4x4(node.matrix.data());
        }
        else {
            joint.undeformedMatrix = Matrix4D(1.0f);
        }
        _skeleton.nodeToJoint[joint.nodeIndex] = i;
    }
   
    processJoint(model, ROOT_JOINT, NO_PARENT);
}

void ModelGLTF::processJoint(const tinygltf::Model & model, int joint, int parent) {
    _skeleton.joints[joint].parent = parent;
    const auto & nodes = model.nodes[_skeleton.joints[joint].nodeIndex];
    for (int i = 0; i < nodes.children.size(); i ++) {
        if (nodes.children[i] >= 0 && nodes.children[i] < model.nodes.size()) {
            int child = _skeleton.nodeToJoint[nodes.children[i]];
            _skeleton.joints[joint].children.push_back(child);
            processJoint(model, child, joint);
        }
    }
}

void ModelGLTF::processAnimation(const tinygltf::Model & model) {
    for (const auto & animModel : model.animations) {

        std::vector<Animation::Sampler> samplers(animModel.samplers.size());

        for (int i = 0; i < animModel.samplers.size(); i ++) {
            const tinygltf::AnimationSampler & samplerModel = animModel.samplers[i];
            Animation::Sampler & sampler = samplers[i];
            sampler.interpolation = Animation::LINEAR;
            if (samplerModel.interpolation == "STEP") {
                sampler.interpolation = Animation::STEP;
            }
            else if (samplerModel.interpolation == "CUBICSPLINE") {
                sampler.interpolation = Animation::CUBICSPLINE;
            }

            {
                const float * timeStepBuffer;
                const tinygltf::Accessor & accessor = model.accessors[samplerModel.input];
                loadAccessor<float>(model, accessor, timeStepBuffer);
                sampler.elapsedTimes.resize(accessor.count);
                for (int i = 0; i < accessor.count; i ++) {
                    sampler.elapsedTimes[i] = timeStepBuffer[i];
                }
            }   
            
            {
                const tinygltf::Accessor & accessor = model.accessors[samplerModel.output];
                sampler.pathValues.resize(accessor.count);
                if (accessor.type == TINYGLTF_TYPE_VEC3) {
                    const Vector3D * buffer;
                    loadAccessor<Vector3D>(model, accessor, buffer);
                    for (int i = 0; i < accessor.count; i ++) {
                        sampler.pathValues[i] = Vector4D(buffer[i], 0.0f);
                    }
                } else if (accessor.type == TINYGLTF_TYPE_VEC4) {
                    const Vector4D * buffer;
                    loadAccessor<Vector4D>(model, accessor, buffer);
                    for (int i = 0; i < accessor.count; i ++) {
                        sampler.pathValues[i] = Vector4D(buffer[i]);
                    }
                }
            } //END outputs            
        }

        size_t numChannels = animModel.channels.size();
        std::vector<Animation::Channel> channels(numChannels);
        for (int i = 0; i < numChannels; i ++) {
            const tinygltf::AnimationChannel channelModel = animModel.channels[i];
            Animation::Channel & channel = channels[i];
            channel.samplerIndex = channelModel.sampler;
            channel.nodeTarget = channelModel.target_node;
            if (channelModel.target_path == "translation") {
                channel.path = Animation::TRANSLATION;
            } 
            else if (channelModel.target_path == "rotation") {
                channel.path = Animation::ROTATION;
            }
            else if (channelModel.target_path == "scale") {
                channel.path = Animation::SCALE;
            }
        }

        _animations.push_back(Animation(samplers, channels));
        _animationsName[animModel.name] = _animations.size() - 1;

    }
}

}
