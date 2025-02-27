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

int ModelGLTF::getVBOIndex(const std::string & key) {
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

ModelGLTF::ModelGLTF() {
    _scale = 1.0f;
    _angleDeg = 0.0f;
    _axisRotation = AXIS_X;
    _translation = Vector3D(0.0f);
    _modelMatrix = Matrix4D(1.0f);
}

void ModelGLTF::setTranslation(const Vector3D & translation) {
    _translation = translation;
    updateModel();
}

void ModelGLTF::setScale(float scale) {
    _scale = scale;
    updateModel();
}

void ModelGLTF::setRotation(float angleDeg, const Vector3D & axisRotation) {
    _angleDeg = angleDeg;
    _axisRotation = axisRotation;
    updateModel();
}

void ModelGLTF::updateModel() {
    Matrix4D M(1.0f);
    _modelMatrix = glm::translate(M, _translation) *
                   glm::rotate(M, glm::radians(_angleDeg), _axisRotation) *
                   glm::scale(M, Vector3D(_scale));
}

void ModelGLTF::drawModelMesh(const Shader & shader) {
    shader.setUniform("textureDiffuse", 0);
    shader.setUniform("model", _modelMatrix);
    _modelMesh.draw();
}   



void ModelGLTF::process(const tinygltf::Model & model) {
    _modelMesh.bind();
    const tinygltf::Scene & scene = model.scenes[model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++ i) {
        if (scene.nodes[i] >= 0) {
            processNodes(model, model.nodes[scene.nodes[i]]);
        }
    }
    _modelMesh.unbind();  
} 

void ModelGLTF::processNodes(
    const tinygltf::Model & model,
    const tinygltf::Node & node
) {
    if (node.mesh >= 0) {
        processMesh(model, model.meshes[node.mesh]);
    }
    for (size_t i = 0; i < node.children.size(); ++ i) {
        if (node.children[i] >= 0) {
            processNodes(model, model.nodes[node.children[i]]);
        }
    }
}

void ModelGLTF::processMesh(
    const tinygltf::Model & model,
    const tinygltf::Mesh & mesh
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
                const tinygltf::Sampler & sampler = model.samplers[texture.sampler];
                int imageIndex = texture.source;
                if (imageIndex >= 0) {
                    const tinygltf::Image & image = model.images[imageIndex];
                    _modelMesh.setTexture0(
                        imageIndex, image.width, image.height, 
                        image.component, image.image.data(),
                        sampler.minFilter, sampler.magFilter, 
                        sampler.wrapS, sampler.wrapT, image.pixel_type
                    );
                    textureID = imageIndex;
                }
            }                
        } 
        ModelSubMeshInfo subMesh = {
            textureID,
            elementsInfo,
            vboInfo
        };
        _modelMesh.addSubMesh(subMesh);
    }    
}

}
