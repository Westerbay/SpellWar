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

#define DEFAULT_DEPTH_COLLISION 2

namespace wgame {

class ICollision {
public:
    virtual ~ICollision() = default;
    virtual bool insert(const Hitbox & hitbox) = 0;
    virtual Hitbox * collidesWith(const Hitbox & hitbox) = 0;
};

class CollisionLeaf : public ICollision {
public:
    CollisionLeaf(const Hitbox & hitbox);
    bool insert(const Hitbox & hitbox) override;
    Hitbox * collidesWith(const Hitbox & hitbox) override;
private:
    Hitbox _hitbox;
    std::vector<Hitbox> _objects;
};

class CollisionTree : public ICollision {
public:
    CollisionTree(
        const Hitbox & hitbox,        
        int depth = DEFAULT_DEPTH_COLLISION
    );
    bool insert(const Hitbox & hitbox) override;
    Hitbox * collidesWith(const Hitbox & hitbox) override;
private:
    void constructTree(int depth);
private:
    Hitbox _hitbox;    
    std::shared_ptr<ICollision> _children[8];
};

}

#endif
