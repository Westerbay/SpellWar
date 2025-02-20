/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/graphics/ModelDrawer.hpp>


namespace wgame {

void ModelDrawer::draw(ModelGLTF & model) const {
    _shader.bind();
    model.draw(_shader);
    _shader.unbind();
}

ModelDrawer::ModelDrawerShader::ModelDrawerShader() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

}
