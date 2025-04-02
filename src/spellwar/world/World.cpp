/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/World.hpp>


World::World(GameCamera * camera, GameLight * light) : GameObjectGroup() {
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

    Player * player = new Player(map);
    add(player);
    
    camera -> setFarPlane(FAR_PLANE);
    camera -> attachGameObject(player -> getCameraObject());

    add(new Maintitle());
}
