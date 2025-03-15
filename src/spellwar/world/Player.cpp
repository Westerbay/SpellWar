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
    _sensibility = 0.2f;
    _state = IDLE;
    _model.setActiveLight(false);
    _model.setTimeAcceleration(ANIMATION_ACCELERATION);
    this->hitbox.size = Vector3D(0.7f, 1.65f, 0.7f);

    Platform & platform = randomChoice(map->getPlatforms());
    Hitbox spawnHitbox = platform.getPlayerSpawn();
    this->hitbox.orientation = spawnHitbox.orientation;
    this->hitbox.position = spawnHitbox.position;
    this->hitbox.move(this->hitbox.size.y * 0.5f, AXIS_Y);
    _currentPlatform = &platform;

    _jumping = false;
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
    if (_system.isKeyPressed(KEY_SPACE) && !_jumping) {
        _jumping = true;
    }
}

void Player::move() {    
    
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

    Point3D lastPosition = hitbox.position; 
    hitbox.move(movement.z, AXIS_Z);
    if (!onPlatform()) {
        hitbox.position = lastPosition;     
    }    
    lastPosition = hitbox.position;  
    hitbox.move(movement.x, AXIS_X);
    if (!onPlatform()) {
        hitbox.position = lastPosition;        
    }    

    Vector3D positionModel = hitbox.position;
    positionModel -= hitbox.orientation[1] * hitbox.size.y * 0.5f;

    Vector2D mouseMovement = _system.getMouseMovement();
    hitbox.rotateY(mouseMovement.x * _sensibility);
    _camera.increaseAngle(mouseMovement.y * _sensibility);
    _camera.updatePlayer(hitbox);

    Matrix4D transform = glm::translate(Matrix4D(1.0f), positionModel);
    transform *= Matrix4D(hitbox.orientation);
    _model.setTransform(transform);
}

void Player::animate() {
    if (_jumping && _model.getCurrentAnimation() == "Jump") {
        _jumping = _model.isRunning();
    }

    if (_jumping) {
        _model.switchAnimation("Jump", false);
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
}

bool Player::onPlatform() const {
    Hitbox platformHitbox = _currentPlatform -> getHitbox();
    Hitbox playerHitbox = hitbox;
    float delta = (playerHitbox.size.y + platformHitbox.size.y) * 0.5f;
    playerHitbox.move(-delta, AXIS_Y);
    Point3D position = playerHitbox.position;
    return platformHitbox.contains(position);
}

void Player::render() {
    glDisable(GL_CULL_FACE);
    _modelDrawer.draw(_model);
    glEnable(GL_CULL_FACE);
    _hitboxDrawer.setDrawCuboidData(hitbox, ColorRGB(1.0f, 0.0f, 0.0f));
    _hitboxDrawer.draw();
}


Player::FrostModel::FrostModel() : AnimatedModelGLTF(FROST_MODEL) {}