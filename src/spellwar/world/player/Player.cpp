/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>


Player::Player(Map * map) : 
GameObject(), 
_map(map),
_state(IDLE),
_jumping(false),
_leap(false),
_trySwap(false),
_active(false)
{
    hitbox.size = HITBOX_SIZE;
    _swapAnimation = {
        hitbox,
        hitbox,
        0.0f, 
        false
    };
    _playerMotion.spawnPlayer(this);

    _playerInputs.state(this);
    _playerMotion.move(this);
    _playerModel.updateCollideHitbox(this);
    _playerInputs.orientation(this);
    _playerModel.animate(this);
}

GameObject * Player::getCameraObject() {
    return &_camera;
}

void Player::setActive(bool active) {
    _active = active;
    _camera.setActive(active);
}

void Player::update() {
    _playerInputs.state(this);
    _playerMotion.move(this);
    _playerModel.updateCollideHitbox(this);
    _playerInputs.orientation(this);
    _playerModel.animate(this); 
}

void Player::render() {
    _playerModel.render();
}

void Player::renderHUD(const Size & screenSize) {
    if (_active) {
        _playerHUD.render(screenSize);
    }
}

Platform * Player::findBestAlignedPlatform(Point3D & destination) {
    Platform * bestPlatform = nullptr;
    float minDist = std::numeric_limits<float>::max();
    Vector3D gazeVector = _camera.getGaze();
    Point3D gazePosition = _camera.getHitbox().position;

    for (Platform & platform : _map -> getPlatforms()) {
        Hitbox platformHitbox = platform.getHitbox();
        Point3D intersectPoint;
        float distance = glm::length(hitbox.position - platformHitbox.position);
        if (distance > MAX_JUMP_DISTANCE || &platform == _currentPlatform) {
            continue;
        }        
        Vector3D normal = glm::normalize(platformHitbox.orientation[1]);
        bool intersect = intersectionPlatform(
            gazePosition, 
            gazeVector,  
            platformHitbox, 
            normal,
            intersectPoint
        );
        if (!intersect) {
            continue;
        }
        distance = glm::length(gazePosition - intersectPoint);
        if (distance < minDist) {
            minDist = distance;
            bestPlatform = &platform;
            destination = intersectPoint;
        }
    }

    return bestPlatform;
}

bool Player::intersectionPlatform(
    const Point3D & gazePosition, 
    const Vector3D & gazeVector,  
    const Hitbox & hitbox,
    const Vector3D & normal,
    Point3D & intersection
) {    
    float denom = glm::dot(normal, gazeVector);
    if (glm::abs(denom) < 1e-6f) {
        return false; 
    }
    
    float t = glm::dot(normal, (hitbox.position - gazePosition)) / denom;
    if (t < 0) {
        return false;
    }

    intersection = gazePosition + t * gazeVector;
    if (!hitbox.contains(intersection)) {
        return false;
    }

    intersection += hitbox.orientation[1] * 0.5f * hitbox.size.y;
    return true;
}

bool Player::canSwap() {
    bool ok = !_trySwap && _leap && !_swapAnimation.isSwapping;
    ok &= _playerModel.getAnimationProgress() < JUMP_START_ANIM + MIN_SWAP_ANIMATION_KEYFRAME;
    return ok;
}
