/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/World.hpp>


World::World(GameCamera * camera) : GameObjectGroup() {
    add(new Background());

    Hitbox mapHitbox(Point3D(0.0f), Vector3D(100.0f, 30.0f, 100.0f));
    Map * map = new Map(mapHitbox);
    map -> generatePlatform(
        20, 
        Vector3D(12.0f, 1.0f, 12.0f), 
        Vector3D(36.0f, 1.0f, 36.0f)
    );
    add(map);

    Hitbox hitbox(Point3D(0.0f), Vector3D(0.0f));
    Player * player = new Player(hitbox);
    add(player);
    
    camera -> setFarPlane(800.0f);
    camera -> attachGameObject(player -> getCameraObject());
}
