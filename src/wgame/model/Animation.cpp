/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/Animation.hpp>


namespace wgame {

Animation::Animation(
    std::string name,
    std::vector<Sampler> samplers,
    std::vector<Channel> channels
) : _name(name), _samplers(samplers), _channels(channels) {
    Sampler & sampler = samplers[0];
    if (sampler.elapsedTimes.size() >= 2) {
        _firstKeyFrameTime = sampler.elapsedTimes.front();
        _lastKeyFrameTime = sampler.elapsedTimes.back();
    }
    _currentKeyFrameTime = 0.0f;
    _repeat = false;
    _lastFrame = System::getTime();
}

std::string Animation::getName() const {
    return _name;
}

void Animation::setLoop(bool repeat) {
    _repeat = repeat;
}

bool Animation::isRunning() const {
    return _repeat || _currentKeyFrameTime <= _lastKeyFrameTime;
}

void Animation::start() {
    _currentKeyFrameTime = _firstKeyFrameTime;
}

void Animation::stop() {
    _currentKeyFrameTime = _lastKeyFrameTime + 1.0f;
    _repeat = false;
}

void Animation::update(Skeleton & skeleton, float elapsedTime) {
    if (!isRunning()) {
        return;
    }
    if (System::getTime() - _lastFrame < KEYFRAME_TIME_SECOND) {
        return;
    }
    _lastFrame = System::getTime();
    _currentKeyFrameTime += (float) KEYFRAME_TIME_SECOND * elapsedTime;
    if (_repeat && _currentKeyFrameTime > _lastKeyFrameTime) {
        _currentKeyFrameTime = _firstKeyFrameTime;
    }
    for (Channel & channel : _channels) {
        Sampler & sampler = _samplers[channel.samplerIndex];
        int jointIndex = skeleton.nodeToJoint[channel.nodeTarget];
        Joint & joint = skeleton.joints[jointIndex];
        int i = findElpasedTimeIndex(sampler.elapsedTimes);
        if (i == -1) {
            skeleton.update();
            return;
        }
        float linearFactor = _currentKeyFrameTime - sampler.elapsedTimes[i];
        linearFactor /= sampler.elapsedTimes[i + 1] - sampler.elapsedTimes[i];
        switch (sampler.interpolation) {
            case LINEAR:
                linearInterpolation(joint, channel.path, sampler.pathValues[i], sampler.pathValues[i + 1], linearFactor);
                break;
            case STEP:
                stepInterpolation(joint, channel.path, sampler.pathValues[i]);
                break;
            case CUBICSPLINE:
                std::cerr << "CUBICSPLINE animation interpolation not supported" << std::endl;
                return;
        }
    }
    skeleton.update();
}

int Animation::findElpasedTimeIndex(
    const std::vector<float> & elapsedTimes
) {
    if (elapsedTimes.size() < 2) {
        return -1;
    }
    if (_currentKeyFrameTime > elapsedTimes.back()) {
        return -1;
    }
    if (_currentKeyFrameTime < elapsedTimes.front()) {
        return -1;
    }

    int mid;
    int left = 0;
    int right = (int) elapsedTimes.size() - 1;    
    while (left <= right) {
        mid = (left + right) / 2;
        if (elapsedTimes[mid] <= _currentKeyFrameTime && _currentKeyFrameTime <= elapsedTimes[mid + 1]) {
            return mid;
        }
        else if (_currentKeyFrameTime < elapsedTimes[mid]) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

void Animation::linearInterpolation(
    Joint & joint,
    Path path,
    const Vector4D & pathValue,
    const Vector4D & nextPathValue,
    float linearFactor
) {
    Quaternion quaternion1;
    Quaternion quaternion2;
    switch (path) {        
        case TRANSLATION:
            joint.translation = glm::mix(pathValue, nextPathValue, linearFactor);
            break;
        case ROTATION:            
            quaternion1.x = pathValue.x;
            quaternion1.y = pathValue.y;
            quaternion1.z = pathValue.z;
            quaternion1.w = pathValue.w;
            quaternion2.x = nextPathValue.x;
            quaternion2.y = nextPathValue.y;
            quaternion2.z = nextPathValue.z;
            quaternion2.w = nextPathValue.w;
            joint.rotation = glm::normalize(glm::slerp(quaternion1, quaternion2, linearFactor));
            break;
        case SCALE:
            joint.scale = glm::mix(pathValue, nextPathValue, linearFactor);
            break;
    }
}

void Animation::stepInterpolation(
    Joint & joint,
    Path path,
    const Vector4D & pathValue
) {
    switch(path) {
        case TRANSLATION:
            joint.translation = pathValue;
            break;
        case ROTATION:
            joint.rotation.x = pathValue.x;
            joint.rotation.y = pathValue.y;
            joint.rotation.z = pathValue.z;
            joint.rotation.w = pathValue.w;
            break;
        case SCALE:
            joint.scale = pathValue;
            break;
    }
}

}

