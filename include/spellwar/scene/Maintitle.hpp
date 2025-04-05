/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __MAINTITLE__
#define __MAINTITLE__

#define FONT_PATH "assets/font.png"

#include <wgame/wgame.hpp>

#include "World.hpp"
#include "Events.hpp"


using namespace wgame;

class Maintitle : public GameObject {
public:
    Maintitle(AbstractGame * game, World * world);  
    void setActive(bool active);
    void update() override;
    void renderHUD(const Size & screenSize) override;
private:
    GameObjectGroup _widget;
    bool _active;
    AbstractGame * _game;
    World * _world;
};

class MaintitleButton : public GameObject {
public:
    MaintitleButton(Button * button);
    void update() override;
private:
    Button * _button;
};


#endif
