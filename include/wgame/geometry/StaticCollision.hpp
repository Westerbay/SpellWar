/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_STATIC_COLLISION_H__
#define __WG_STATIC_COLLISION_H__

#include "Cuboid.hpp"

#include <memory>

#define DEFAULT_MAX_DEPTH 2
#define DEFAULT_MAX_OBJECTS 0

namespace wgame {

class StaticCollision {
public:
    StaticCollision(
        const Hitbox & hitbox,        
        unsigned maxDepth = DEFAULT_MAX_DEPTH,
        unsigned maxObjects = DEFAULT_MAX_OBJECTS,
        unsigned depth = 0
    );
    bool insert(const Hitbox & hitbox);
    bool collidesWith(const Hitbox & hitbox) const;
private:
    void subdivide();
private:
    Hitbox _hitbox;
    unsigned _depth;
    unsigned _maxDepth;
    unsigned _maxObjects;
    std::vector<Hitbox> _objects;
    std::unique_ptr<StaticCollision> _children[8];
};

}

#endif
