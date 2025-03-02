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
    //_modelStatic = new StaticModelGLTF("assets/model/player/gai/scene.gltf");
    Matrix4D transform = glm::scale(Matrix4D(1.0f), Vector3D(0.05f));
    //_modelStatic -> setTransform(transform);
    //_model = nullptr;

    _model = new AnimatedModelGLTF("assets/model/brenda.glb");
    _model -> setLoop(true);
    //_model -> setTransform(transform);
    _modelStatic = nullptr;
}

Player::~Player() {
    delete _modelStatic;
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

    
}

void Player::render() {
    //_modelDrawer.draw(*_model);
    //_modelDrawer.draw(*_modelStatic);
}
