/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/GameObjectGroup.hpp>


namespace wgame {

GameObjectGroup::~GameObjectGroup() {
    for (GameObject * gameObject : _objects) {
        delete gameObject;
    }
}

void GameObjectGroup::add(GameObject * gameObject) {
    _objects.insert(gameObject);
}

void GameObjectGroup::remove(GameObject * gameObject) {
    _objects.erase(gameObject);
}

void GameObjectGroup::update() {
    for (GameObject * gameObject : _objects) {
        gameObject -> update();
    }
}

void GameObjectGroup::render() {
    for (GameObject * gameObject : _objects) {
        gameObject -> render();
    }
}

void GameObjectGroup::renderBackground() {
    for (GameObject * gameObject : _objects) {
        gameObject -> renderBackground();
    }
}

void GameObjectGroup::renderHUD() {
    for (GameObject * gameObject : _objects) {
        gameObject -> renderHUD();
    }
}

};
