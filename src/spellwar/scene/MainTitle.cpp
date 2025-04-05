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
    labelBuilder.setHorizontalResponsive(true);
    labelBuilder.setDesignedSize(DEFAULT_SIZE);
    labelBuilder.setText("Spellwar");
    labelBuilder.setPosition(Point2D(0.0f, 0.0f));
    _widget.add(labelBuilder.build(font));    

    setButtons(font);
    setBackground();
}

void Maintitle::setButtons(const Font & font) {
    ButtonBuilder buttonBuilder;
    buttonBuilder.setHorizontalResponsive(true);
    buttonBuilder.setDesignedSize(DEFAULT_SIZE);
    buttonBuilder.setText("Play");
    buttonBuilder.setPosition(Point2D(0.0f, 100.0f));
    buttonBuilder.setAction([&]() {
        System system;
        system.postEvent(IN_GAME_EVENT);
        _world -> setActive(true);
        setActive(false);
    });
    Button * playButton = buttonBuilder.build(font);
    _widget.add(playButton);  

    buttonBuilder.setText("Exit");
    buttonBuilder.setPosition(Point2D(0.0f, 200.0f));
    buttonBuilder.setAction([&]() {
        _game -> stop();
    });
    Button * exitButton = buttonBuilder.build(font);
    _widget.add(exitButton);  

    _widget.add(new MaintitleButton(playButton));
    _widget.add(new MaintitleButton(exitButton));
}

void Maintitle::setBackground() {
    Hitbox background;
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
    _text = button -> getText();
}

void MaintitleButton::update() {
    String text = _button -> getText();
    bool hover = _button -> hover();
    if (hover && text[0] != '>') {
        Font font(FONT_PATH, 50.0f);    
        font.setReferencedCharacter(' ');
        font.setColumnCharacterNumber(8);
        _button -> setText(">" + _text);
        _button -> rebuild(font);
    } else if (!hover && text[0] == '>') {
        Font font(FONT_PATH, 50.0f);    
        font.setReferencedCharacter(' ');
        font.setColumnCharacterNumber(8);
        _button -> setText(_text);
        _button -> rebuild(font);
    }
}
 