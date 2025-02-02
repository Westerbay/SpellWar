/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <LSystem/Turtle.hpp>
#include <glm/gtc/matrix_transform.hpp>

Turtle::Turtle(const TurtleState & state, float angle, float length) : 
	_state(state), _length(length) {
	_rotationMatrix[TURN_LEFT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[TURN_RIGHT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[PITCH_DOWN] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[PITCH_UP] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[ROLL_LEFT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[ROLL_RIGHT] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(-angle), glm::vec3(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[TURN_AROUND] = glm::mat3(glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
}

void Turtle::rotate(Rotation rotation) {
    _state.heading = _state.heading * _rotationMatrix[rotation];
}

void Turtle::forward() {
	_lines.push_back(_state.position);
	_state.position += _state.heading[0] * _length;
	_lines.push_back(_state.position);
}

void Turtle::pop() {
	_state = _stackStates.top();
	_stackStates.pop();
}

void Turtle::push() {
	_stackStates.push(_state);
}

std::vector<glm::vec3> & Turtle::getLines() {
	return _lines;
}

void Turtle::reset(const TurtleState & state) {
	_state = state;
	_lines = std::vector<glm::vec3>();
}

