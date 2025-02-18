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
    Matrix4D modelMatrix(1.0f);
    float scale = model.getScaleFactor();
    modelMatrix = glm::scale(modelMatrix, Vector3D(scale, scale, scale));
    for (ModelMesh * mesh: model.getMeshes()) {
        _shader.setUniform("textureDiffuse", 0);
        _shader.setUniform("model", modelMatrix);
        _shader.setUniform("matNode", Matrix4D(1.0f));
        mesh -> draw();
    }
    _shader.unbind();
}

ModelDrawer::ModelDrawerShader::ModelDrawerShader() : 
Shader(MODEL_DRAWER_VERTEX_SHADER_PATH, MODEL_DRAWER_FRAGMENT_SHADER_PATH) {}

}
