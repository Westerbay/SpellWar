/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/map/Light.hpp>

Light::Light(GameLight * gameLight, StaticModelGLTF * sun, float scale) : GameObject() {
    _gameLight = gameLight;
    _scale = scale;
    _angle = 0.0f;
    _color = ColorRGB(1.0f, 1.0f, 1.0f);    
    
    _gameLight -> setDisplayLight(true);
    _gameLight -> setPosition(LIGHT_POSITION);
    _gameLight -> setDefaultAmbientLighting(DEFAULT_AMBIENT);
    _gameLight -> setDefaultSpecularFactor(DEFAULT_SPECULAR_FACTOR);
    _gameLight -> setDefaultSpecularExponent(DEFAULT_SPECULAR_EXPONENT);
    _gameLight -> setActiveNormalMap(true);
    _gameLight -> setActiveParallaxMapping(true);

    _sun = sun;
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
    model = glm::rotate(model, glm::radians(_angle * SUN_ROTATION), AXIS_Y);
    model = glm::scale(model, Vector3D(_scale));
    _sun -> setTransform(model);
    _drawer.draw(*_sun, Drawer::BACKGROUND);
}

