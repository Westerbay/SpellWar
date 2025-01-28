/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __STOCHASTIC_RULES__
#define __STOCHASTIC_RULES__
 
#include <string>
#include <map>
#include <set>
#include <utility>
 
class StochasticRules {
public:
	StochasticRules() = default;
	StochasticRules(std::map<char, std::set<std::pair<std::string, double>>> rules);
	void add(char predecessor, std::string successor, double probability);
	std::string randomSuccessor(char predecessor);
private:
	std::map<char, std::set<std::pair<std::string, double>>> _rules;
};
 
#endif
 
