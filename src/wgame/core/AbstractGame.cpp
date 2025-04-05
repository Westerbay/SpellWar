/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/AbstractGame.hpp>
#include <wgame/tools/System.hpp>


namespace wgame {

AbstractGame::AbstractGame(unsigned tps) : _running(true) {
    setTPS(tps);
    _world = nullptr;
    _camera = nullptr;
    _light = nullptr;
}

unsigned AbstractGame::getUpdateDelay() const {
    return _updateDelay;
}

void AbstractGame::setTPS(unsigned tps) {
    _updateDelay = 1000 / tps;
}

GameCamera * AbstractGame::getCamera() {
    return _camera;
}

GameLight * AbstractGame::getLight() {
    return _light;
}

bool AbstractGame::isRunning() const {
	return _running;
}

void AbstractGame::stop() {
	_running = false;
}

void AbstractGame::initWorld(GameObjectGroup * world) {
	if (_world != nullptr) {
		throw std::runtime_error("World already initialized ! ");
	}
	_world = world;
}

void AbstractGame::initCamera(GameCamera * camera) {
	if (_camera != nullptr) {
		throw std::runtime_error("Camera already initialized ! ");
	}
	_camera = camera;
}

void AbstractGame::initLight(GameLight * light) {
	if (_light != nullptr) {
		throw std::runtime_error("Light already initialized ! ");
	}
	_light = light;
}

void AbstractGame::addGameObject(GameObject * gameObject) {
    _world -> add(gameObject);
}

void AbstractGame::removeGameObject(GameObject * gameObject) {
    _world -> remove(gameObject);
}

void AbstractGame::update() {
    _world -> update();
}

}

