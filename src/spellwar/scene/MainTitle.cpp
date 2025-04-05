/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/scene/Maintitle.hpp>


Maintitle::Maintitle(AbstractGame * game, World * world) : GameObject() {
    _active = true;
    _world = world;
    _game = game;

    Font font(FONT_PATH, 50.0f);    
    font.setReferencedCharacter(' ');
    font.setColumnCharacterNumber(8);

    LabelBuilder labelBuilder;
    labelBuilder.setText("Spellwar");
    labelBuilder.setPosition(Point2D(0.0f, 0.0f));
    _widget.add(labelBuilder.build(font));    

    ButtonBuilder buttonBuilder;
    buttonBuilder.setText("Play");
    buttonBuilder.setPosition(Point2D(0.0f, 100.0f));
    buttonBuilder.setAction([&]() {
        System _system;
        _system.postEvent(IN_GAME_EVENT);
        _world -> setActive(true);
        setActive(false);
    });
    _widget.add(buttonBuilder.build(font));  

    buttonBuilder.setText("Exit");
    buttonBuilder.setPosition(Point2D(0.0f, 200.0f));
    buttonBuilder.setAction([game]() {
        game -> stop();
    });
    _widget.add(buttonBuilder.build(font));  
}

void Maintitle::setActive(bool active) {
    _active = active;
}

void Maintitle::update() {
    if (_active) {
        _widget.update();
    }
}

void Maintitle::renderHUD(const Size & screenSize) {
    if (_active) {
        _widget.renderHUD(screenSize);
    }
}

MaintitleButton::MaintitleButton(Button * button) : GameObject() {
    _button = button;
}

void MaintitleButton::update() {
    if (_button -> hover()) {

    }
}
 