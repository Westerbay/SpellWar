/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_HUD_H__
#define __PLAYER_HUD_H__

#include <wgame/wgame.hpp>


using namespace wgame;

class Player;

class PlayerHUD {
public:
    PlayerHUD();
    void render(const Size & screenSize);
private:
    ColorDrawer _visionIndicator;
};

#endif
