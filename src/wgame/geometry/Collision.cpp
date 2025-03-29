/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/geometry/Collision.hpp>


namespace wgame {

CollisionLeaf::CollisionLeaf(const Hitbox & hitbox) {
    _hitbox = hitbox;
}

bool CollisionLeaf::insert(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return false;
    }
    _objects.push_back(hitbox);
    return true;
}

Hitbox * CollisionLeaf::collidesWith(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return nullptr;
    }
    for (Hitbox & object: _objects) {
        if (hitbox.collidesWith(object)) {
            return &object;
        }
    }
    return nullptr;
}

CollisionTree::CollisionTree(
    const Hitbox & hitbox,        
    int depth
) : _hitbox(hitbox) {
    constructTree(depth);
}

bool CollisionTree::insert(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return false;
    }
    bool inserted = false;
    for (auto & child: _children) {
        inserted |= child -> insert(hitbox);
    }
    return inserted;
}

Hitbox * CollisionTree::collidesWith(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return nullptr;
    }
    for (const auto & child : _children) {
        Hitbox * collidedHitbox = child -> collidesWith(hitbox);
        if (collidedHitbox) {
            return collidedHitbox;
        }
    }
    return nullptr;
}

void CollisionTree::constructTree(int depth) {
    static Vector3D translate[] = {
        {1.0f, 1.0f, 1.0f},
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, -1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
    };

    std::vector<Hitbox> hitboxes(8, _hitbox);
    for (unsigned i = 0; i < 8; i ++) {
        hitboxes[i].size *= 0.5f;
        hitboxes[i].move(translate[i] * hitboxes[i].size * 0.5f);        
        if (depth > 1) {  
            std::shared_ptr<CollisionTree> node = std::make_shared<CollisionTree>(hitboxes[i], depth - 1);
            _children[i] = std::static_pointer_cast<ICollision>(node);
        }
        else {
            std::shared_ptr<CollisionLeaf> leaf = std::make_shared<CollisionLeaf>(hitboxes[i]);
            _children[i] = std::static_pointer_cast<ICollision>(leaf);
        }        
    }
}

}
