/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_DRAWER_H__
#define __WG_DRAWER_H__


#include "../opengl/Shader.hpp"
#include "../opengl/ShaderStorageBufferObject.hpp"
#include "../geometry/Geometry.hpp"

#include <memory>
#include <map>

#define BINDING_POINT_TRANSFORMS 5


namespace wgame {

class Drawer {
public:
    enum Mode {
        BACKGROUND,
        WORLD,
        HUD
    };
public:
    void setActiveLight(bool activeLight);
    void configureInstances(const std::vector<Matrix4D> & transforms, int id);
protected:
    std::map<int, std::unique_ptr<ShaderStorageBufferObject>> instances;
	std::map<int, size_t> numberOfInstances;
    bool activeLight = true;
};
        
#endif

}

