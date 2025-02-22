/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/tools/System.hpp>
#include <iostream>


namespace wgame {

GLFWwindow * System::_frame = nullptr;
Point2D System::_mousePosition = Point2D(0.0f);
Point2D System::_lastMousePosition = Point2D(0.0f);

void System::initContext(GLFWwindow * frame) {
    _frame = frame;
}

void System::record() {
    double mouseX;
    double mouseY;
    _lastMousePosition = _mousePosition;
    glfwGetCursorPos(_frame, &mouseX, &mouseY);
    _mousePosition.x = (float) mouseX;
    _mousePosition.y = (float) mouseY;
}

double System::getTime() {
    return glfwGetTime();
}

Point2D System::getMousePosition() {
    return _mousePosition;
}

Vector2D System::getMouseMovement() {
    return _lastMousePosition - _mousePosition;
}

bool System::isKeyPressed(Key key) {
    return glfwGetKey(_frame, key) == PRESS;
}

}
