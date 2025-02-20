/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/Skeleton.hpp>


namespace wgame {

Matrix4D Joint::getTransformationMatrix() const {
    return glm::translate(Matrix4D(1.0f), translation) *
           glm::mat4(rotation) * 
           glm::scale(Matrix4D(1.0f), scale) *
           undeformedMatrix;
}

void Skeleton::update() {
    for (int i = 0; i < joints.size(); i ++) {
        jointMatrices[i] = joints[i].getTransformationMatrix();
    }
    updateJoint(ROOT_JOINT);
    for (int i = 0; i < joints.size(); i ++) {
        jointMatrices[i] = jointMatrices[i] * joints[i].inverseBindMatrix;
    }
}

void Skeleton::updateJoint(int jointIndex) {
    Joint & joint = joints[jointIndex];
    int parent = joint.parent;
    if (parent != NO_PARENT) {
        jointMatrices[jointIndex] = jointMatrices[parent] * jointMatrices[jointIndex];
    }
    for (int child: joint.children) {
        updateJoint(child);
    }
}

}
