/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/AbstractGame.hpp>
#include <wgame/tools/Inputs.hpp>


namespace wgame {

AbstractGame::AbstractGame(unsigned tps) : _running(false) {
    setTPS(tps);
    _world = nullptr;
    _camera = nullptr;
}

void AbstractGame::setTPS(unsigned tps) {
    _updateDelay = 1000 / tps;
}

GameCamera * AbstractGame::getCamera() {
    return _camera;
}

void AbstractGame::initWorld(GameObjectGroup & world) {
	if (_world != nullptr) {
		throw std::runtime_error("World already initialized ! ");
	}
	_world = &world;
}
void AbstractGame::initCamera(GameCamera & camera) {
	if (_camera != nullptr) {
		throw std::runtime_error("Camera already initialized ! ");
	}
	_camera = &camera;
}

void AbstractGame::start() {
	using namespace std::chrono;
    _running = true;
    while (_running) {
        steady_clock::time_point updateStart = std::chrono::steady_clock::now();
        
        Inputs::record();
        updateWorld();
        _camera -> update();
        
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

