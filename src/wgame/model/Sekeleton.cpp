/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/Skeleton.hpp>


namespace wgame {

Matrix4D Skeleton::getTransformationMatrix(Joint & joint) const {
    return glm::translate(Matrix4D(1.0f), joint.translation) *
           glm::mat4(joint.rotation) * 
           glm::scale(Matrix4D(1.0f), joint.scale) *
           joint.undeformedMatrix;
}

void Skeleton::update() {
    for (size_t i = 0; i < joints.size(); i ++) {
        jointMatrices[i] = getTransformationMatrix(joints[i]);
    }
    updateJoint(ROOT_JOINT);
    for (size_t i = 0; i < joints.size(); i ++) {
        jointMatrices[i] = jointMatrices[i] * jointInverseBindMatrices[i];
    }
}

void Skeleton::updateJoint(int jointIndex) {
    int parent = jointParents[jointIndex];
    if (parent != NO_PARENT) {
        jointMatrices[jointIndex] = jointMatrices[parent] * jointMatrices[jointIndex];
    }
    for (int child: jointChildren[jointIndex]) {
        updateJoint(child);
    }
}

}
