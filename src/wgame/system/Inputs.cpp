/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/system/Inputs.hpp>
#include <iostream>


namespace wgame {

GLFWwindow * Inputs::_frame = nullptr;
Point2D Inputs::_mousePosition = Point2D(0.0f);
Point2D Inputs::_lastMousePosition = Point2D(0.0f);

void Inputs::initContext(GLFWwindow * frame) {
    _frame = frame;
}

void Inputs::mouseRecord() {
    double mouseX;
    double mouseY;
    _lastMousePosition = _mousePosition;
    glfwGetCursorPos(_frame, &mouseX, &mouseY);
    _mousePosition.x = (float) mouseX;
    _mousePosition.y = (float) mouseY;
}

Point2D Inputs::getMousePosition() const {
    return _mousePosition;
}

Vector2D Inputs::getMouseMovement() const {
    return _lastMousePosition - _mousePosition;
}

bool Inputs::isKeyPressed(Key key) const {
    return glfwGetKey(_frame, key) == PRESS;
}

}
