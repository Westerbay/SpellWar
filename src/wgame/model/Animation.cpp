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
    std::vector<Sampler> samplers,
    std::vector<Channel> channels
) : _samplers(samplers), _channels(channels) {
    Sampler & sampler = samplers[0];
    if (sampler.elapsedTimes.size() >= 2) {
        _firstKeyFrameTime = sampler.elapsedTimes.front();
        _lastKeyFrameTime = sampler.elapsedTimes.back();
    }
    _currentKeyFrameTime = 0.0f;
    _repeat = false;
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
    _currentKeyFrameTime = _lastKeyFrameTime;
}

void Animation::update(Skeleton & skeleton, float elapsedTime) {
    if (!isRunning()) {
        return;
    }
    _currentKeyFrameTime += elapsedTime;
    if (_repeat && _currentKeyFrameTime > _lastKeyFrameTime) {
        _currentKeyFrameTime = _firstKeyFrameTime;
    }
    for (Channel & channel : _channels) {
        Sampler & sampler = _samplers[channel.samplerIndex];
        int jointIndex = skeleton.nodeToJoint[channel.nodeTarget];
        Joint & joint = skeleton.joints[jointIndex];
        for (int i = 0; i < sampler.elapsedTimes.size() - 1; i ++) {
            if (_currentKeyFrameTime >= sampler.elapsedTimes[i] && _currentKeyFrameTime <= sampler.elapsedTimes[i + 1]) {
                float linearFactor = _currentKeyFrameTime - sampler.elapsedTimes[i];
                linearFactor /= sampler.elapsedTimes[i + 1] - sampler.elapsedTimes[i];
                switch (sampler.interpolation) {
                    case LINEAR:
                    {
                        switch (channel.path) {
                            case TRANSLATION:
                            {
                                joint.translation = glm::mix(sampler.pathValues[i], sampler.pathValues[i + 1], linearFactor);
                                break;
                            }
                            case ROTATION:
                            {
                                Quaternion quaternion1;
                                quaternion1.x = sampler.pathValues[i].x;
                                quaternion1.y = sampler.pathValues[i].y;
                                quaternion1.z = sampler.pathValues[i].z;
                                quaternion1.w = sampler.pathValues[i].w;

                                Quaternion quaternion2;
                                quaternion2.x = sampler.pathValues[i + 1].x;
                                quaternion2.y = sampler.pathValues[i + 1].y;
                                quaternion2.z = sampler.pathValues[i + 1].z;
                                quaternion2.w = sampler.pathValues[i + 1].w;

                                joint.rotation = glm::normalize(glm::slerp(quaternion1, quaternion2, linearFactor));
                                break;
                            }
                            case SCALE:
                            {
                                joint.scale = glm::mix(sampler.pathValues[i], sampler.pathValues[i + 1], linearFactor);
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
                                joint.translation = Vector3D(sampler.pathValues[i]);
                                break;
                            }
                            case ROTATION:
                            {
                                joint.rotation.x = sampler.pathValues[i].x;
                                joint.rotation.y = sampler.pathValues[i].y;
                                joint.rotation.z = sampler.pathValues[i].z;
                                joint.rotation.w = sampler.pathValues[i].w;
                                break;
                            }
                            case SCALE:
                            {
                                joint.scale = Vector3D(sampler.pathValues[i]);
                                break;
                            }
                        }
                        break;
                    }
                    case CUBICSPLINE:
                    {
                        std::cerr << "CUBICSPLINE animation interpolation not supported" << std::endl;
                        return;
                    }
                }
                break;
            }            
        }
    }
    skeleton.update();
}

}

