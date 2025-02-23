/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameLight.hpp>


namespace wgame {

GameLight::GameLight() {
    _lightInfo = {
        Point4D(0.0f),
        Vector4D(1.0f),
    };
    _ubo.configure(sizeof(LightInfo));
    _ubo.setBindingPoint(LIGHT_POINT);
}

void GameLight::setPosition(const Point3D & position) {
    _lightInfo.position = Point4D(position, _lightInfo.position.w);
}

void GameLight::setLightColor(const Vector3D & lightColor) {
    _lightInfo.lightColor = Vector4D(lightColor, _lightInfo.lightColor.w);
}

void GameLight::setDisplayLight(int displayLight) {
    _lightInfo.position.w = displayLight;
}

void GameLight::setAmbientLightning(float ambient) {
    _lightInfo.lightColor.w = ambient;
}

void GameLight::apply() const {
    _ubo.setData(&_lightInfo, sizeof(LightInfo));
}

}
