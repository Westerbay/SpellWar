/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/geometry/StaticCollision.hpp>


namespace wgame {

StaticCollision::StaticCollision(
    const Hitbox & hitbox,
    unsigned maxDepth,
    unsigned maxObjects,
    unsigned depth
) : _hitbox(hitbox),
    _depth(depth),
    _maxDepth(maxDepth),
    _maxObjects(maxObjects) {}

bool StaticCollision::insert(const Hitbox & hitbox) {
    if (!_hitbox.collidesWith(hitbox)) {
        return false;
    }
    if (_objects.size() < _maxObjects || _depth >= _maxDepth) {
        _objects.push_back(hitbox);
        return true;
    }
    
    if (!_children[0]) {
        subdivide();
    }

    bool ok = false;
    for (auto & child: _children) {
        if (child -> _hitbox.collidesWith(hitbox) && child -> insert(hitbox)) {
            ok = true;
        }
    }
    if (!ok) {
        _objects.push_back(hitbox);
    }
    return true;
}

bool StaticCollision::collidesWith(const Hitbox & hitbox) const {
    if (!_hitbox.collidesWith(hitbox)) {
        return false;
    }
    if (hitbox.collidesList(_objects)) {
        return true;
    }
    if (_children[0]) {
        for (const auto & child : _children) {
            if (child -> collidesWith(hitbox)) {
                return true;
            }
        }
    }
    return false;
}

void StaticCollision::subdivide() {
    Vector3D translate[] = {
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
        _children[i] = std::make_unique<StaticCollision>(
            hitboxes[i], _maxDepth, _maxObjects, _depth + 1
        );
    }
}

}
