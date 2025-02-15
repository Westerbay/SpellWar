/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __INPUTS_H__
#define __INPUTS_H__

#include <GLFW/glfw3.h>
#include "Keys.hpp"

#define PRESS GLFW_PRESS


namespace wgame {

typedef int Key;

class Inputs {
public:
    static void initContext(GLFWwindow * frame);
    bool isKeyPressed(Key key);
private:
    static GLFWwindow * _frame;    
};

}


#endif
