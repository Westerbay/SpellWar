/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameEngine.hpp>


namespace wgame {

GameEngine::GameEngine(AbstractGame * game, AbstractFrame * frame) : 
    _game(game), _frame(frame), _running(false) {}

GameEngine::~GameEngine() {
    delete _game;
    delete _frame;
}

bool GameEngine::isRunning() const {
    return _running;
}

static void gameLoop(AbstractGame * game) {
    game -> start();
}

static void eventLoop(GameEngine * engine) {
    SDL_Event event;
    while (engine -> isRunning()) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                engine -> exit();
            }
        }
        std::this_thread::sleep_for(
            std::chrono::milliseconds(1)
        );
    }
}

void GameEngine::start() {

    std::thread gameThread(gameLoop, _game);
    std::thread eventThread(eventLoop, this);
    _running = true;
    _frame -> start();
    gameThread.join();
    eventThread.join();

}

void GameEngine::pause() {
    _frame -> stop();
    _game -> stop();
}

void GameEngine::exit() {
    pause();
    _running = false;
}

}

