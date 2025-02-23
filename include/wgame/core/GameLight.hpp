/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_GAME_LIGHT_H__
#define __WG_GAME_LIGHT_H__

#include "../geometry/Geometry.hpp"
#include "../opengl/UniformBufferObject.hpp"

#define LIGHT_POINT 1


namespace wgame {

struct LightInfo {
    Point4D position; // w -> apply or not
    Vector4D lightColor; // w -> ambient
};

class GameLight {
public:
    GameLight();
    void setPosition(const Point3D & position);
    void setLightColor(const Vector3D & lightColor);
    void setDisplayLight(int displayLight);
    void setAmbientLightning(float ambient);
    void apply() const;
private:
    LightInfo _lightInfo;
    UniformBufferObject _ubo;
};

}

#endif
