/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __BUTTON_MAINTITLE_H__
#define __BUTTON_MAINTITLE_H__


#include <wgame/wgame.hpp>
#include "Scene.hpp"


#define HOVER_COLOR ColorRGB(0.2f, 0.2f, 1.0f)


using namespace wgame;

class MaintitleHoverButton : public GameObject {
public:
    MaintitleHoverButton(Button * button);
    void update() override;
protected:
    Button * _button;
    Font _font;
    bool _rebuild;
};

class CharacterSelector : public MaintitleHoverButton {
public:
    CharacterSelector(Button * button);
    void renderHUD(const Size & screenSize) override;
private:
    Size _screenSize;
    Point2D _position;
};

class OptionButton : public MaintitleHoverButton {
public:
    OptionButton(Button * button, Label * label, bool * active);
    void renderHUD(const Size & screenSize) override;
private:
    Label * _label;
    bool * _active;
    bool _changed;
};

#endif
