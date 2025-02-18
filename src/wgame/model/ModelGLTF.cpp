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
    
    process(model);
}

ModelGLTF::~ModelGLTF() {
    for (ModelMesh * mesh : _meshes) {
        delete mesh;
    }
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

        ElementArrayBufferInfo elementsInfo;
        elementsInfo.drawMode = primitive.mode;
        elementsInfo.countElement = (GLsizei) indexAccessor.count;
        elementsInfo.componentType = indexAccessor.componentType;
        elementsInfo.offsetElement = (char *)NULL + indexAccessor.byteOffset;

        ModelMesh * modelMesh = new ModelMesh(elementsInfo, matrix);
        modelMesh -> bind();        
        for (auto & attrib : primitive.attributes) {
            const tinygltf::Accessor accessor = model.accessors[attrib.second];
            const tinygltf::BufferView & bufferView = model.bufferViews[accessor.bufferView];
            const tinygltf::Buffer & buffer = model.buffers[bufferView.buffer];
            int byteStride = accessor.ByteStride(bufferView);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int attribute = -1;
            if (attrib.first.compare("POSITION") == 0) {
                attribute = VBO_POSITION;
            }
            if (attribute >= 0) {
                modelMesh -> setVBO(
                    (GLsizei) bufferView.byteLength,
                    &buffer.data.at(0) + bufferView.byteOffset,
                    attribute, size, accessor.componentType,
                    accessor.normalized ? GL_TRUE : GL_FALSE,
                    byteStride, (char *)NULL + accessor.byteOffset
                );
            }
        }        
        const tinygltf::BufferView & bufferView = model.bufferViews[indexAccessor.bufferView];
        const tinygltf::Buffer & buffer = model.buffers[bufferView.buffer];
        
        modelMesh -> setEBO(
            (GLsizei) bufferView.byteLength, 
            &buffer.data.at(0) + bufferView.byteOffset
        );
        modelMesh -> unbind();        
        _meshes.push_back(modelMesh);
    }    
}

void ModelGLTF::draw() {
    _shader.bind();
    Matrix4D model(1.0f);
    model = glm::scale(model, Vector3D(_scale, _scale, _scale));
    for (ModelMesh * mesh: _meshes) {
        _shader.setUniform("model", model);
        _shader.setUniform("matNode", mesh -> getTransformation());
        mesh -> draw();
    }
    _shader.unbind();
}

ModelGLTF::ShaderModel::ShaderModel() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

}
