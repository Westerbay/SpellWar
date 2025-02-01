/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <StochasticRules.hpp>

void StochasticRules::add(char predecessor, std::string successor, double probability) {
	std::pair<std::string, double> pair(successor, probability);
	_rules[predecessor].insert(pair);
}

std::string StochasticRules::nextSuccessor(char predecessor) {
	double probability = rand() / (double) RAND_MAX;
	for (std::pair<std::string, double> pair : _rules[predecessor]) {
		if (probability < pair.second) {
			return pair.first;
		}
		probability -= pair.second;
	}
	std::string successor(1, predecessor);
	return successor;
}

