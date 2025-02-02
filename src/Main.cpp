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

#include <LSystem/LSystem.hpp>
#include <LSystem/Interpreter.hpp>
#include <LSystem/Turtle.hpp>
#include <LSystem/StochasticRules.hpp>
#include <WindowGL/MainFrame.hpp>
 
int main() {

	srand(time(NULL));
	StochasticRules * rules = new StochasticRules;
	rules -> add('F', "F", 0.33);
	rules -> add('F', "F[-F]", 0.33);
	rules -> add('F', "F[+F]", 0.33);
	LSystem * system = new LSystem("F", rules, 5);
	
	glm::vec3 position = {0.0f, 0.0f, 0.0f};
	glm::mat3 heading(1.0f);
	TurtleState turtleState = {position, heading};
	float angle = 60.0f;
	Turtle * turtle = new Turtle(turtleState, angle, 10.0f);
	Interpreter interpreter(system, turtle);
	interpreter.systemToWorld();
	std::cout << "END" << std::endl;

	MainFrame mainFrame("Application", {800, 800});
	mainFrame.run();
	return EXIT_SUCCESS;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main();
}
#endif
