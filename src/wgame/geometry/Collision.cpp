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
    if (_objects.size() < DEFAULT_MAX_OBJECT_PER_REGION) {
        _objects.push_back(hitbox);
        return true;
    }
    return false;
}

bool CollisionLeaf::isFull() const {
    return _objects.size() >= DEFAULT_MAX_OBJECT_PER_REGION;
}

std::vector<Hitbox> & CollisionLeaf::getObjects() {
    return _objects;
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

CollisionTree::CollisionTree(const Hitbox & hitbox, int depth)
    : _hitbox(hitbox), _depth(depth) {
}

bool CollisionTree::insert(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return false;
    }
    if (isLeaf()) {
        _objects.push_back(hitbox);
        if (_objects.size() > DEFAULT_MAX_OBJECT_PER_REGION && _depth > 0) {
            subdivide();
        }
        return true;
    } else {
        bool inserted = false;
        for (auto & child : _children) {
            inserted |= child->insert(hitbox);
        }
        return inserted;
    }
}

Hitbox * CollisionTree::collidesWith(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return nullptr;
    }
    if (isLeaf()) {
        for (Hitbox & object : _objects) {
            if (hitbox.collidesWith(object)) {
                return &object;
            }
        }
        return nullptr;
    } else {
        for (const auto & child : _children) {
            Hitbox * collidedHitbox = child->collidesWith(hitbox);
            if (collidedHitbox) {
                return collidedHitbox;
            }
        }
        return nullptr;
    }
}

void CollisionTree::subdivide() {
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
    for (unsigned i = 0; i < 8; i++) {
        hitboxes[i].size *= 0.5f;
        hitboxes[i].move(translate[i] * hitboxes[i].size * 0.5f);
        _children.push_back(std::make_shared<CollisionLeaf>(hitboxes[i]));
    }
    // Redistribute objects
    for (const Hitbox & obj : _objects) {
        for (auto & child : _children) {
            child->insert(obj);
        }
    }
    _objects.clear();
    _depth--;
}

bool CollisionTree::isLeaf() const {
    return _children.empty();
}

}
