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
#define FONT_SIZE_OPTIONS 20.0f
#define FONT_SIZE_SELECTOR 75.0f
#define MARGIN 80.0f

#define HOVER_COLOR ColorRGB(0.2f, 0.2f, 1.0f)


using namespace wgame;

class Maintitle : public Scene {
public:
    enum State {
        MAIN, OPTIONS
    };
public:
    Maintitle(AbstractGame * game, World * world);  
    void setActive(bool active) override;
    void update() override;
    void renderHUD(const Size & screenSize) override;
private:
    void setMaintitleButtons(Font & font);
    void setCharacterSelector(Font & font);
    void setOptions(Font & font);
    void setBackground();
private:
    State _state;
    bool _active;
    Font _font;
    AbstractGame * _game;
    World * _world;
    ColorDrawer _colorDrawer;
    GameObjectGroup _mainTitleButtons;
    GameObjectGroup _optionButtons;
    GameObjectGroup _characterSelector;

    bool _lightDisplay;
    bool _activeNormalMapping;
    bool _activeParallaxMapping;
};

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
