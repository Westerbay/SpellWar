/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/Player.hpp>
#include <iostream>


Player::Player(Map * map) : GameObject(), _map(map) {
    _speed = SPEED;
    _runningFactor = RUNNING_FACTOR;
    _state = IDLE;
    _model.setTimeAcceleration(ANIMATION_ACCELERATION);
    hitbox.size = HITBOX_SIZE;

    Platform & platform = randomChoice(map->getPlatforms());
    Hitbox spawnHitbox = platform.getPlayerSpawn();
    hitbox.orientation = spawnHitbox.orientation;
    hitbox.position = spawnHitbox.position;
    hitbox.move(hitbox.size.y * 0.5f, AXIS_Y);
    _currentPlatform = &platform;

    _jumping = false;
    _leap = false;
    _swapAnimation = {
        hitbox,
        hitbox,
        0.0f, 
        false
    };

    _hitboxDrawer.setActiveLight(false);
    _modelDrawer.setActiveLight(false);

    Sphere sphere(Point3D(0.0f), 0.004f);
    _visionIndicator.setFillSphereData(
        sphere, ColorRGB(1.0f), 40, 40
    );
    _transformHUD = glm::perspective(
        glm::radians(60.0f), 
        (float) 16 / 9,
         0.01f, 
         100.0f
    );
}

GameObject * Player::getCameraObject() {
    return &_camera;
}

void Player::update() {
    state();
    move();
    updateCollideHitbox();
    orientation();
    animate();    
}

void Player::state() {
    if (_swapAnimation.isSwapping) {
        _direction = NONE;
        _swapAnimation.keyFrame += SWAP_ANIMATION_KEYFRAME;
        return;
    }

    if (_system.isKeyPressed(KEY_W)) {
        if (_system.isKeyPressed(KEY_LEFT_SHIFT)) {
            _state = RUNNING;
        }
        else {
            _state = WALKING;
        }
    }
    else if (_system.isKeyPressed(KEY_S)) {
        _state = BACK;
    }
    else {
        _state = IDLE;
    }

    if (_system.isKeyPressed(KEY_D) && !_system.isKeyPressed(KEY_A)) {
        if (_state == IDLE) {
            _state = STRAFE;
        }
        _direction = RIGHT;
    }
    else if (_system.isKeyPressed(KEY_A) && !_system.isKeyPressed(KEY_D)) {
        if (_state == IDLE) {
            _state = STRAFE;
        }
        _direction = LEFT;
    }
    else {
        _direction = NONE;
    }
    if (_system.isKeyPressed(KEY_SPACE) && !_jumping) {
        _jumping = true;
    }
}

Vector3D Player::getMovement() const {
    static float value45d = glm::sqrt(2.0f) / 2.0f;
    Vector3D movement(0.0f);
    switch (_state) {
        case RUNNING:
            movement.z = _speed * _runningFactor;
            break;
        case WALKING:
            movement.z = _speed;
            break;
        case BACK:
            movement.z = -_speed;
            break;
        case IDLE:
        case STRAFE:
            break;
    }
    if (_direction != NONE) {        
        movement.x = _speed;
        movement.x *= _direction == RIGHT ? 1.0f : -1.0f;
        movement.x *= _state == RUNNING ? _runningFactor : 1.0f;        
        if (movement.z) {
            movement.z *= value45d;
            movement.x *= value45d;
        }      
    }
    return movement;
}

bool Player::onPlatform() const {
    Hitbox platformHitbox = _currentPlatform -> getHitbox();
    Hitbox playerHitbox = hitbox;
    float delta = (playerHitbox.size.y + platformHitbox.size.y) * 0.5f;
    playerHitbox.move(-delta, AXIS_Y);
    return platformHitbox.contains(playerHitbox.position);
}

