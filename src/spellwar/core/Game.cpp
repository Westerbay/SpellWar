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
    getLight() -> setDisplayLight(1);
    getLight() -> setPosition(Point3D(5.0f, 0.0f, -1.0f));
    getLight() -> setAmbientLighting(0.2f);
    getLight() -> setSpecularFactor(0.5f);
    getLight() -> setSpecularExponent(8);

    addToWorld(new World(getCamera()));
}

