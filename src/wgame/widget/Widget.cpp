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

float Widget::getScale(const Size & size) {
    if (_horizontalResponsive) {
        _scale = (float) size.width / _designedSize.width;
    }
    else {
        _scale = 1.0f;
    }
    return _scale;
}
    
bool Widget::hover() {
    Hitbox scaledHitbox = hitbox;
    scaledHitbox.position *= _scale;
    scaledHitbox.size *= _scale;
    return scaledHitbox.contains(_system.getMousePosition());
}

bool Widget::triggered() {
    return hover() && _system.isMouseReleased(MOUSE_BUTTON_LEFT);
}

}

