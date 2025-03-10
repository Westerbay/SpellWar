/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_CUBOID_H__
#define __WG_CUBOID_H__

#include "Geometry.hpp"
#include <iostream>

#include <vector>


namespace wgame {

struct Cuboid {
    Point3D position;
    Vector3D size;
    Matrix3D orientation;
    Cuboid(
        const Point3D & position = Point3D(0.0f),
        const Vector3D & size = Vector3D(0.0f),
        Matrix3D orientation = Matrix3D(1.0f)
    );
    Matrix4D getTransform() const;
    Matrix4D getTransformWithoutScale() const;
    std::vector<Point3D> getVertices() const;
    std::vector<std::vector<Point3D>> getVerticesPerFace() const;
    std::vector<std::vector<Vector3D>> getNormalsPerFace() const;
    std::vector<std::vector<Vector3D>> getTangentsPerFace() const;
    std::vector<std::vector<unsigned>> getElementsPerFace() const;
    bool contains(const Point3D & point) const;
    bool collidesWith(const Cuboid & other) const;
    bool collidesList(const std::vector<Cuboid> & cuboids) const;
    void translate(float delta, const Vector3D & axis);
    void move(const Vector3D & vector);    
    void move(float delta, const Vector3D & axis);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    bool isSeparated(const Cuboid & other, const Point3D & axis) const;
    void projectOntoAxis(const Point3D & axis, float & minProj, float & maxProj) const;
};

typedef Cuboid Hitbox;

}


#endif

