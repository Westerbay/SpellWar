/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/geometry/Cuboid.hpp>


namespace wgame {

Cuboid::Cuboid(
    Point3D position,
    float width,  
    float height, 
    float length
) : position(position), width(width), height(height), length(length) {}

bool Cuboid::containsPoint(const Point3D & point) const {
    return (point.x >= position.x && point.x <= position.x + width) &&
           (point.y >= position.y && point.y <= position.y + height) &&
           (point.z >= position.z && point.z <= position.z + length);
}

bool Cuboid::intersectCuboid(const Cuboid & other) const {
    bool separated = (position.x + width  < other.position.x || other.position.x + other.width  < position.x) ||
                     (position.y + height < other.position.y || other.position.y + other.height < position.y) ||
                     (position.z + length < other.position.z || other.position.z + other.length < position.z);
    return !separated;
}

}

