/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_SPHERE_H__
#define __WG_SPHERE_H__
 
#include "Geometry.hpp"


namespace wgame {

struct Sphere {
    float radius;
    Point3D position;
    Sphere(
        Point3D position = Point3D(0.0f), 
        float radius = 0.0f
    );   
    void generateSphere(
        std::vector<unsigned> & elements, 
        std::vector<Point3D> & normals, 
        std::vector<Point3D> & vertices, 
        unsigned int stacks, unsigned int slices
    ) const;
};

struct Circle {
    float radius;
    Point2D position;
    Circle(
        Point2D position = Point2D(0.0f), 
        float radius = 0.0f
    ); 
    void generateCircle(
        std::vector<unsigned> & elements,
        std::vector<Point3D> & normals,
        std::vector<Point3D> & vertices,
        unsigned int segments
    ) const;
};

}

#endif
