/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_MODEL_DRAWER_H__
#define __WG_MODEL_DRAWER_H__

#include "Drawer.hpp"
#include "../model/ModelGLTF.hpp"

#define MODEL_DRAWER_VERTEX_SHADER_PATH "shaders/modelDrawer.vert"
#define MODEL_DRAWER_FRAGMENT_SHADER_PATH "shaders/modelDrawer.frag"


namespace wgame {

class ModelDrawer : public Drawer {
public:
    ModelDrawer();
    void draw(ModelGLTF & model, Mode mode = WORLD) const;
    void draw(ModelGLTF * model, Mode mode = WORLD) const;
    void drawInstanced(ModelGLTF & model, int id, Mode mode = WORLD);
public:
    class ModelDrawerShader : public Shader {
    public:
        ModelDrawerShader(); 
    };
private:
    static std::weak_ptr<ModelDrawerShader> _uniqueShader;
    std::shared_ptr<ModelDrawerShader> _shader;
};

}

#endif
