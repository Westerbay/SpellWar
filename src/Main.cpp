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
 
int main() {
	srand((unsigned int) time(nullptr));
	MainFrame * mainFrame = new MainFrame("Application", {1280, 720});
	Game * game = new Game();
	GameEngine gameEngine(game, mainFrame);
	gameEngine.start();
	return EXIT_SUCCESS;
}

#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main();
}
#endif
