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
    _characters = {&_flame, &_frost};
    _characterIndex = 0;
    _light = light;

    AbstractBiome * biome = new Space(light);
    add(biome);

    Hitbox mapHitbox(Point3D(0.0f), MAP_SIZE);
    Map * map = new Map(mapHitbox, biome);    
    add(map);

    _player = new Player(map, _characters[_characterIndex]);
    add(_player);

    map -> generatePlatform(
        _player -> getCameraObject(),
        MAX_NUMBER_OF_PLATFORMS, 
        MIN_PLATFORM_SIZE, 
        MAX_PLATFORM_SIZE
    );
    _player -> spawn();
    
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
    _player -> updateCamera();
}

void World::nextCharacter() {
    _characterIndex = (_characterIndex + 1) % _characters.size();
    _player -> setCharacter(_characters[_characterIndex]);
}

void World::previousCharacter() {
    _characterIndex = ((int) _characters.size() + _characterIndex - 1) % _characters.size();
    _player -> setCharacter(_characters[_characterIndex]);
}

void World::setActiveLight(bool active) {
    _light -> setDisplayLight(active);
    if (!active) {
        _light -> setActiveParallaxMapping(false);
        _light -> setActiveNormalMap(false);
    }
}

void World::setActiveNormalMap(bool active) {
    _light -> setActiveNormalMap(active);
    if (!active) {
        _light -> setActiveParallaxMapping(false);
    }
}

void World::setActiveParallaxMapping(bool active) {
    _light -> setActiveParallaxMapping(active);
}

