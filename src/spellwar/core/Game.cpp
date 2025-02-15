/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */

#include <spellwar/core/Game.hpp>
#include <spellwar/world/Platform.hpp>
#include <spellwar/world/Player.hpp>

Game::Game(unsigned tps) : AbstractGame(tps) {}

void Game::init() {
    Cuboid cuboid(Point3D(0.0f, 0.0f, -2.0f), Vector3D(0.5f, 0.5f, 0.5f));
    cuboid.rotateX(45.0f);
    cuboid.rotateY(45.0f);
    addToWorld(new Platform(cuboid));

    cuboid = Cuboid(Point3D(0.0f, -55.0f, 0.0f), Vector3D(100.0f, 100.0f, 100.0f));
    addToWorld(new Platform(cuboid));

    Hitbox hitbox(Point3D(0.0f), Vector3D(0.0f));
    Player * player = new Player(hitbox);
    addToWorld(player);
    getCamera() -> attachGameObject(player -> getCameraObject());
}

