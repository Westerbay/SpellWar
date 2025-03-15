/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/PlayerCamera.hpp>

PlayerCamera::PlayerCamera() {
    _offsetFromPlayer = OFFSET_FROM_PLAYER;
    _angle = 0;
}

void PlayerCamera::increaseAngle(float delta) {
    _angle += delta;    
    if (_angle > MAX_ANGLE_CAMERA) {
        _angle = MAX_ANGLE_CAMERA;
    }
    else if (_angle < -MAX_ANGLE_CAMERA) {
        _angle = -MAX_ANGLE_CAMERA;
    }
}

void PlayerCamera::updatePlayer(const Hitbox & playerHitbox) {
    hitbox = playerHitbox;
    
    Vector3D offset = _offsetFromPlayer;
    float radians = glm::radians(_angle);

    float radiusX = offset.z;  
    float radiusZ = offset.z * (_angle > 0 ? 0.5f : 1.0f);  

    offset.y += glm::sin(radians) * radiusZ;
    offset.z = glm::cos(radians) * radiusX;

    hitbox.move(offset.x, AXIS_X);
    hitbox.move(offset.y, AXIS_Y);
    hitbox.move(offset.z, AXIS_Z);
    hitbox.rotateX(_angle);
}

void PlayerCamera::update() {}

