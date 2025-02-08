/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/gui/AbstractFrame.hpp>

#include <stdexcept>


namespace wgame {

AbstractFrame::AbstractFrame(const char * title, const Size & size, unsigned fps) : _running(false) {
	initSDL(title, size);
	setFPS(fps);
}

void AbstractFrame::initSDL(const char * title, const Size & size) {
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		throw std::runtime_error(std::string("Error SDL : ") + SDL_GetError());		
	}
	_mainFrame = SDL_CreateWindow(
		title,
		size.width, size.height,
		SDL_WINDOW_OPENGL
	);
	if (!_mainFrame) {
		throw std::runtime_error(std::string("Error creating window : ") + SDL_GetError());	
	}
	_glContext = SDL_GL_CreateContext(_mainFrame);
	if (!_glContext) {
		throw std::runtime_error(std::string("Error creating GL context : ") + SDL_GetError());
	}
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Error init GLEW");
	}
}

void AbstractFrame::setFPS(unsigned fps) {
	_frameDelay = 1000 / fps;
}

AbstractFrame::~AbstractFrame() {
	SDL_GL_DestroyContext(_glContext);
	SDL_DestroyWindow(_mainFrame);
	SDL_Quit();
}

void AbstractFrame::start() {
	SDL_Event event;
	_running = true;
	while (_running) {
        Uint64 frameStart = SDL_GetTicks();		
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
				stop();
				return;
            }
        }
		glClear(GL_COLOR_BUFFER_BIT);
        render();
		SDL_GL_SwapWindow(_mainFrame);
        Uint64 frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < _frameDelay) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(_frameDelay - frameTime)
            );
        }
    }
}

void AbstractFrame::stop() {
	_running = false;
}

void AbstractFrame::addSprite(Sprite * sprite) {
	_group.add(sprite);
}

void AbstractFrame::removeSprite(Sprite * sprite) {
	_group.remove(sprite);
}

void AbstractFrame::displaySprites() {
	_group.render();
}

};

