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
    Cuboid(
        Point3D position, 
        float width, 
        float height,         
        float length
    );
    bool containsPoint(const Point3D & point) const;
    bool intersectCuboid(const Cuboid &other) const;
    Point3D position;
    float width;
    float height;    
    float length;
};

}


#endif

