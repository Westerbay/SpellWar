/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/widget/Button.hpp>


namespace wgame {

Button::Button() : Label() {
    _action = [](){};
}

Button * Button::createButton() {
    return new Button();
}

void Button::setAction(const std::function<void()> & action) {
    _action = action;
}

void Button::update() {
    if (triggered()) {
        _action();
    }
}

ButtonBuilder::ButtonBuilder() : Button() {}

Button * ButtonBuilder::build() {
    Button * newButton = createButton();
    newButton -> setHorizontalResponsive(_horizontalResponsive);
    newButton -> setDesignedSize(_designedSize);
    newButton -> setText(_text);
    newButton -> setPosition(_position);
    newButton -> setAction(_action);
    newButton -> setFont(_font);
    newButton -> rebuild();
    return newButton;
}

}

