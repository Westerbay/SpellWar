/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/scene/World.hpp>


World::World(GameCamera * camera, GameLight * light) : Scene() {
    _active = false;
    AbstractBiome * biome = new Space(light);
    add(biome);

    Hitbox mapHitbox(Point3D(0.0f), MAP_SIZE);
    Map * map = new Map(mapHitbox, biome);
    map -> generatePlatform(
        MAX_NUMBER_OF_PLATFORMS, 
        MIN_PLATFORM_SIZE, 
        MAX_PLATFORM_SIZE
    );
    add(map);

    _player = new Player(map);
    add(_player);
    
    camera -> setFarPlane(FAR_PLANE);
    camera -> attachGameObject(_player -> getCameraObject());
    update();
}

void World::setMaintitle(Scene * maintitle) {
    _maintitle = maintitle;
}

void World::setActive(bool active) {
    _player -> setActive(active);
    _active = active;
}

void World::update() {
    if (_active) {        
        if (_system.isKeyPressed(KEY_ESCAPE)) {
            setActive(false);
            _maintitle -> setActive(true);
            _system.postEvent(IN_MAINTITLE_EVENT);
        }
        Scene::update();
    }    
}

