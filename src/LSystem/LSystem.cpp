/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <LSystem.hpp>

LSystem::LSystem(std::string axiom,	Rules * rules) 
: _axiom(axiom), _rules(rules) {}
	
std::string LSystem::generate(unsigned numberOfIteration) {
	std::string word = _axiom;
	for (unsigned i = 0; i < numberOfIteration; i ++) {
		std::string stringBuilder = "";
		for (char predecessor : word) {
			stringBuilder += _rules -> nextSuccessor(predecessor);
		}
		word = stringBuilder;
	}
	return word;
}

