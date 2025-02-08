/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/core/EntityGroup.hpp>


namespace wgame {

EntityGroup::~EntityGroup() {
    for (Entity * entity : _entities) {
        delete entity;
    }
}

void EntityGroup::add(Entity * entity) {
    _entities.insert(entity);
}

void EntityGroup::remove(Entity * entity) {
    _entities.erase(entity);
}

void EntityGroup::update() {
    for (Entity * entity : _entities) {
        entity -> update();
    }
}

};
