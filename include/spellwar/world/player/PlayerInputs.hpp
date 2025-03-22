/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __PLAYER_INPUTS__
#define __PLAYER_INPUTS__

#include <wgame/wgame.hpp>


using namespace wgame;

class Player;

class PlayerInputs {
public:
    void state(Player * player);
    void orientation(Player * player);
private: 
    System _system; 
};

#endif
