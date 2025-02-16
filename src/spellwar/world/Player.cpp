/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Player.hpp>
#include <iostream>


Player::Player(const Hitbox & hitbox) : GameObject(hitbox) {
    _speed = 0.2f;
    _sensibility = 0.2f;
}

GameObject * Player::getCameraObject() {
    return &_camera;
}

void Player::update() {
    if (_inputs.isKeyPressed(KEY_W)) {
        hitbox.move(_speed, AXIS_Z);
    }
    if (_inputs.isKeyPressed(KEY_S)) {
        hitbox.move(-_speed, AXIS_Z);
    }
    if (_inputs.isKeyPressed(KEY_D)) {
        hitbox.move(_speed, AXIS_X);
    }
    if (_inputs.isKeyPressed(KEY_A)) {
        hitbox.move(-_speed, AXIS_X);
    }
    if (_inputs.isKeyPressed(KEY_SPACE)) {
        hitbox.move(_speed, AXIS_Y);
    }
    if (_inputs.isKeyPressed(KEY_LEFT_SHIFT)) {
        hitbox.move(-_speed, AXIS_Y);
    }
    Vector2D mouseMovement = _inputs.getMouseMovement();
    hitbox.rotateY(mouseMovement.x * _sensibility);
    _camera.increaseAngle(mouseMovement.y * _sensibility);
    _camera.updatePlayer(hitbox);
}
