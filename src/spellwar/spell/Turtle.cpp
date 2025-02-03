/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/spell/Turtle.hpp>


Turtle::Turtle(const TurtleState & state, float angle, float length) : 
	_state(state), _length(length) {
	_rotationMatrix[TURN_LEFT] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), Vector3D(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[TURN_RIGHT] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(-angle), Vector3D(0.0f, 0.0f, 1.0f)));
	_rotationMatrix[PITCH_DOWN] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), Vector3D(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[PITCH_UP] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(-angle), Vector3D(0.0f, 1.0f, 0.0f)));
	_rotationMatrix[ROLL_LEFT] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(angle), Vector3D(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[ROLL_RIGHT] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(-angle), Vector3D(1.0f, 0.0f, 0.0f)));
	_rotationMatrix[TURN_AROUND] = Matrix3D(glm::rotate(Matrix4D(1.0f), glm::radians(180.0f), Vector3D(0.0f, 0.0f, 1.0f)));
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

std::vector<Point3D> & Turtle::getLines() {
	return _lines;
}

void Turtle::reset(const TurtleState & state) {
	_state = state;
	_lines = std::vector<Point3D>();
}

