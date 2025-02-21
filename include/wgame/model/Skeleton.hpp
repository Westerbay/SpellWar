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
    int nodeIndex;
    int parent;
    std::vector<int> children;

    Matrix4D undeformedMatrix;
    Matrix4D inverseBindMatrix;
    Vector3D translation;
    Vector3D scale;
    Quaternion rotation;

    Matrix4D getTransformationMatrix() const;
};

struct Skeleton {
    std::map<int, int> nodeToJoint;
    std::vector<Joint> joints;    
    std::vector<Matrix4D> jointMatrices;
    size_t jointMatricesByteLength;

    void update();
    void updateJoint(int jointIndex);
};

}

#endif
