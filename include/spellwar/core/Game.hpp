/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GAME__
#define __GAME__

#include "../scene/World.hpp"
#include "../scene/Maintitle.hpp"

#include <wgame/wgame.hpp>


using namespace wgame;

class Game : public AbstractGame {
public:
    Game(unsigned tps = DEFAULT_TPS);
    void init() override;
private:
    World * _world;
    Maintitle * _mainTitle;
};


#endif

