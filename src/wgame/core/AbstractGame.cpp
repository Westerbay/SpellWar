/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/AbstractGame.hpp>


namespace wgame {

AbstractGame::AbstractGame(unsigned tps) : _running(false) {
    setTPS(tps);
}

void AbstractGame::setTPS(unsigned tps) {
    _updateDelay = 1000 / tps;
}

void AbstractGame::setWord(GameObjectGroup & world) {
    _world = &world;
}

void AbstractGame::start() {
	using namespace std::chrono;
    _running = true;
    while (_running) {
        steady_clock::time_point updateStart = std::chrono::steady_clock::now();
        
        updateWorld();
        
        steady_clock::time_point updateEnd = std::chrono::steady_clock::now();
		unsigned updateTime = duration_cast<milliseconds>(updateEnd - updateStart).count();
        if (updateTime < _updateDelay) {
            std::this_thread::sleep_for(
                milliseconds(_updateDelay - updateTime)
            );
        }
    }
}

void AbstractGame::stop() {
    _running = false;
}

void AbstractGame::addToWorld(GameObject * gameObject) {
    _world -> add(gameObject);
}

void AbstractGame::removeFromWorld(GameObject * gameObject) {
    _world -> remove(gameObject);
}

void AbstractGame::updateWorld() {
    _world -> update();
}

}

