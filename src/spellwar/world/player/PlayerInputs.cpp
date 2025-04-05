/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>

void PlayerInputs::state(Player * player) {
    if (player -> _swapAnimation.isSwapping) {
        player -> _direction = Player::NONE;
        player -> _swapAnimation.keyFrame += SWAP_ANIMATION_KEYFRAME;
        return;
    }

    if (_system.isKeyPressed(KEY_W)) {
        if (_system.isKeyPressed(KEY_LEFT_SHIFT)) {
            player -> _state = Player::RUNNING;
        }
        else {
            player -> _state = Player::WALKING;
        }
    }
    else if (_system.isKeyPressed(KEY_S)) {
        player -> _state = Player::BACK;
    }
    else {
        player -> _state = Player::IDLE;
    }

    if (_system.isKeyPressed(KEY_D) && !_system.isKeyPressed(KEY_A)) {
        if (player -> _state == Player::IDLE) {
            player -> _state = Player::STRAFE;
        }
        player -> _direction = Player::RIGHT;
    }
    else if (_system.isKeyPressed(KEY_A) && !_system.isKeyPressed(KEY_D)) {
        if (player -> _state == Player::IDLE) {
            player ->  _state = Player::STRAFE;
        }
        player -> _direction = Player::LEFT;
    }
    else {
        player -> _direction = Player::NONE;
    }
    if (_system.isKeyPressed(KEY_SPACE) && !player -> _jumping) {
        player -> _jumping = true;
    }
}

void PlayerInputs::orientation(Player * player) {
    if (!player -> _swapAnimation.isSwapping) {
        Vector2D mouseMovement = _system.getMouseMovement();
        player -> hitbox.rotateY(mouseMovement.x * _system.getSensibility());
        player -> _camera.increaseAngle(mouseMovement.y * _system.getSensibility());
    } else {        
        player -> _camera.increaseAngle(-SWAP_ANIMATION_KEYFRAME * player -> _swapAnimation.angle);
    }     
}
