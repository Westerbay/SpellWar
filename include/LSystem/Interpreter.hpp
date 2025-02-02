/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __LSYSTEM_INTERPRETER__
#define __LSYSTEM_INTERPRETER__

#include <LSystem/LSystem.hpp>
#include <LSystem/Turtle.hpp>

#include <unordered_map>

#define FORWARD_TOKEN 'F'

#define PUSH_TOKEN '['
#define POP_TOKEN ']'

#define TURN_LEFT_TOKEN '+'
#define TURN_RIGHT_TOKEN '-'
#define PITCH_DOWN_TOKEN '&'
#define PITCH_UP_TOKEN '^'
#define ROLL_LEFT_TOKEN '\\' 
#define ROLL_RIGHT_TOKEN '/'
#define TURN_AROUND_TOKEN '|'

class Interpreter {
public:
	Interpreter(LSystem * system, Turtle * turtle);
	~Interpreter();
	void systemToWorld(std::string word);
private:
	LSystem * _system;
	Turtle * _turtle;
	std::unordered_map<char, Rotation> _tokenToRotation;
};

#endif

