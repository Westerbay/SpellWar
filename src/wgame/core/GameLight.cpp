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
        Point4D(0.0f, 0.0f, 0.0f, 1.0f),
        Vector4D(1.0f),
        0, 0.0f, 0.0f, 0
    };
    _ubo.configure(sizeof(LightInfo));
    _ubo.setBindingPoint(LIGHT_POINT);
}

void GameLight::setPosition(const Point3D & position) {
    _lightInfo.position = Point4D(position, 1.0f);
}

void GameLight::setLightColor(const Vector3D & lightColor) {
    _lightInfo.color = Vector4D(lightColor, 1.0f);
}

void GameLight::setDisplayLight(int displayLight) {
    _lightInfo.display = displayLight;
}

void GameLight::setAmbientLighting(float ambient) {
    _lightInfo.ambient = ambient;
}

void GameLight::setSpecularFactor(float specularFactor) {
    _lightInfo.specularFactor = specularFactor;
}

void GameLight::setSpecularExponent(int specularExponent) {
    _lightInfo.specularExponent = specularExponent;
}

void GameLight::apply(const Point3D & cameraPosition) {
    _lightInfo.cameraPosition = Point4D(cameraPosition, 1.0f);
    _ubo.setData(&_lightInfo, sizeof(LightInfo));
}

}
