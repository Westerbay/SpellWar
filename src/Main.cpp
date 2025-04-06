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

#include <spellwar/core/MainFrame.hpp>
#include <spellwar/core/Game.hpp>
#include <wgame/wgame.hpp>
 
int main(int argc, char * argv[]) {
	srand((unsigned int) time(nullptr));

	MainFrame * mainFrame;
	if (argc == 3) {
		try {
			unsigned width = std::stoi(argv[1]);
			unsigned height = std::stoi(argv[2]);
			mainFrame = new MainFrame({width, height});
		}
		catch (const std::invalid_argument &) {
			std::cerr << "Wrong format, try unsigned sizes." << std::endl;
			return EXIT_FAILURE;
		}
	}
	else if (argc == 1) {
		mainFrame = new MainFrame();
	}
	else {
		std::cerr << "No arguments → fullscreen; otherwise, you must provide two positive integers for width and height, respectively." << std::endl;
		return EXIT_FAILURE;
	}
	 
	Game * game = new Game();
	GameEngine gameEngine(game, mainFrame);
	gameEngine.start();
	return EXIT_SUCCESS;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main(1, NULL);
}
#endif
