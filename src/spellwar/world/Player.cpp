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
    _speed = SPEED;
    _runningFactor = RUNNING_FACTOR;
    _sensibility = 0.2f;
    _state = IDLE;
    _model.setActiveLight(false);
    _model.setTimeAcceleration(ANIMATION_ACCELERATION);
}

GameObject * Player::getCameraObject() {
    return &_camera;
}

void Player::update() {
    state();
    move();
    animate();
}

void Player::state() {
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
}

void Player::move() {  
    
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
    }
    switch (_direction) {
        case RIGHT:
            movement.x = _speed;
            break;
        case LEFT:
            movement.x = -_speed;
            break;
    }

    hitbox.move(movement);

    Vector2D mouseMovement = _system.getMouseMovement();
    hitbox.rotateY(mouseMovement.x * _sensibility);
    _camera.increaseAngle(mouseMovement.y * _sensibility);
    _camera.updatePlayer(hitbox);

    Matrix4D transform = glm::translate(Matrix4D(1.0f), hitbox.position);
    transform *= Matrix4D(hitbox.orientation);
    _model.setTransform(transform);
}

void Player::animate() {
    if (_state == IDLE) {
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
}

void Player::render() {
    glDisable(GL_CULL_FACE);
    _modelDrawer.draw(_model);
    glEnable(GL_CULL_FACE);
}


Player::FrostModel::FrostModel() : AnimatedModelGLTF(FROST_MODEL) {}