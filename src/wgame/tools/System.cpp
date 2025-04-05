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
float System::_sensibility = DEFAULT_SENSIBILITY;
bool System::_lastMousePressed[2] = {false, false};
std::queue<Event> System::_events = std::queue<Event>();

void System::initContext(GLFWwindow * frame) {
    _frame = frame;
}

float System::getSensibility() {
    return _sensibility;
}

void System::record() {
    double mouseX;
    double mouseY;
    _lastMousePosition = _mousePosition;
    glfwGetCursorPos(_frame, &mouseX, &mouseY);
    _mousePosition.x = (float) mouseX;
    _mousePosition.y = (float) mouseY;
}

void System::resetMousePosition() {
    record();
    _lastMousePosition = _mousePosition;
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

bool System::isKeyReleased(Key key) {
    return glfwGetKey(_frame, key) == RELEASE;
}

bool System::isMousePressed(Mouse mouse) {
    return glfwGetMouseButton(_frame, mouse) == PRESS;
}

bool System::isMouseReleased(Mouse mouse) {
    int state = glfwGetMouseButton(_frame, mouse);
    if (state == RELEASE && _lastMousePressed[mouse]) {
        _lastMousePressed[mouse] = false;
        return true;
    }
    _lastMousePressed[mouse] = state == PRESS;
    return false;
}

void System::setSensibility(float sensibility) {
    _sensibility = sensibility;
}

std::queue<Event> & System::getEvents() {
    return _events;
}

void System::postEvent(Event event) {
    _events.push(event);
}

}
