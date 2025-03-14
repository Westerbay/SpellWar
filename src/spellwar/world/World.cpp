/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <spellwar/world/World.hpp>


World::World(GameCamera * camera, GameLight * light) : GameObjectGroup() {
    add(new Background());
    add(new Light(light));

    Hitbox mapHitbox(Point3D(0.0f), Vector3D(200.0f, 70.0f, 200.0f));
    Map * map = new Map(mapHitbox);
    map -> generatePlatform(
        50, 
        Vector3D(12.0f, 1.0f, 12.0f), 
        Vector3D(40.0f, 1.0f, 40.0f)
    );
    add(map);

    Player * player = new Player(map);
    add(player);
    
    camera -> setFarPlane(800.0f);
    camera -> attachGameObject(player -> getCameraObject());
}
