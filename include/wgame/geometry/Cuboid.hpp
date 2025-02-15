/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __CUBOID_H__
#define __CUBOID_H__

#include "Geometry.hpp"

#include <vector>


namespace wgame {

struct Cuboid {
    Point3D position;
    Vector3D size;
    Matrix3D orientation;
    Cuboid(
        const Point3D & position = Point3D(),
        const Vector3D & size = Vector3D(),
        Matrix3D orientation = Matrix3D(1.0f)
    );
    std::vector<Point3D> getVertices() const;
    bool contains(const Point3D & point) const;
    bool collidesWith(const Cuboid & other) const;
    void translate(float delta, const Vector3D & axis);
    void move(float delta, const Vector3D & axis);
    void rotate(float angle, const Vector3D & axis);
    bool isSeparated(const Cuboid & other, const Point3D & axis) const;
    void projectOntoAxis(const Point3D & axis, float & minProj, float & maxProj) const;
};

typedef Cuboid Hitbox;

}


#endif

