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
    _model = new AnimatedModelGLTF("assets/model/player/frost.glb");
    _model -> switchAnimation("Run");
    _model -> setLoop(true);
    _model -> setActiveLight(false);
    _model -> stop();
}

Player::~Player() {
    delete _model;
}

GameObject * Player::getCameraObject() {
    return &_camera;
}

void Player::update() {
    if (_system.isKeyPressed(KEY_W)) {
        hitbox.move(_speed, AXIS_Z);
    }
    if (_system.isKeyPressed(KEY_S)) {
        hitbox.move(-_speed, AXIS_Z);
    }
    if (_system.isKeyPressed(KEY_D)) {
        hitbox.move(_speed, AXIS_X);
    }
    if (_system.isKeyPressed(KEY_A)) {
        hitbox.move(-_speed, AXIS_X);
    }
    if (_system.isKeyPressed(KEY_SPACE)) {
        hitbox.move(_speed, AXIS_Y);
    }
    if (_system.isKeyPressed(KEY_LEFT_SHIFT)) {
        hitbox.move(-_speed, AXIS_Y);
    }
    Vector2D mouseMovement = _system.getMouseMovement();
    hitbox.rotateY(mouseMovement.x * _sensibility);
    _camera.increaseAngle(mouseMovement.y * _sensibility);
    _camera.updatePlayer(hitbox);

    Matrix4D transform = glm::translate(Matrix4D(1.0f), hitbox.position);
    transform *= Matrix4D(hitbox.orientation);
    _model -> setTransform(transform);
}

void Player::render() {
    glDisable(GL_CULL_FACE);
    _modelDrawer.draw(*_model);
    glEnable(GL_CULL_FACE);
}
