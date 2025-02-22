/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/PlayerCamera.hpp>

PlayerCamera::PlayerCamera() {
    _offsetFromPlayer = Vector3D(0.0f);
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
    hitbox.move(_offsetFromPlayer.x, AXIS_X);
    hitbox.move(_offsetFromPlayer.y, AXIS_Y);
    hitbox.move(_offsetFromPlayer.z, AXIS_Z);
    hitbox.rotateX(_angle);
}

void PlayerCamera::update() {}

