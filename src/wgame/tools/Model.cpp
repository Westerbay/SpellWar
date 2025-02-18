/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/tools/Model.hpp>

#include <stdexcept>
#include <iostream>


namespace wgame {

Model::Model(const std::string & filename, float scale) : _scale(scale) {
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    bool ret = loader.LoadBinaryFromFile(&_model, &err, &warn, filename);
    //bool ret = loader.LoadASCIIFromFile(&_model, &err, &warn, filename);

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

    process();
    std::cout << "END" << std::endl;
}

Model::~Model() {
}

void Model::process() {
    /*for (int i = 0; i < _model.bufferViews.size(); ++ i) {
        const tinygltf::BufferView & bufferView = _model.bufferViews[i];
        if (bufferView.target == 0) {
            continue;
        }        
        const tinygltf::Buffer & buffer = _model.buffers[bufferView.buffer];

        GLuint bufferID;
        glGenBuffers(1, &bufferID);
        _buffers[i] = bufferID;
        glBindBuffer(bufferView.target, bufferID);
        glBufferData(
            bufferView.target, bufferView.byteLength, 
            &buffer.data.at(0) + bufferView.byteOffset, 
            GL_STATIC_DRAW
        );
        glBindBuffer(bufferView.target, 0);
    }*/

    const tinygltf::Scene & scene = _model.scenes[_model.defaultScene];
    for (int i = 0; i < scene.nodes.size(); ++ i) {
        if (scene.nodes[i] >= 0 && scene.nodes[i] < _model.nodes.size()) {
            processNodes(_model.nodes[scene.nodes[i]]);
        }
    }
}

Matrix4D Model::getNodeTransform(const tinygltf::Node & node) {
    Matrix4D transform(1.0f); 

    if (!node.matrix.empty()) {
        transform = glm::make_mat4(node.matrix.data());
    } else {
        Vector3D translation = node.translation.size() == 3 ? Vector3D(node.translation[0], node.translation[1], node.translation[2]) : Vector3D(0.0f);
        Vector3D scale = node.scale.size() == 3 ? Vector3D(node.scale[0], node.scale[1], node.scale[2]) : Vector3D(1.0f);
        Quaternion rotation = node.rotation.size() == 4 ? Quaternion(node.rotation[3], node.rotation[0], node.rotation[1], node.rotation[2]) : Quaternion(1.0f, 0.0f, 0.0f, 0.0f);

        transform = glm::translate(Matrix4D(1.0f), translation) * glm::mat4_cast(rotation) * glm::scale(Matrix4D(1.0f), scale);
    }

    return transform;
}

void Model::processNodes(const tinygltf::Node & node, Matrix4D matrix) {
    glm::mat4 nodeTransform = matrix * getNodeTransform(node);
    if (node.mesh >= 0 && node.mesh < _model.meshes.size()) {
        processMesh(_model.meshes[node.mesh], nodeTransform);
    }
    for (int i = 0; i < node.children.size(); ++ i) {
        if (node.children[i] >= 0 && node.children[i] < _model.nodes.size()) {
            processNodes(_model.nodes[node.children[i]], nodeTransform);
        }
    }
}

void Model::processMesh(const tinygltf::Mesh & mesh, Matrix4D matrix) {
    for (size_t i = 0; i < mesh.primitives.size(); ++ i) {
        Mesh meshStruct;
        meshStruct.nodeTransform = matrix;
        glGenVertexArrays(1, &meshStruct.vao);
        glBindVertexArray(meshStruct.vao);

        tinygltf::Primitive primitive = mesh.primitives[i];
        for (auto & attrib : primitive.attributes) {
            tinygltf::Accessor accessor = _model.accessors[attrib.second];
            tinygltf::BufferView & bufferView = _model.bufferViews[accessor.bufferView];
            tinygltf::Buffer & buffer = _model.buffers[bufferView.buffer];
            int byteStride = accessor.ByteStride(bufferView);

            int size = 1;
            if (accessor.type != TINYGLTF_TYPE_SCALAR) {
                size = accessor.type;
            }

            int attribute = -1;
            if (attrib.first.compare("POSITION") == 0) {
                attribute = VBO_VERTEX;
            }
            if (attribute >= 0) {
                glGenBuffers(1, &meshStruct.vbo);
                glBindBuffer(GL_ARRAY_BUFFER, meshStruct.vbo);
                glBufferData(GL_ARRAY_BUFFER, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
                glEnableVertexAttribArray(attribute);
                glVertexAttribPointer(
                    attribute, size, accessor.componentType,
                    accessor.normalized ? GL_TRUE : GL_FALSE,
                    byteStride, (char *)NULL + accessor.byteOffset
                );
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        }
        tinygltf::Accessor & accessor = _model.accessors[primitive.indices];
        tinygltf::BufferView & bufferView =  _model.bufferViews[accessor.bufferView];
        tinygltf::Buffer & buffer = _model.buffers[bufferView.buffer];
        
        glGenBuffers(1, &meshStruct.ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshStruct.ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        meshStruct.drawMode = primitive.mode;
        meshStruct.count = accessor.count;
        meshStruct.componentType = accessor.componentType;
        meshStruct.offset = (char *)NULL + accessor.byteOffset;
        _meshes.push_back(meshStruct);
    }    
}

void Model::draw() {
    _shader.bind();
    Matrix4D model(1.0f);
    model = glm::scale(model, Vector3D(_scale, _scale, _scale));
    for (const Mesh & mesh: _meshes) {
        _shader.setUniform("model", model);
        _shader.setUniform("matNode", Matrix4D(1.0f));
        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glDrawElements(mesh.drawMode, mesh.count, mesh.componentType, mesh.offset);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    _shader.unbind();
}

Model::ShaderModel::ShaderModel() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

}
