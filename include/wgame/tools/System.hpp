/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_SYSTEM_H__
#define __WG_SYSTEM_H__

#include <GLFW/glfw3.h>

#include "Keys.hpp"
#include "../geometry/Geometry.hpp"

#define PRESS GLFW_PRESS


namespace wgame {

typedef int Key;

class System {
public:
    static void initContext(GLFWwindow * frame);
    static void record();
    static double getTime();
    static Point2D getMousePosition();
    static Vector2D getMouseMovement();
    static bool isKeyPressed(Key key); 
private:
    static GLFWwindow * _frame;
    static Point2D _mousePosition;
    static Vector2D _lastMousePosition;
};

}


#endif
