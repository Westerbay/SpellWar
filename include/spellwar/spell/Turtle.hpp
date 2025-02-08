/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __LSYSTEM_TURTLE__
#define __LSYSTEM_TURTLE__

#include <wgame/wgame.hpp>

#include <unordered_map>
#include <stack>
#include <vector>


using namespace wgame;

typedef enum {
    TURN_LEFT,
    TURN_RIGHT,
    PITCH_DOWN,
    PITCH_UP,
    ROLL_LEFT,
    ROLL_RIGHT,
    TURN_AROUND
} Rotation;

typedef struct {
    Point3D position;
	Matrix3D heading;
    float length;
} TurtleState;

class Turtle {
public:
    Turtle(const TurtleState & state, float angle, float length);
    void rotate(Rotation rotation);
    void forward();
	void pop();
	void push();
    std::vector<Point3D> & getLines();
    void reset(const TurtleState & state);
private:
    float _length;
    TurtleState _state;
    std::unordered_map<Rotation, glm::mat3> _rotationMatrix;
	std::stack<TurtleState> _stackStates;
    std::vector<Point3D> _lines;
};

#endif
