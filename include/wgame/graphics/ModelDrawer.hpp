/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MODEL_DRAWER_H__
#define __MODEL_DRAWER_H__

#include "../opengl/Shader.hpp"
#include "../model/ModelGLTF.hpp"
#include "../geometry/Geometry.hpp"

#define MODEL_DRAWER_VERTEX_SHADER_PATH "shaders/modelDrawer.vert"
#define MODEL_DRAWER_FRAGMENT_SHADER_PATH "shaders/modelDrawer.frag"


namespace wgame {

class ModelDrawer {
public:
    void draw(ModelGLTF & model) const;
protected:
    class ModelDrawerShader : public Shader {
    public:
        ModelDrawerShader(); 
    };
private:
    ModelDrawerShader _shader;
};

}

#endif
