/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_SEKELETON_H__
#define __WG_SEKELETON_H__

#include "../geometry/Geometry.hpp"

#include <vector>
#include <map>

#define NO_PARENT -1
#define ROOT_JOINT 0


namespace wgame {

struct Joint {
    Matrix4D undeformedMatrix;
    Vector3D translation;
    Vector3D scale;
    Quaternion rotation;    
};

struct Skeleton {
    size_t jointMatricesByteLength;
    std::map<int, std::vector<int>> jointChildren;
    std::map<int, int> jointParents;
    std::map<int, int> nodeToJoint;
    std::vector<Joint> joints;    
    std::vector<Matrix4D> jointMatrices;    
    std::vector<Matrix4D> jointInverseBindMatrices;

    Matrix4D getTransformationMatrix(Joint & joint) const;
    void update();
    void updateJoint(int jointIndex);
};

}

#endif
