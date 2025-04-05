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
#include "Scene.hpp"

#define FONT_SIZE_TITLE 50.0f
#define FONT_SIZE_BUTTONS 25.0f
#define MARGIN 50.0f


using namespace wgame;

class Maintitle : public Scene {
public:
    Maintitle(AbstractGame * game, Scene * world);  
    void setActive(bool active) override;
    void update() override;
    void renderHUD(const Size & screenSize) override;
private:
    void setButtons();
    void setBackground();
private:
    bool _active;
    AbstractGame * _game;
    Scene * _world;
    ColorDrawer _colorDrawer;
};

class MaintitleButton : public GameObject {
public:
    MaintitleButton(Button * button);
    void update() override;
private:
    Button * _button;
    String _text;
};


#endif
