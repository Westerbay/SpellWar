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
#include <queue>

#include "Inputs.hpp"
#include "../geometry/Geometry.hpp"

#define DEFAULT_SENSIBILITY 0.2f


namespace wgame {

typedef int Key;
typedef int Mouse;
typedef int Event;

class System {
public:
    static void initContext(GLFWwindow * frame);
    static void record();
    static double getTime();
    static float getSensibility();
    static Point2D getMousePosition();
    static Vector2D getMouseMovement();
    static bool isKeyPressed(Key key); 
    static bool isKeyReleased(Key key); 
    static bool isMousePressed(Mouse mouse); 
    static bool isMouseReleased(Mouse mouse);
    static void setSensibility(float sensibility);
    static std::queue<Event> & getEvents(); 
    static void postEvent(Event event);
    static void resetMousePosition();
private:
    static GLFWwindow * _frame;
    static Point2D _mousePosition;
    static Vector2D _lastMousePosition;
    static float _sensibility;
    static std::queue<Event> _events;
    static bool _lastMousePressed[2];
};

}


#endif
