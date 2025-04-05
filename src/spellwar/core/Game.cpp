/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/core/Game.hpp>


Game::Game(unsigned tps) : AbstractGame(tps) {}

void Game::init() {
    _world = new World(getCamera(), getLight());
    _mainTitle = new Maintitle(this, _world);
    _world -> setMaintitle(_mainTitle);
    addGameObject(_world);
    addGameObject(_mainTitle);
}
