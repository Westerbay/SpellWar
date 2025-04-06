/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_MODEL_H__
#define __PLAYER_MODEL_H__

#include <wgame/wgame.hpp>

#include "../character/Character.hpp"

#define ANIMATION_ACCELERATION 1.5f

#define JUMP_START_PROGRESS 0.20f
#define JUMP_END_PROGRESS 0.65f
#define JUMP_START_ANIM 0.20f
#define JUMP_END_ANIM 0.80f
#define JUMP_HEIGHT 0.65f 


using namespace wgame;

class Player;

class PlayerModel {
public:
    PlayerModel();
    float getAnimationProgress() const;
    void setCharacter(Character * model);
    void setTransform(const Matrix4D & transform);
    void updateCollideHitbox(Player * player);
    void animate(Player * player);
    void render(Player * player);
private:
    void updateTransform(Player * player);
private:
    Character * _model;
    ModelDrawer _modelDrawer;
    ColorDrawer _hitboxDrawer;
};

#endif