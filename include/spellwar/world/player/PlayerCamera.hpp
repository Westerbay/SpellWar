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

#define MAX_ANGLE_CAMERA 70.0f
#define OFFSET_FROM_PLAYER Vector3D(0.4f, 0.0f, 2.5f) //Vector3D(0.3f, 0.7f, -2.5f)

 
using namespace wgame;
 
class PlayerCamera : public GameObject {
public:
    PlayerCamera();
    float getAngle() const;
    void increaseAngle(float delta);    
    void updatePlayer(const Hitbox & playerHitbox);  
    Vector3D getGaze() const;    
private:
    Vector3D _offsetFromPlayer;
    float _angle;
};
 
 
#endif