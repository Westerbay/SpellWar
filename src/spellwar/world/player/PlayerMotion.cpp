/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>


PlayerMotion::PlayerMotion() {
    _speed = SPEED;
    _runningFactor = RUNNING_FACTOR;
}

void PlayerMotion::spawnPlayer(Player * player) {
    Platform & platform = randomChoice(player -> _map ->getPlatforms());
    Hitbox spawnHitbox = platform.getPlayerSpawn();
    Hitbox & hitbox = player -> hitbox;
    hitbox.orientation = spawnHitbox.orientation;
    hitbox.position = spawnHitbox.position;
    hitbox.move(hitbox.size.y * 0.5f, AXIS_Y);
    player -> _currentPlatform = &platform;
}

Vector3D PlayerMotion::getMovement(Player * player) const {
    static float value45d = glm::sqrt(2.0f) / 2.0f;
    Vector3D movement(0.0f);
    switch (player -> _state) {
        case Player::RUNNING:
            movement.z = _speed * _runningFactor;
            break;
        case Player::WALKING:
            movement.z = _speed;
            break;
        case Player::BACK:
            movement.z = -_speed;
            break;
        case Player::IDLE:
        case Player::STRAFE:
            break;
    }
    if (player -> _direction != Player::NONE) {        
        movement.x = _speed;
        movement.x *= player -> _direction == Player::RIGHT ? 1.0f : -1.0f;
        movement.x *= player -> _state == Player::RUNNING ? _runningFactor : 1.0f;        
        if (movement.z) {
            movement.z *= value45d;
            movement.x *= value45d;
        }      
    }
    return movement;
}

Hitbox PlayerMotion::getSwapPlatformHitbox(Player * player, Platform * platform, const Point3D & intersectPoint) {
    Hitbox & hitbox = player -> hitbox;
    Hitbox destinationHitbox = hitbox;
    Hitbox platformHitbox = platform -> getHitbox();

    Matrix3D A = player -> _currentPlatform -> getHitbox().orientation;
    Matrix3D B = hitbox.orientation;
    Matrix3D R = B * glm::inverse(A);
    Quaternion q = glm::quat_cast(R);
    Vector3D euler = glm::eulerAngles(q);

    destinationHitbox.orientation = platformHitbox.orientation;
    if (glm::dot(B[2], platform->getHitbox().orientation[2]) < -0.5f) {
        euler.y += PI;
    } else if (glm::dot(B[2], platform->getHitbox().orientation[0]) < -0.5f) {
        euler.y += PI / 2.0f;
    } else if (glm::dot(B[2], platform->getHitbox().orientation[0]) > 0.5f) {
        euler.y -= PI / 2.0f;
    }
    destinationHitbox.rotateY(glm::degrees(euler.y));
    destinationHitbox.position = intersectPoint;
    destinationHitbox.move(hitbox.size.y * 0.5f, AXIS_Y);
    return destinationHitbox;
}

bool PlayerMotion::swapPlatform(Player * player, Platform * platform, const Point3D & intersectPoint) {
    player -> _trySwap = true;
    Hitbox destinationHitbox = getSwapPlatformHitbox(player, platform, intersectPoint);
    PlatformAnimation swapAnimation = {
        destinationHitbox,
        player -> hitbox,
        player -> _camera.getAngle(),
        0.0f,
        true
    };
    Matrix3D pathOrientation = swapAnimation.destinationHitbox.orientation - swapAnimation.startHitbox.orientation;
    Vector3D path = swapAnimation.destinationHitbox.position - swapAnimation.startHitbox.position;
    Hitbox precalculatedHitbox = player -> hitbox;
    for (int i = 0; i < ANIMATION_COLLSION_TEST_STEP; i ++) {
        precalculatedHitbox.position += path * (1.0f / ANIMATION_COLLSION_TEST_STEP);    
        precalculatedHitbox.orientation += pathOrientation * (1.0f / ANIMATION_COLLSION_TEST_STEP);
        if (player -> _map -> collide(precalculatedHitbox)) {            
            return false;
        }
    } 
    player -> _swapAnimation = swapAnimation;
    player -> _currentPlatform = platform;
    return true;
}

void PlayerMotion::animateSwap(Player * player) {
    if (player -> _swapAnimation.keyFrame > 1.0f) {
        player -> _swapAnimation.isSwapping = false;
        player -> hitbox = player -> _swapAnimation.destinationHitbox;
    }
    else {
        Matrix3D pathOrientation = player -> _swapAnimation.destinationHitbox.orientation - player -> _swapAnimation.startHitbox.orientation;
        Vector3D path = player -> _swapAnimation.destinationHitbox.position - player -> _swapAnimation.startHitbox.position;
        player -> hitbox.position += path * SWAP_ANIMATION_KEYFRAME;
        player -> hitbox.orientation += pathOrientation * SWAP_ANIMATION_KEYFRAME;
    }
}

void PlayerMotion::move(Player * player) {   
    if (!player -> _jumping) {
        player -> _trySwap = false;
    }
    if (player -> _swapAnimation.isSwapping) {
        animateSwap(player);
        return;
    } 

    Platform * platform = player -> _currentPlatform;    
    Vector3D movement = getMovement(player);        
    Hitbox & hitbox = player -> hitbox;
    Point3D lastPosition = hitbox.position;
    Hitbox * collision;

    hitbox.move(movement);
    Hitbox deviatedHitbox = hitbox;
    deviatedHitbox.move(0.001f, AXIS_Y);
    deviatedHitbox.orientation = platform -> getHitbox().orientation;
    collision = player -> _map -> collide(deviatedHitbox);
    if (collision) {
        hitbox.position = lastPosition;
    } 
    else if (!platform -> onPlatform(deviatedHitbox) && player -> canSwap()) {
        Point3D destination;
        Platform * destPlat = player -> findBestAlignedPlatform(destination);
        if (destPlat && swapPlatform(player, destPlat, destination)) {
            return;
        }
        else {
            hitbox.position = lastPosition;
        }
    }
    else if (!platform -> onPlatform(deviatedHitbox)) {
        hitbox.position = lastPosition;
    }             
}
