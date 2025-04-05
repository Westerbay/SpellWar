/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __SCENE_H__
#define __SCENE_H__

#include <wgame/wgame.hpp>

#define DEFAULT_SIZE {1280, 720}


using namespace wgame;

enum Events {
    IN_GAME_EVENT,
    IN_MAINTITLE_EVENT
};

class Scene : public GameObjectGroup {
public:
    virtual void setActive(bool active) = 0;
};

#endif
