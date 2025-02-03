/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 

#include <spellwar/spell/LSystem.hpp>


LSystem::LSystem(std::string axiom,	Rules * rules, unsigned numberOfIteration) : 
	_axiom(axiom), _rules(rules), _numberOfIteration(numberOfIteration) {}
	
LSystem::~LSystem() {
	delete _rules;
}

std::string LSystem::generate() {
	std::string word = _axiom;
	for (unsigned i = 0; i < _numberOfIteration; i ++) {
		std::string stringBuilder = "";
		for (char predecessor : word) {
			stringBuilder += _rules -> nextSuccessor(predecessor);
		}
		word = stringBuilder;
	}
	return word;
}

