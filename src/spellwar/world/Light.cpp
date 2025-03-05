/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Light.hpp>

Light::Light(GameLight * gameLight) : GameObject() {
    _gameLight = gameLight;
    _angle = 0.0f;
    _color = ColorRGB(1.0f, 1.0f, 1.0f);
    update();
}

void Light::update() {
    _angle += STEP_TIME;
    if (_angle > 360.0f) {
        _angle -= 360.0f;
    }
    hitbox.position.x = glm::cos(glm::radians(_angle));
    hitbox.position.y = glm::sin(glm::radians(_angle));

    _gameLight -> setPosition(hitbox.position * LIGHT_DISTANCE_TO_WORLD);
    _gameLight -> setLightColor(_color);
}

void Light::renderBackground() {   
    Matrix4D model(1.0f); 
    model = glm::translate(model, hitbox.position);
    model = glm::rotate(model, glm::radians(_angle * 5.0f), AXIS_Y);
    model = glm::scale(model, Vector3D(LIGHT_SIZE));
    _sun.setTransform(model);
    _drawer.drawStatic(_sun);
}

Light::Sun::Sun() : StaticModelGLTF(SUN_ASSET) {}

