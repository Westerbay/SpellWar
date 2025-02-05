/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GAME_ENGINE_H__
#define __GAME_ENGINE_H__

#include <wgame/core/AbstractGame.hpp>
#include <wgame/gui/AbstractFrame.hpp>

#include <atomic>


namespace wgame {

class GameEngine {
public:
    GameEngine(AbstractGame * game, AbstractFrame * frame);
    ~GameEngine();
    bool isRunning() const;
    void start();
    void pause();
    void exit();
private:
    AbstractGame * _game;
    AbstractFrame * _frame;
    std::atomic<bool> _running;
};

}


#endif

