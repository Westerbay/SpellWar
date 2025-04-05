/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/widget/Widget.hpp>


namespace wgame {
    
bool Widget::hover() {
    return hitbox.contains(_system.getMousePosition());
}

bool Widget::triggered() {
    return hover() && _system.isMouseReleased(MOUSE_BUTTON_LEFT);
}

}

