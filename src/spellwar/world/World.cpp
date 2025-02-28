/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/World.hpp>


World::World(GameCamera * camera) : GameObjectGroup() {
    //add(new Background());

    Hitbox mapHitbox(Point3D(0.0f), Vector3D(200.0f, 100.0f, 200.0f));
    Map * map = new Map(mapHitbox);
    map -> generatePlatform(
        30, 
        Vector3D(10.0f, 2.0f, 10.0f), 
        Vector3D(80.0f, 5.0f, 80.0f)
    );
    add(map);

    Hitbox hitbox(Point3D(0.0f), Vector3D(0.0f));
    Player * player = new Player(hitbox);
    add(player);
    
    camera -> setFarPlane(600.0f);
    camera -> attachGameObject(player -> getCameraObject());
}
