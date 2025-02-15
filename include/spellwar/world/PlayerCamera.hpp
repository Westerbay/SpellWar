/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_CAMERA_H__
#define __PLAYER_CAMERA_H__
 
#include <wgame/wgame.hpp>

 
using namespace wgame;
 
class PlayerCamera : public GameObject {
public:
    PlayerCamera();
    void increaseAngle(float delta);    
    void updatePlayer(const Hitbox & playerHitbox);  
    void update() override;  
private:
    Vector3D _offsetFromPlayer;
    float _angle;
};
 
 
#endif