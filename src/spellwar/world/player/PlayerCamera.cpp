/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/PlayerCamera.hpp>

PlayerCamera::PlayerCamera() {
    _angle = 0.0f;
    _keyFrame = 0.0f;
    _active = false;
    _moving = false;
}

float PlayerCamera::getAngle() const {
    return _angle;
}

void PlayerCamera::setActive(bool active) {
    _active = active;
    _moving = true;
    _keyFrame = 0.0f;
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

Hitbox PlayerCamera::getOffsetPlayer(const Hitbox & playerHitbox) {
    Hitbox hitboxOffset = playerHitbox;    
    Vector3D offset = OFFSET_FROM_PLAYER;
    hitboxOffset.move(offset.x, AXIS_X);
    hitboxOffset.move(offset.y, AXIS_Y);
    hitboxOffset.move(offset.z, AXIS_Z);
    hitboxOffset.rotateY(180.0f);
    return hitboxOffset;
}

Hitbox PlayerCamera::getOffsetIGPlayer(const Hitbox & playerHitbox) {
    Hitbox hitboxOffset = playerHitbox;
    
    Vector3D offset = OFFSET_FROM_PLAYER_IG;
    float radians = glm::radians(_angle);

    float radiusX = offset.z;  
    float radiusZ = offset.z * (_angle > 0 ? 0.5f : 1.0f);  

    offset.y += glm::sin(radians) * radiusZ;
    offset.z = glm::cos(radians) * radiusX;

    hitboxOffset.move(offset.x, AXIS_X);
    hitboxOffset.move(offset.y, AXIS_Y);
    hitboxOffset.move(offset.z, AXIS_Z);

    hitboxOffset.rotateX(_angle);
    return hitboxOffset;
}

void PlayerCamera::updatePlayer(const Hitbox & playerHitbox) {
    if (_moving) {
        Hitbox start;
        Hitbox end;
        if (_active) {
            start = getOffsetPlayer(playerHitbox);
            end = getOffsetIGPlayer(playerHitbox);
        } else {
            start = getOffsetIGPlayer(playerHitbox);
            end = getOffsetPlayer(playerHitbox);
        }
        _keyFrame += CAMERA_KEY_FRAME;        
        Point3D offsetPos = end.position - start.position;
        hitbox.position = start.position + offsetPos * _keyFrame;
        Matrix3D offsetOr = end.orientation - start.orientation;
        hitbox.orientation = start.orientation + offsetOr * _keyFrame;
        _moving = _keyFrame < 1.0f;
    }
    else if (_active) {
        hitbox = getOffsetIGPlayer(playerHitbox);
    }
    else {
        hitbox = getOffsetPlayer(playerHitbox);
    }
}

Vector3D PlayerCamera::getGaze() const {
    return glm::normalize(hitbox.orientation[2]);
}
