/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <LSystem/Interpreter.hpp>
#include <glm/gtc/matrix_transform.hpp>

Interpreter::Interpreter(LSystem * system, Turtle * turtle) :
	_system(system), _turtle(turtle) {
	_tokenToRotation[TURN_LEFT_TOKEN] = TURN_LEFT;
	_tokenToRotation[TURN_RIGHT_TOKEN] = TURN_RIGHT;
	_tokenToRotation[PITCH_DOWN_TOKEN] = PITCH_DOWN;
	_tokenToRotation[PITCH_UP_TOKEN] = PITCH_UP;
	_tokenToRotation[ROLL_LEFT_TOKEN] = ROLL_LEFT;
	_tokenToRotation[ROLL_RIGHT_TOKEN] = ROLL_RIGHT;
	_tokenToRotation[TURN_AROUND_TOKEN] = TURN_AROUND;
}

Interpreter::~Interpreter() {
	delete _system;
	delete _turtle;
}

void Interpreter::systemToWorld() {
	std::string word = _system -> generate();
	for (char token : word) {
		switch (token) {
			case FORWARD_TOKEN:
				_turtle -> forward();
				break;
			case PUSH_TOKEN:
				_turtle -> push();
				break;
			case POP_TOKEN:
				_turtle -> pop();
				break;
			case TURN_LEFT_TOKEN:
			case TURN_RIGHT_TOKEN:
			case PITCH_DOWN_TOKEN:
			case PITCH_UP_TOKEN:
			case ROLL_LEFT_TOKEN:
			case ROLL_RIGHT_TOKEN:
			case TURN_AROUND_TOKEN:
				_turtle -> rotate(_tokenToRotation[token]);
				break;
		}
	}		
}
