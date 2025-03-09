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
    if (key.compare(TANGENT) == 0) {
        return VBO_TANGENTS;
    }
    return -1;
}

ModelGLTF::ModelGLTF() {
    _transform = Matrix4D(1.0f);
}

void ModelGLTF::setTransform(const Matrix4D & transform) {
    _transform = transform;
}

void ModelGLTF::drawModelMesh(const Shader & shader) {
    shader.setUniform("textureDiffuse", UNIT_TEXTURE_DIFFUSE);
    shader.setUniform("textureMetallicRoughness", UNIT_TEXTURE_PBR);   
    shader.setUniform("textureNormal", UNIT_TEXTURE_NORMAL);   
    _modelMesh.draw(shader, _transform);
}  

void ModelGLTF::drawModelMeshInstanced(const Shader & shader, size_t numberOfInstance) {
    shader.setUniform("textureDiffuse", UNIT_TEXTURE_DIFFUSE);
    shader.setUniform("textureMetallicRoughness", UNIT_TEXTURE_PBR);  
    shader.setUniform("textureNormal", UNIT_TEXTURE_NORMAL); 
    _modelMesh.draw(shader, numberOfInstance);
}  

Matrix4D ModelGLTF::getTransformNode(const tinygltf::Node & node) const {
    
    Vector3D translation(0.0f);
    Quaternion rotation(1.0f, 0.0f, 0.0f, 0.0f);
    Vector3D scale(1.0f);
    Matrix4D undeformedMatrix(1.0f);

    if (node.translation.size() == 3) {
        translation = glm::make_vec3(node.translation.data());
    }
    if (node.rotation.size() == 4) {
        rotation = glm::make_quat(node.rotation.data());
    }
    if (node.scale.size() == 3) {
        scale = glm::make_vec3(node.scale.data());
    }
    if (node.matrix.size() == 16) {
        undeformedMatrix = glm::make_mat4x4(node.matrix.data());
    }

    return glm::translate(Matrix4D(1.0f), translation) *
           glm::mat4(rotation) * 
           glm::scale(Matrix4D(1.0f), scale) *
           undeformedMatrix;
}

void ModelGLTF::process(const tinygltf::Model & model) {
    _modelMesh.bind();
    const tinygltf::Scene & scene = model.scenes[model.defaultScene];
    for (size_t i = 0; i < scene.nodes.size(); ++ i) {
        if (scene.nodes[i] >= 0) {
            processNodes(model, model.nodes[scene.nodes[i]], Matrix4D(1.0f));
        }
    }
    _modelMesh.unbind();  
} 

void ModelGLTF::processNodes(
    const tinygltf::Model & model,
    const tinygltf::Node & node,
    Matrix4D transformParent
) {
    Matrix4D transform = transformParent * getTransformNode(node); 
    if (node.mesh >= 0) {
        processMesh(model, model.meshes[node.mesh], transform);
    }
    for (size_t i = 0; i < node.children.size(); ++ i) {
        if (node.children[i] >= 0) {
            processNodes(model, model.nodes[node.children[i]], transform);
        }
    }
}

void ModelGLTF::processMesh(
    const tinygltf::Model & model,
    const tinygltf::Mesh & mesh, Matrix4D transform
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
            (char *) NULL + indexAccessor.byteOffset
        };

        int textureID = -1;
        int metallicRoughnessID = -1;
        int normalMapID = -1;

        Vector4D baseColorFactor = Vector4D(1.0f);
        float metallicFactor = 0.0f;
        float roughnessFactor = 0.0f;

        if (primitive.material >= 0) {
            const tinygltf::Material & mat = model.materials[primitive.material];            
            int textureIndex = mat.pbrMetallicRoughness.baseColorTexture.index;
            if (textureIndex < 0) {
                textureIndex = mat.emissiveTexture.index;
            }
            if (textureIndex >= 0) {
                textureID = processTexture(model, textureIndex);
            } 
            int metallicRoughnessIndex = mat.pbrMetallicRoughness.metallicRoughnessTexture.index;
            if (metallicRoughnessIndex >= 0) {
                metallicRoughnessID = processTexture(model, metallicRoughnessIndex);
                baseColorFactor = Vector4D(
                    mat.pbrMetallicRoughness.baseColorFactor[0],
                    mat.pbrMetallicRoughness.baseColorFactor[1],
                    mat.pbrMetallicRoughness.baseColorFactor[2],
                    mat.pbrMetallicRoughness.baseColorFactor[3]
                );
                metallicFactor = (float) mat.pbrMetallicRoughness.metallicFactor;
                roughnessFactor = (float) mat.pbrMetallicRoughness.roughnessFactor;
            }             
            int normalIndex = mat.normalTexture.index;
            if (normalIndex >= 0) {
                normalMapID = processTexture(model, normalIndex);
            } 
            
        } 
        ModelSubMeshInfo subMesh = {
            textureID,
            normalMapID,
            metallicRoughnessID,
            baseColorFactor,
            metallicFactor,
            roughnessFactor,
            transform,
            elementsInfo,
            vboInfo
        };
        _modelMesh.addSubMesh(subMesh);
    }    
}

int ModelGLTF::processTexture(const tinygltf::Model & model, int textureIndex) {
    const tinygltf::Texture & texture = model.textures[textureIndex];
    const tinygltf::Sampler & sampler = model.samplers[texture.sampler];
    int imageIndex = texture.source;
    if (imageIndex >= 0) {
        const tinygltf::Image & image = model.images[imageIndex];
        _modelMesh.setTexture(
            imageIndex, image.width, image.height, 
            image.component, image.image.data(),
            sampler.minFilter, sampler.magFilter, 
            sampler.wrapS, sampler.wrapT, image.pixel_type
        );
        return imageIndex;
    }
    return -1;
}

}
