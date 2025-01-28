/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#ifndef __STOCHASTIC_L_SYSTEM__
#define __STOCHASTIC_L_SYSTEM__
 
#include <StochasticRules.hpp>
 
class StochasticLSystem {
public:
	StochasticLSystem(
		std::string axiom,
		StochasticRules rules, 
		unsigned numberOfIteration
	);
	std::string generate();
private:
	std::string _axiom;
	StochasticRules _rules;
	unsigned _numberOfIteration;
};
 
#endif
 
