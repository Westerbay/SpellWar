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

#define DEFAULT_DEPTH_COLLISION 100
#define DEFAULT_MAX_OBJECT_PER_REGION 100

namespace wgame {

class ICollisionStatic {
public:
    virtual ~ICollisionStatic() = default;
    virtual bool insert(const Hitbox & hitbox) = 0;
    virtual Hitbox * collidesWith(const Hitbox & hitbox) = 0;
};

class CollisionLeaf : public ICollisionStatic {
public:
    CollisionLeaf(const Hitbox & hitbox, int maxObjects);
    bool insert(const Hitbox & hitbox) override;
    Hitbox * collidesWith(const Hitbox & hitbox) override;
    bool isFull() const;
    std::vector<Hitbox> & getObjects();
private:
    Hitbox _hitbox;
    int _maxObjects;
    std::vector<Hitbox> _objects;
};

class CollisionTree : public ICollisionStatic {
public:
    CollisionTree(const Hitbox & hitbox, int depth = DEFAULT_DEPTH_COLLISION, int maxObjects = DEFAULT_MAX_OBJECT_PER_REGION);
    bool insert(const Hitbox & hitbox) override;
    Hitbox * collidesWith(const Hitbox & hitbox) override;
private:
    void subdivide();
    bool isLeaf() const;
    Hitbox _hitbox;
    std::vector<Hitbox> _objects;
    std::vector<std::shared_ptr<ICollisionStatic>> _children;
    int _depth;
    int _maxObjects;
};

}

#endif
