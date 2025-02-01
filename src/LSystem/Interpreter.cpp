/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <Interpreter.hpp>
#include <glm/gtc/matrix_transform.hpp>

Interpreter::Interpreter(const Turtle & turtle, float angle, unsigned numberOfIterations) :
	_turtle(turtle),
	_numberOfIterations(numberOfIterations)
{
	_rotationMatrix[TURN_LEFT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[TURN_RIGHT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[PITCH_DOWN] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[PITCH_UP] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[ROLL_LEFT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[ROLL_RIGHT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[TURN_AROUND] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
}

void Interpreter::systemToWorld(LSystem & system) {
	std::string word = system.generate(_numberOfIterations);
	for (char token : word) {
		switch (token) {
			case FORWARD:
				forward();
				break;
			case PUSH:
				push();
				break;
			case POP:
				pop();
				break;
			case TURN_LEFT:
			case TURN_RIGHT:
			case PITCH_DOWN:
			case PITCH_UP:
			case ROLL_LEFT:
			case ROLL_RIGHT:
			case TURN_AROUND:
				_turtle.heading = _turtle.heading * _rotationMatrix[token];
				break;
		}
	}		
}

std::queue<Line> & Interpreter::getLines() {
	return _lines;
}

void Interpreter::reset(const Turtle & turtle) {
	_turtle = turtle;
}

void Interpreter::forward() {
	Line line;
	line.firstPoint = _turtle.position;
	_turtle.position += _turtle.heading[0] * LENGTH;
	line.secondPoint = _turtle.position;
	_lines.push(line);
}

void Interpreter::pop() {
	_turtle = _turtleStack.top();
	_turtleStack.pop();
}

void Interpreter::push() {
	_turtleStack.push(_turtle);
}

