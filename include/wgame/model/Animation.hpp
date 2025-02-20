/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __ANIMATION_H__
#define __ANIMATION_H__
 
#include "Skeleton.hpp"

#include <iostream>

#define DEFAULT_ELAPSED_TIME 0.01f
 
 
namespace wgame {

class Animation  {
public:
    enum Path {
        TRANSLATION,
        ROTATION,
        SCALE
    };
    enum Interpolation {
        LINEAR,
        STEP,
        CUBICSPLINE
    };
public:
    struct Channel {
        Animation::Path path;
        int samplerIndex;
        int nodeTarget;
    };

    struct Sampler {
        std::vector<float> elapsedTimes;
        std::vector<Vector4D> pathValues;
        Animation::Interpolation interpolation;
    };
public:
    Animation(
        std::vector<Sampler> samplers,
        std::vector<Channel> channels
    );    
    void setLoop(bool repeat);
    bool isRunning() const;
    void start();
    void stop();
    void update(
        Skeleton & skeleton, 
        float elapsedTime = DEFAULT_ELAPSED_TIME
    );
private:
    std::vector<Sampler> _samplers;
    std::vector<Channel> _channels;
    float _firstKeyFrameTime;
    float _lastKeyFrameTime;        
    float _currentKeyFrameTime;
    bool _repeat;
};
 
}
 
#endif
 