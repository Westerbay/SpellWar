/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/scene/MaintitleButton.hpp>


MaintitleHoverButton::MaintitleHoverButton(Button * button) : GameObject() {
    _button = button;
    _font = button -> getFont();
    _rebuild = false;
}

void MaintitleHoverButton::update() {
    bool hover = _button -> hover();
    if (hover && !_rebuild) { 
        Font font = _font;
        font.setColor(HOVER_COLOR);
        _button -> setFont(font);
        _button -> rebuild();
        _rebuild = true;
    } else if (!hover && _rebuild) {
        _button -> setFont(_font);
        _button -> rebuild();
        _rebuild = false;
    }
}

CharacterSelector::CharacterSelector(Button * button) : MaintitleHoverButton(button) {
    _position = button -> getPosition();
    _screenSize = DEFAULT_SIZE;
}

void CharacterSelector::renderHUD(const Size & screenSize) {
    if (_screenSize.width == screenSize.width && _screenSize.height == screenSize.height) {
        MaintitleHoverButton::renderHUD(screenSize);
        return;
    }
    Size designedSize = DEFAULT_SIZE;
    float designedRatio = (float) designedSize.width / designedSize.height;
    float ratio = (float) screenSize.width / screenSize.height;
    float diff = designedRatio - ratio;
    _button -> setPosition(_position + Vector2D(diff * 175.0f));
    _button -> rebuild();
    _screenSize = screenSize;
    MaintitleHoverButton::renderHUD(screenSize);
}

OptionButton::OptionButton(Button * button, Label * label, bool * active) : MaintitleHoverButton(button) {
    _label = label;
    _active = active;
    _changed = !*active;
}

void OptionButton::renderHUD(const Size & screenSize) {
    if (*_active && !_changed) {
        Font font = _label -> getFont();
        font.setColor(ColorRGB(0.0f, 1.0f, 0.0f));
        _label -> setText("V");
        _label -> setFont(font);
        _label -> rebuild();
        _changed = *_active;
    } else if (!*_active && _changed) {
        Font font = _label -> getFont();
        font.setColor(ColorRGB(1.0f, 0.0f, 0.0f));
        _label -> setText("X");
        _label -> setFont(font);
        _label -> rebuild();
        _changed = *_active;
    }
    MaintitleHoverButton::renderHUD(screenSize);
}
