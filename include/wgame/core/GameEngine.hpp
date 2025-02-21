/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_GAME_ENGINE_H__
#define __WG_GAME_ENGINE_H__

#include "AbstractGame.hpp"
#include "AbstractFrame.hpp"
#include "GameObjectGroup.hpp"
#include "GameCamera.hpp"

#include <atomic>


namespace wgame {

class GameEngine {
public:
    GameEngine(AbstractGame * game, AbstractFrame * frame);
    ~GameEngine();
    void start();
private:
    static void gameLoop(AbstractGame * game);
    GameCamera * _camera;
    GameObjectGroup * _world;   
    AbstractGame * _game;
    AbstractFrame * _frame;     
};

}


#endif

