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
