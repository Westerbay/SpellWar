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
    Point4D cameraPosition; 
    Point4D position; 
    Vector4D color;
    bool display;
    float defaultAmbient;
    float defaultSpecularFactor; 
    int defaultSpecularExponent;
};

class GameLight {
public:
    GameLight();
    void setPosition(const Point3D & position);
    void setLightColor(const Vector3D & lightColor);
    void setDisplayLight(bool displayLight);
    void setDefaultAmbientLighting(float ambient);
    void setDefaultSpecularFactor(float specularFactor);
    void setDefaultSpecularExponent(int specularExponent);
    void apply(const Point3D & cameraPosition);
private:
    LightInfo _lightInfo;
    UniformBufferObject _ubo;
};

}

#endif
