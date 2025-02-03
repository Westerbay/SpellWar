/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __LSYSTEM__
#define __LSYSTEM__

#include <spellwar/spell/Rules.hpp>

class LSystem {
public:
	LSystem(std::string axiom, Rules * rules, unsigned numberOfIteration);
	~LSystem();
	std::string generate();
private:
	std::string _axiom;
	Rules * _rules;
	unsigned _numberOfIteration;
};

#endif

