/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Light.hpp>

Light::Light(GameLight * gameLight) : GameObject() {
    _sphere.radius = LIGHT_SIZE;
    _gameLight = gameLight;
    _angle = 0.0f;
    _color = ColorRGB(1.0f, 1.0f, 1.0f);
    _drawer.setFillSphereData(_sphere, SLICES_STACKS, SLICES_STACKS);
    update();
}

void Light::update() {
    _angle += STEP_TIME;
    if (_angle > 360.0f) {
        _angle -= 360.0f;
    }
    _sphere.position.x = glm::cos(glm::radians(_angle));
    _sphere.position.y = glm::sin(glm::radians(_angle));

    _gameLight -> setPosition(_sphere.position * LIGHT_DISTANCE_TO_WORLD);
    _gameLight -> setLightColor(_color);
}

void Light::renderBackground() {   
    Matrix4D model(1.0f); 
    model = glm::translate(model, _sphere.position);
    _drawer.drawLight(model);
}
