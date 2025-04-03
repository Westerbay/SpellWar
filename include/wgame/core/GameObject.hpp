/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_GAME_OBJECT_H__
#define __WG_GAME_OBJECT_H__

#include <glad/glad.h>

#include "../geometry/Cuboid.hpp"


namespace wgame {

class GameObject {
public:
    GameObject(const Hitbox & hitbox = Hitbox());
    Hitbox getHitbox() const;
    virtual void update() {};
    virtual void render() {};
    virtual void renderBackground() {};
    virtual void renderHUD(const Size & screenSize) {};
    virtual ~GameObject() = default;    
protected:
    Hitbox hitbox;
};

};


#endif
