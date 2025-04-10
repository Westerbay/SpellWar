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
    GameLight * light = getLight();
    _world = new World(getCamera(), light);
    _mainTitle = new Maintitle(this, _world, light -> getInfo());
    _world -> setMaintitle(_mainTitle);
    addGameObject(_world);
    addGameObject(_mainTitle);
}
