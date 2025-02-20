/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


 #ifndef __ANIMATION_H__
 #define __ANIMATION_H__
 
 #include "../geometry/Geometry.hpp"
 
 #include <map>
 #include <string>
 #include <iostream>
 
 namespace wgame {
 
 struct Joint {
     int nodeIndex;
 
     Matrix4D undeformedMatrix = Matrix4D(1.0f);
     Matrix4D inverseBindMatrix;
     Vector3D translation = Vector3D(0.0f);
     Vector3D scale = Vector3D(1.0f);
     Quaternion rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
 
     Matrix4D getDeformedBindMatrix() {
         return glm::translate(Matrix4D(1.0f), translation) *
                glm::mat4(rotation) * 
                glm::scale(Matrix4D(1.0f), scale) *
                undeformedMatrix;
     }
 
     int parent;
     std::vector<int> children;
 };
 
 struct Skeleton {
     std::vector<Joint> joints;
     std::map<int, int> nodeToJoint;
     std::map<int, int> jointToNode;

     unsigned size;
     std::vector<Matrix4D> finalMatrixJoints;
 
     void update() {
        for (int i = 0; i < joints.size(); i ++) {
            finalMatrixJoints[i] = joints[i].getDeformedBindMatrix();
        }
        updateJoint(0);
        for (int i = 0; i < joints.size(); i ++) {
            finalMatrixJoints[i] = finalMatrixJoints[i] * joints[i].inverseBindMatrix;
        }
     }
     void updateJoint(int jointIndex) {
        Joint & joint = joints[jointIndex];
        int parent = joint.parent;
        if (parent != -1) {
            finalMatrixJoints[jointIndex] = finalMatrixJoints[parent] * finalMatrixJoints[jointIndex];
        }
        for (int child: joint.children) {
            updateJoint(child);
        }
     }

 };

typedef enum {
    TRANSLATION,
    ROTATION,
    SCALE
} AnimationType;

typedef enum {
    LINEAR,
    STEP,
    CUBICSPLINE
} InterpolationMethod;

struct Channel {
    AnimationType path;
    int samplerIndex;
    int node;
};

struct Sampler {
    std::vector<float> timeStep;
    std::vector<Vector4D> outputValues;
    InterpolationMethod method;
};


struct Animation {
    void start() {
        currentKeyFrameTime = firstKeyFrameTime;
    }
    void stop() {
        currentKeyFrameTime = lastKeyFrameTime + 1.0f;
    }
    bool isRunning() {
        return (repeat || currentKeyFrameTime <= lastKeyFrameTime);
    }
    bool willExpire(float timestep) {
        return (!repeat && currentKeyFrameTime + timestep > lastKeyFrameTime);
    }
    float getDuration() {
        return lastKeyFrameTime - firstKeyFrameTime;
    }
    float getCurrentTime() {
        return currentKeyFrameTime - firstKeyFrameTime;
    }
    void update(Skeleton & skeleton, float timestep) {
        if (!isRunning()) {
            return;
        }
        currentKeyFrameTime += timestep;
        if (repeat && currentKeyFrameTime > lastKeyFrameTime) {
            currentKeyFrameTime = firstKeyFrameTime;
        }
        for (Channel & channel: channels) {
            Sampler & sampler = samplers[channel.samplerIndex];
            int jointIndex = skeleton.nodeToJoint[channel.node];
            Joint & joint = skeleton.joints[jointIndex];

            for (int i = 0; i < sampler.timeStep.size() - 1; i ++) {
                if (currentKeyFrameTime >= sampler.timeStep[i] && currentKeyFrameTime <= sampler.timeStep[i + 1]) {
                    switch (sampler.method) {
                        case LINEAR:
                        {
                            float a = (currentKeyFrameTime - sampler.timeStep[i]) / (sampler.timeStep[i + 1] - sampler.timeStep[i]);
                            switch (channel.path) {
                                case TRANSLATION:
                                {
                                    joint.translation = glm::mix(sampler.outputValues[i], sampler.outputValues[i + 1], a);
                                    break;
                                }
                                case ROTATION:
                                {
                                    Quaternion quaternion1;
                                    quaternion1.x = sampler.outputValues[i].x;
                                    quaternion1.y = sampler.outputValues[i].y;
                                    quaternion1.z = sampler.outputValues[i].z;
                                    quaternion1.w = sampler.outputValues[i].w;

                                    Quaternion quaternion2;
                                    quaternion2.x = sampler.outputValues[i + 1].x;
                                    quaternion2.y = sampler.outputValues[i + 1].y;
                                    quaternion2.z = sampler.outputValues[i + 1].z;
                                    quaternion2.w = sampler.outputValues[i + 1].w;

                                    joint.rotation = glm::normalize(glm::slerp(quaternion1, quaternion2, a));
                                    break;
                                }
                                case SCALE:
                                {
                                    joint.scale = glm::mix(sampler.outputValues[i], sampler.outputValues[i + 1], a);
                                    break;
                                }
                            }
                            break;
                        }
                        case STEP:
                        {
                            switch (channel.path) {
                                case TRANSLATION:
                                {
                                    joint.translation = Vector3D(sampler.outputValues[i]);
                                    break;
                                }
                                case ROTATION:
                                {
                                    joint.rotation.x = sampler.outputValues[i].x;
                                    joint.rotation.y = sampler.outputValues[i].y;
                                    joint.rotation.z = sampler.outputValues[i].z;
                                    joint.rotation.w = sampler.outputValues[i].w;
                                    break;
                                }
                                case SCALE:
                                {
                                    joint.scale = Vector3D(sampler.outputValues[i]);
                                    break;
                                }
                            }   
                            break;
                        }
                    }
                }
            }
        }
    }
    
    std::vector<Sampler> samplers;
    std::vector<Channel> channels;
    float firstKeyFrameTime;
    float lastKeyFrameTime;
    float currentKeyFrameTime = 0.0f;
    
    bool repeat = true;
    std::string name;
};
 
 }
 
 #endif
 