/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/player/Player.hpp>

PlayerModel::PlayerModel() {    
    _hitboxDrawer.setActiveLight(false);
    _modelDrawer.setActiveLight(false);
    _model = nullptr;
}

float PlayerModel::getAnimationProgress() const {
    return _model -> getAnimationProgress();
}

void PlayerModel::setCharacter(Character * model) {
    if (_model) {
        model -> switchAnimation(
            _model -> getCurrentAnimation()
        );
        model -> setLoop(
            _model -> isLooping()
        );
        model -> setAnimationProgress(
            _model -> getAnimationProgress()
        );
        model -> update();
    }
    else {
        model -> setLoop(true);
    }
    _model = model;
    _model -> setTimeAcceleration(ANIMATION_ACCELERATION);
    
}

void PlayerModel::setTransform(const Matrix4D & transform) {
    _model -> setTransform(transform);
}

void PlayerModel::updateTransform(Player * player) {
    Hitbox & hitbox = player -> hitbox;
    Vector3D positionModel = hitbox.position;
    positionModel -= hitbox.orientation[1] * hitbox.size.y * 0.5f;
    Matrix4D transform = glm::translate(Matrix4D(1.0f), positionModel);
    transform *= Matrix4D(hitbox.orientation);
    setTransform(transform);
}

void PlayerModel::animate(Player * player) {    
    if (player -> _jumping) {        
        _model -> switchAnimation("Jump", false);
        if (!player -> _leap) {
            _model -> setAnimationProgress(JUMP_START_ANIM);
            player -> _leap = true;
        }
    } else if (player -> _state == Player::IDLE) {
        _model -> switchAnimation("Idle", true);
    } else if (player -> _state == Player::STRAFE && player -> _direction == Player::LEFT) {
        _model -> switchAnimation("WalkRight", true);
    } else if (player -> _state == Player::STRAFE && player -> _direction == Player::RIGHT) {
        _model -> switchAnimation("WalkLeft", true);
    } else if (player -> _state == Player::WALKING) {
        _model -> switchAnimation("Walking", true);
    } else if (player -> _state == Player::RUNNING) {
        _model -> switchAnimation("Run", true);
    } else if (player -> _state == Player::BACK) {
        _model -> switchAnimation("Walking", true, true);
    }    
    
    if (player -> _jumping && _model -> getCurrentAnimation() == "Jump") {
        if (_model -> getAnimationProgress() > JUMP_END_ANIM) {
            player -> _jumping = false;
            player -> _leap = false; 
        }        
    }
    updateTransform(player);
}

void PlayerModel::updateCollideHitbox(Player * player) {
    player -> _collideHitbox = player -> hitbox;
    if (player -> _jumping) {
        float progress = _model -> getAnimationProgress();
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
            
            player -> _collideHitbox.size.y *= scaleFactor;
            player -> _collideHitbox.move(moveFactor, AXIS_Y);
        }
    }   
}

void PlayerModel::render(Player * player) {   
    if (player -> _active || _model -> getCurrentAnimation() == "Idle") {
        _model -> update();
    }     
    if (!_model -> isCullable()) {
        disableCullFace();
        _modelDrawer.draw(_model);
        enableCullFace();
    }
    else {
        _modelDrawer.draw(_model);
    }
}
