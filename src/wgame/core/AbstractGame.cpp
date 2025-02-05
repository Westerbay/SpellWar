/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/AbstractGame.hpp>
#include <SDL3/SDL.h>


namespace wgame {

AbstractGame::AbstractGame(unsigned tps) : _running(false) {
    setTPS(tps);
}

void AbstractGame::setTPS(unsigned tps) {
    _updateDelay = 1000 / tps;
}

void AbstractGame::start() {
    _running = true;
    while (_running) {
        Uint32 updateStart = SDL_GetTicks();
        update();
        Uint32 updateTime = SDL_GetTicks() - updateStart;
        if (updateTime < _updateDelay) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(_updateDelay - updateTime)
            );
        }
    }
}

void AbstractGame::stop() {
    _running = false;
}

}

