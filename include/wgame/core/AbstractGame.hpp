/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_ABSTRACT_GAME_H__
#define __WG_ABSTRACT_GAME_H__

#include "GameObjectGroup.hpp"
#include "GameCamera.hpp"
#include "GameLight.hpp"

#include <thread>
#include <chrono>
#include <stdexcept>


#define DEFAULT_TPS 60

namespace wgame {

class AbstractGame {
public:
    AbstractGame(unsigned tps = DEFAULT_TPS);
    virtual ~AbstractGame() = default;
    void setTPS(unsigned tps);
    GameCamera * getCamera();
    GameLight * getLight();
    void initWorld(GameObjectGroup * world);
    void initCamera(GameCamera * camera);
    void initLight(GameLight * light);
    void start();
    void stop();    
    void addToWorld(GameObject * gameObject);
    void removeFromWorld(GameObject * gameObject);
    void updateWorld();
    virtual void init() = 0;
private:
    GameObjectGroup * _world;
    GameCamera * _camera;
    GameLight * _light;
    unsigned _updateDelay;
    bool _running;
};

}

#endif

