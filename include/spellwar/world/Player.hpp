/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <wgame/wgame.hpp>
#include "PlayerCamera.hpp"


using namespace wgame;

class Player : public GameObject {
public:
    Player(const Hitbox & hitbox);    
    ~Player();
    GameObject * getCameraObject();
    void update() override;
    void render() override;
private: 
    float _speed;
    float _sensibility;
    System _system;
    PlayerCamera _camera;
    AnimatedModelGLTF * _model;
    StaticModelGLTF * _modelStatic;
    ModelDrawer _modelDrawer;
};


#endif
