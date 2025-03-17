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

ModelDrawer::ModelDrawer() {
    _shader = _uniqueShader.lock();
    if (!_shader) {
        _shader = std::make_shared<ModelDrawerShader>();
        _uniqueShader = _shader;
    }    
}

void ModelDrawer::draw(ModelGLTF & model, Mode mode) const {
    _shader -> bind();
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", false);  
    model.draw(*_shader);
    _shader -> unbind();
}

void ModelDrawer::drawInstanced(ModelGLTF & model, int id, Mode mode) {
    if (instances.find(id) == instances.end()) {
        return;
    }
    _shader -> bind();
    instances[id] -> setBindingPoint(BINDING_POINT_TRANSFORMS);
    instances[id] -> bind();
    _shader -> setUniform("activeLight", activeLight);
    _shader -> setUniform("drawMode", (int) mode);
    _shader -> setUniform("drawInstanced", true);    
    model.drawInstanced(*_shader, numberOfInstances[id]);
    instances[id] -> unbind();
    _shader -> unbind();
}

ModelDrawer::ModelDrawerShader::ModelDrawerShader() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

}
