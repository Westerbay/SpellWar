/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __ABSTRACT_GAME_H__
#define __ABSTRACT_GAME_H__

#include <wgame/core/GameObjectGroup.hpp>

#include <atomic>
#include <thread>
#include <chrono>


#define DEFAULT_TPS 60

namespace wgame {

class AbstractGame {
public:
    AbstractGame(unsigned tps = DEFAULT_TPS);
    virtual ~AbstractGame() = default;
    void setTPS(unsigned tps);
    void setWord(GameObjectGroup & world);
    void start();
    void stop();
    void addToWorld(GameObject * gameObject);
    void removeFromWorld(GameObject * gameObject);
    void updateWorld();
    virtual void init() = 0;
private:
    GameObjectGroup * _world;
    std::atomic<unsigned> _updateDelay;
    std::atomic<bool> _running;
};

}

#endif

