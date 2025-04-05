/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/PlayerCamera.hpp>

PlayerCamera::PlayerCamera() {
    _angle = 0;
    _active = false;
}

float PlayerCamera::getAngle() const {
    return _angle;
}

void PlayerCamera::setActive(bool active) {
    _active = active;
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

Vector3D PlayerCamera::getOffsetFromPlayer() {
    if (_active) {
        return OFFSET_FROM_PLAYER_IG;
    }
    else {
        return OFFSET_FROM_PLAYER;
    }
}

void PlayerCamera::updatePlayer(const Hitbox & playerHitbox) {
    hitbox = playerHitbox;
    
    Vector3D offset = getOffsetFromPlayer();
    float radians = glm::radians(_angle);

    float radiusX = offset.z;  
    float radiusZ = offset.z * (_angle > 0 ? 0.5f : 1.0f);  

    offset.y += glm::sin(radians) * radiusZ;
    offset.z = glm::cos(radians) * radiusX;

    hitbox.move(offset.x, AXIS_X);
    hitbox.move(offset.y, AXIS_Y);
    hitbox.move(offset.z, AXIS_Z);
    hitbox.rotateX(_angle);

    if (!_active) {
        hitbox.rotateY(180.0f);
    }
}

Vector3D PlayerCamera::getGaze() const {
    return glm::normalize(hitbox.orientation[2]);
}
