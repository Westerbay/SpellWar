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
#include <map>

#define MODEL_DRAWER_VERTEX_SHADER_PATH "shaders/modelDrawer.vert"
#define MODEL_DRAWER_FRAGMENT_SHADER_PATH "shaders/modelDrawer.frag"

#define MODEL_STATIC_DRAWER_VERTEX_SHADER_PATH "shaders/modelStaticDrawer.vert"
#define MODEL_STATIC_DRAWER_FRAGMENT_SHADER_PATH "shaders/modelStaticDrawer.frag"

#define BINDING_POINT_TRANSFORMS_MODEL 5

namespace wgame {

class ModelDrawer {
public:
    ModelDrawer();
    void configureInstances(const std::vector<Matrix4D> & transforms, int id);
    void draw(ModelGLTF & model) const;
    void drawStatic(ModelGLTF & model) const;
    void drawInstanced(ModelGLTF & model, int id);
public:
    class ModelDrawerShader : public Shader {
    public:
        ModelDrawerShader(); 
    };
    class ModelStaticDrawerShader : public Shader {
    public:
        ModelStaticDrawerShader(); 
    };
private:
    static std::weak_ptr<ModelDrawerShader> _uniqueShader;
    static std::weak_ptr<ModelStaticDrawerShader> _uniqueShaderStatic;
    std::shared_ptr<ModelDrawerShader> _shader;
	std::shared_ptr<ModelStaticDrawerShader> _shaderStatic; 
	std::map<int, std::unique_ptr<UniformBufferObject>> _instances;
	std::map<int, size_t> _numberOfInstances;
};

}

#endif
