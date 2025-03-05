/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/ModelDrawer.hpp>


namespace wgame {

std::weak_ptr<ModelDrawer::ModelDrawerShader> ModelDrawer::_uniqueShader;
std::weak_ptr<ModelDrawer::ModelStaticDrawerShader> ModelDrawer::_uniqueShaderStatic;

ModelDrawer::ModelDrawer() {
    _shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<ModelDrawerShader>();
        _uniqueShader = _shader;
    }
    
    _shaderStatic = _uniqueShaderStatic.lock();
    if (!_shaderStatic) {
        _shaderStatic = std::make_shared<ModelStaticDrawerShader>();
        _uniqueShaderStatic = _shaderStatic;
    }
    
    _instanced = nullptr;
    _numberOfInstances = 0;
}

void ModelDrawer::configureInstances(const std::vector<Matrix4D> & transforms) {
    if (!_instanced) {
        _instanced = std::make_unique<UniformBufferObject>();
        _instanced -> setBindingPoint(BINDING_POINT_TRANSFORMS_MODEL);
    }
    _instanced -> configure(transforms.size() * sizeof(Matrix4D));
    _instanced -> setData(transforms.data(), transforms.size() * sizeof(Matrix4D));
    _numberOfInstances = transforms.size();
}

void ModelDrawer::draw(ModelGLTF & model) const {
    _shader -> bind();
    _shader -> setUniform("drawInstanced", 0);
    model.draw(*_shader);
    _shader -> unbind();
}

void ModelDrawer::drawStatic(ModelGLTF & model) const {
    _shaderStatic -> bind();
    _shaderStatic -> setUniform("drawInstanced", 0);
    model.draw(*_shaderStatic);
    _shaderStatic -> unbind();
}

void ModelDrawer::drawInstanced(ModelGLTF & model) const {
    if (!_instanced) {
        return;
    }
    _shader -> bind();
    _instanced -> bind();
    _shader -> setUniform("drawInstanced", 1);
    model.drawInstanced(*_shader, _numberOfInstances);
    _instanced -> unbind();
    _shader -> unbind();
}

ModelDrawer::ModelDrawerShader::ModelDrawerShader() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

ModelDrawer::ModelStaticDrawerShader::ModelStaticDrawerShader() : 
Shader(MODEL_STATIC_DRAWER_VERTEX_SHADER_PATH, MODEL_STATIC_DRAWER_FRAGMENT_SHADER_PATH) {}

}
