/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WORLD__
#define __WORLD__

#include "Player.hpp"
#include "Background.hpp"
#include "Map.hpp"

#include <wgame/wgame.hpp>


using namespace wgame;

class World : public GameObjectGroup {
public:
    World(GameCamera * camera);
};

#endif
