/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/system/Inputs.hpp>


namespace wgame {

GLFWwindow * Inputs::_frame = nullptr;

void Inputs::initContext(GLFWwindow * frame) {
    _frame = frame;
}

bool Inputs::isKeyPressed(Key key) {
    return glfwGetKey(_frame, key) == PRESS;
}

}
