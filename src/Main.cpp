/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <StochasticLSystem.hpp>
 
int main() {
	srand(time(NULL));
	StochasticRules rules;
	rules.add('F', "F", 0.33);
	rules.add('F', "F[-F]", 0.33);
	rules.add('F', "F[+F]", 0.33);
	StochasticLSystem system("F", rules, 5);
	std::cout << system.generate() << std::endl;
	return EXIT_SUCCESS;
}
