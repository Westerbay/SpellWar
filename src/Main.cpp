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

#include <LSystem.hpp>
#include <Interpreter.hpp>
#include <StochasticRules.hpp>
#include <MainFrame.hpp>
 
int main() {
	
	MainFrame mainFrame("Application", {400, 400});
	mainFrame.run();

	/*srand(time(NULL));
	StochasticRules rules;
	rules.add('F', "F", 0.33);
	rules.add('F', "F[-F]", 0.33);
	rules.add('F', "F[+F]", 0.33);
	LSystem system("F", &rules);
	
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::mat3 heading(1.0f);
	Turtle turtle = {position, heading};
	float angle = 60.0f;
	Interpreter interpreter(turtle, angle, 5);
	interpreter.systemToWorld(system);*/
	std::cout << "END" << std::endl;
	return EXIT_SUCCESS;
}