void Player::swapPlatform(Platform * platform, const Point3D & intersectPoint) {
    Hitbox destinationHitbox = hitbox;
    Hitbox platformHitbox = platform -> getHitbox();

    Matrix3D A = _currentPlatform -> getHitbox().orientation;
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
    destinationHitbox.move(this->hitbox.size.y * 0.5f, AXIS_Y);
    _currentPlatform = platform;
    _swapAnimation = {
        destinationHitbox,
        hitbox,
        0.0f,
        true
    };
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

void Player::move() {   
    if (_swapAnimation.isSwapping) {
        if (_swapAnimation.keyFrame > 1.0f) {
            _swapAnimation.isSwapping = false;
            hitbox = _swapAnimation.destinationHitbox;
        }
        else {
            Vector3D path = _swapAnimation.destinationHitbox.position - _swapAnimation.startHitbox.position;
            hitbox.position += path * SWAP_ANIMATION_KEYFRAME;
            Matrix3D pathOrientation = _swapAnimation.destinationHitbox.orientation - _swapAnimation.startHitbox.orientation;
            hitbox.orientation += pathOrientation * SWAP_ANIMATION_KEYFRAME;
        }
    } else {
        Vector3D movement = getMovement();
        Point3D lastPosition = hitbox.position; 
        hitbox.move(movement);
        if (!onPlatform()) {
            if (canSwap()) {
                Point3D destination;
                Platform * destPlat = findBestAlignedPlatform(destination);
                if (!destPlat) {
                    hitbox.position = lastPosition; 
                }
                else {
                    swapPlatform(destPlat, destination);
                }
            }
            else {
                _state = IDLE;
                hitbox.position = lastPosition;   
            }             
        }    
    }     
}

void Player::updateCollideHitbox() {
    _collideHitbox = hitbox;
    if (_jumping) {
        float progress = _model.getAnimationProgress();
        if (progress > JUMP_START_PROGRESS && progress < JUMP_END_PROGRESS) {
            float midProgress = (JUMP_START_PROGRESS + JUMP_END_PROGRESS) / 2.0f;
            float scaleFactor;
            float moveFactor;
            
            if (progress < midProgress) {
                scaleFactor = 1.0f + ((progress - JUMP_START_PROGRESS) / (midProgress - JUMP_START_PROGRESS)) * (JUMP_HEIGHT - 1.0f);
                moveFactor = ((progress - JUMP_START_PROGRESS) / (midProgress - JUMP_START_PROGRESS)) * JUMP_HEIGHT;
            } else {
                scaleFactor = 1.0f + ((JUMP_END_PROGRESS - progress) / (JUMP_END_PROGRESS - midProgress)) * (JUMP_HEIGHT - 1.0f);
                moveFactor = ((JUMP_END_PROGRESS - progress) / (JUMP_END_PROGRESS - midProgress)) * JUMP_HEIGHT;
            }
            
            _collideHitbox.size.y *= scaleFactor;
            _collideHitbox.move(moveFactor, AXIS_Y);
        }
    }
}

void Player::orientation() {
    Vector3D positionModel = hitbox.position;
    positionModel -= hitbox.orientation[1] * hitbox.size.y * 0.5f;

    Vector2D mouseMovement = _system.getMouseMovement();
    hitbox.rotateY(mouseMovement.x * _system.getSensibility());
    _camera.increaseAngle(mouseMovement.y * _system.getSensibility());
    _camera.updatePlayer(_collideHitbox);

    Matrix4D transform = glm::translate(Matrix4D(1.0f), positionModel);
    transform *= Matrix4D(hitbox.orientation);
    _model.setTransform(transform);
}

void Player::animate() {
    if (_jumping) {        
        _model.switchAnimation("Jump", false);
        if (!_leap) {
            _model.setAnimationProgress(JUMP_START_ANIM);
            _leap = true;
        }
    } else if (_state == IDLE) {
        _model.switchAnimation("Idle", true);
    } else if (_state == STRAFE && _direction == LEFT) {
        _model.switchAnimation("WalkRight", true);
    } else if (_state == STRAFE && _direction == RIGHT) {
        _model.switchAnimation("WalkLeft", true);
    } else if (_state == WALKING) {
        _model.switchAnimation("Walking", true);
    } else if (_state == RUNNING) {
        _model.switchAnimation("Run", true);
    } else if (_state == BACK) {
        _model.switchAnimation("Walking", true, true);
    }    
    
    if (_jumping && _model.getCurrentAnimation() == "Jump") {
        if (_model.getAnimationProgress() > JUMP_END_ANIM) {
            _jumping = false;
            _leap = false; 
        }        
    }
}

void Player::render() {
    disableCullFace();
    _modelDrawer.draw(_model);
    enableCullFace();
    _hitboxDrawer.setDrawCuboidData(_collideHitbox, ColorRGB(1.0f, 0.0f, 0.0f));
    _hitboxDrawer.draw();
}

void Player::renderHUD() {
    _visionIndicator.fill(_transformHUD, Drawer::HUD);
}


Player::FrostModel::FrostModel() : AnimatedModelGLTF(FROST_MODEL) {}

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
    bool ok = _jumping && !_swapAnimation.isSwapping;
    ok &= _model.getCurrentAnimation() == "Jump";
    ok &= _model.getAnimationProgress() < JUMP_START_ANIM + MIN_SWAP_ANIMATION_KEYFRAME;
    return ok;
}
