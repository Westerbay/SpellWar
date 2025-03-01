/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_MODEL_DRAWER_H__
#define __WG_MODEL_DRAWER_H__

#include "../opengl/Shader.hpp"
#include "../opengl/UniformBufferObject.hpp"
#include "../model/ModelGLTF.hpp"
#include "../geometry/Geometry.hpp"

#include <memory>

#define MODEL_DRAWER_VERTEX_SHADER_PATH "shaders/modelDrawer.vert"
#define MODEL_DRAWER_FRAGMENT_SHADER_PATH "shaders/modelDrawer.frag"

#define BINDING_POINT_TRANSFORMS_MODEL 5

namespace wgame {

class ModelDrawer {
public:
    ModelDrawer();
    void configureInstances(const std::vector<Matrix4D> & transforms);
    void draw(ModelGLTF & model) const;
    void drawInstanced(ModelGLTF & model) const;
public:
    class ModelDrawerShader : public Shader {
    public:
        ModelDrawerShader(); 
    };
private:
    static std::weak_ptr<ModelDrawerShader> _uniqueShader;
    std::shared_ptr<ModelDrawerShader> _shader;
    std::unique_ptr<UniformBufferObject> _instanced;
    size_t _numberOfInstances;
};

}

#endif
