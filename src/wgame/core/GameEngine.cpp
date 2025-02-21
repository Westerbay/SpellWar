/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameEngine.hpp>


namespace wgame {

GameEngine::GameEngine(AbstractGame * game, AbstractFrame * frame) {
    _game = game;
    _frame = frame;
    _camera = new GameCamera();
    _world = new GameObjectGroup();
}

GameEngine::~GameEngine() {
    delete _camera;
    delete _world;
    delete _game;
    delete _frame;
}

void GameEngine::gameLoop(AbstractGame * game) {
    game -> start();
}

void GameEngine::start() {
    _game -> initWorld(_world);
    _frame -> initWorld(_world);

    _game -> initCamera(_camera);
    _frame -> initCamera(_camera);

    _game -> init();
    _game -> updateWorld();
    std::thread gameThread(gameLoop, _game);
    _frame -> start();

    _game -> stop();
    gameThread.join();
}

}

