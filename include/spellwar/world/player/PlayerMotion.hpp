/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_MOTION_H__
#define __PLAYER_MOTION_H__

#include <wgame/wgame.hpp>
#include "../map/Platform.hpp"

#define SPEED 0.08f
#define RUNNING_FACTOR 2.0f

using namespace wgame;

class Player;

class PlayerMotion {
public:
    PlayerMotion();
    Vector3D getMovement(Player * player) const;
    void spawnPlayer(Player * player);
    void move(Player * player);
private:
    void animateSwap(Player * player);
    bool swapPlatform(Player * player, Platform * platform, const Point3D & intersectPoint);
    Hitbox getSwapPlatformHitbox(Player * player, Platform * platform, const Point3D & intersectPoint);
private:
    float _speed;
    float _runningFactor;
};

#endif
