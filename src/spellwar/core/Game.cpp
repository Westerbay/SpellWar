/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <spellwar/core/Game.hpp>
#include <spellwar/world/Platform.hpp>

Game::Game(unsigned tps) : AbstractGame(tps) {}

void Game::init() {
    Cuboid cuboid(Point3D(0.0f, 0.0f, 0.0f), Point3D(0.5f, 0.5f, 0.5f));
    cuboid.rotate(glm::radians(45.0f), AXIS_XY);
    addToWorld(new Platform(cuboid));
}

