/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */
 
#include <MainFrame.hpp>

#include <iostream>
#include <stdexcept>

MainFrame::MainFrame(const char * title, const Size & size) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error(std::string("Error SDL : ") + SDL_GetError());		
	}
	
	_mainFrame = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		size.width, size.height,
		SDL_WINDOW_OPENGL
	);
	if (!_mainFrame) {
		SDL_Quit();
		throw std::runtime_error(std::string("Error creating window : ") + SDL_GetError());	
	}
	
	_glContext = SDL_GL_CreateContext(_mainFrame);
	if (!_glContext) {
		SDL_DestroyWindow(_mainFrame);
		SDL_Quit();
		throw std::runtime_error(std::string("Error creating GL context : ") + SDL_GetError());
	}
	
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		SDL_GL_DeleteContext(_glContext);
		SDL_DestroyWindow(_mainFrame);
		SDL_Quit();
		throw std::runtime_error("Error init GLEW");
	}
}

MainFrame::~MainFrame() {
	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_mainFrame);
	SDL_Quit();
}

void MainFrame::run() {
	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}
	}
	SDL_GL_SwapWindow(_mainFrame);
}
