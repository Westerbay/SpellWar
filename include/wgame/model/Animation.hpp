/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#ifndef __WG_ANIMATION_H__
#define __WG_ANIMATION_H__
 
#include "Skeleton.hpp"
#include "../tools/Inputs.hpp"

#include <iostream>

#define KEYFRAME_TIME_SECOND 0.01
 
 
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
        std::string name,
        std::vector<Sampler> samplers,
        std::vector<Channel> channels
    );    
    std::string getName() const;
    void setLoop(bool repeat);
    bool isRunning() const;
    void start();
    void stop();
    void update(
        Skeleton & skeleton, 
        float elapsedTime
    );
private:
    int findElpasedTimeIndex(
        const std::vector<float> & elapsedTimes
    );
    void linearInterpolation(
        Joint & joint,
        Path path,
        const Vector4D & pathValue,
        const Vector4D & nextPathValue,
        float linearFactor
    );
    void stepInterpolation(
        Joint & joint,
        Path path,
        const Vector4D & pathValue
    );

    std::string _name;
    std::vector<Sampler> _samplers;
    std::vector<Channel> _channels;
    double _lastFrame;
    float _firstKeyFrameTime;
    float _lastKeyFrameTime;        
    float _currentKeyFrameTime;
    bool _repeat;
};
 
}
 
#endif
 