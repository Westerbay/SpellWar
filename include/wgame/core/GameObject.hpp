/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "../geometry/Cuboid.hpp"


namespace wgame {

class GameObject {
public:
    GameObject(const Hitbox & hitbox = Hitbox());
    virtual void update() = 0;
    virtual void render() {};
    virtual ~GameObject() = default;
    Hitbox getHitbox() const;
protected:
    Hitbox hitbox;
};

};


#endif
