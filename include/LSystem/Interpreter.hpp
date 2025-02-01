/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __LSYSTEM_INTERPRETER__
#define __LSYSTEM_INTERPRETER__

#include <glm/glm.hpp>
#include <LSystem.hpp>

#include <unordered_map>
#include <stack>
#include <queue>

#define FORWARD 'F'

#define PUSH '['
#define POP ']'

#define TURN_LEFT '+'
#define TURN_RIGHT '-'
#define PITCH_DOWN '&'
#define PITCH_UP '^'
#define ROLL_LEFT '\\' 
#define ROLL_RIGHT '/'
#define TURN_AROUND '|'

#define LENGTH 10.0f


typedef struct {
	glm::vec3 position;
	glm::mat3 heading;
} Turtle;

typedef struct {
	glm::vec3 firstPoint;
	glm::vec3 secondPoint;
} Line;


class Interpreter {
public:
	Interpreter(const Turtle & turtle, float angle, unsigned numberOfIterations);
	void systemToWorld(LSystem & system);
	std::queue<Line> & getLines();
	void reset(const Turtle & turtle);
private:
	void forward();
	void pop();
	void push();
	
	Turtle _turtle;
	std::unordered_map<char, glm::mat3> _rotationMatrix;
	std::stack<Turtle> _turtleStack;
	std::queue<Line> _lines;
	unsigned _numberOfIterations;
};

#endif

