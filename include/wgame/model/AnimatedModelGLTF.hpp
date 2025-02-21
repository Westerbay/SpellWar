/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_ANIMATED_MODEL_H__
#define __WG_ANIMATED_MODEL_H__
 
#include "ModelGLTF.hpp"
#include "Animation.hpp"
#include "../opengl/UniformBufferObject.hpp"

#include <unordered_map>
 
 
namespace wgame {
 
class AnimatedModelGLTF : public ModelGLTF {
public:
    AnimatedModelGLTF(const std::string & filename);
    ~AnimatedModelGLTF();
    std::vector<std::string> getAnimationNames() const;
    std::string getCurrentAnimation() const;
    void setTimeAcceleration(float elapsedTime);
    void setLoop(bool loop);
    bool isRunning() const;
    void start();
    void stop();
    void switchAnimation(std::string name, bool loop = false);
    void draw(const Shader & shader) override;    
private:
    void processSkeleton(const tinygltf::Model & model);
    void processJoint(
        const tinygltf::Model & model, 
        int joint, int parent,
        const std::vector<int> & nodeIndices
    );
    void processAnimation(const tinygltf::Model & model);

    float _timeAcceleration;
    UniformBufferObject * _ubo;
    Animation * _currentAnimation;
    Skeleton _skeleton;
    std::vector<Animation> _animations;
    std::unordered_map<std::string, unsigned> _nameToAnimation;
};
 
}
 
#endif
 