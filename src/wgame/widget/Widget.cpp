/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/widget/Widget.hpp>


namespace wgame {

Widget::Widget() {
    _horizontalResponsive = false;
    _scale = 1.0f;
}

void Widget::setDesignedSize(const Size & designedSize) {
    _designedSize = designedSize;
}

void Widget::setHorizontalResponsive(bool enable) {
    _horizontalResponsive = enable;
}

void Widget::resize(const Size & size) {
    float scale;
    if (_horizontalResponsive) {
        scale = (float) size.width / _designedSize.width;
    }
    else {
        scale = 1.0f;
    }
    if (_scale != scale) {
        _scale = scale;
        rebuild();
    }
    else {
        _scale = scale;
    }
}
    
bool Widget::hover() {
    return hitbox.contains(_system.getMousePosition());
}

bool Widget::triggered() {
    return hover() && _system.isMouseReleased(MOUSE_BUTTON_LEFT);
}

}

