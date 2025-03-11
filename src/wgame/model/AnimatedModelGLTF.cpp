/*
 * Wester
 * This code is open source and free to use.
 * 
 * You are free to copy, modify, and distribute this file without restriction.
 * No warranties are provided, and any use of this code is at your own risk.
 */


#include <wgame/model/AnimatedModelGLTF.hpp>


namespace wgame {

AnimatedModelGLTF::AnimatedModelGLTF(const std::string & filename) {
    tinygltf::TinyGLTF loader;    
    tinygltf::Model model;
    std::string err, warn;

    bool ret;
    if (getFilePathExtension(filename) == GLTF_EXT) {
        ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
    } else if (getFilePathExtension(filename) == GLB_EXT) {
        ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
    } else {
        std::cerr << "Wrong file format !" << err << std::endl;
        throw std::runtime_error("Wrong file format !");
    }

    if (!warn.empty()) {
        std::cout << "Warning: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "Error: " << err << std::endl;
        throw std::runtime_error("Cannot open model !");
    }
    if (!ret) {
        std::cerr << "Can't open model: " << filename << std::endl;
        throw std::runtime_error("Cannot open model !");
    }

    _timeAcceleration = 1.0f;

    processSkeleton(model);
    processAnimation(model);
    process(model);

    _currentAnimation = &_animations.front();
    _ubo.configure(_skeleton.jointMatricesByteLength);
    _ubo.setBindingPoint(BINDING_JOINT_MATRICES);
    _skeleton.update();
}

std::vector<std::string> AnimatedModelGLTF::getAnimationNames() const {
    std::vector<std::string> animationNames;
    for (const auto & pair : _nameToAnimation) {
        animationNames.push_back(pair.first);
    }
    return animationNames;
}

std::string AnimatedModelGLTF::getCurrentAnimation() const {
    return _currentAnimation -> getName();
}

void AnimatedModelGLTF::setTimeAcceleration(float timeAcceleration) {
    _timeAcceleration = timeAcceleration;
}

void AnimatedModelGLTF::setLoop(bool loop) {
    _currentAnimation -> setLoop(loop);
}

bool AnimatedModelGLTF::isRunning() const {
    return _currentAnimation -> isRunning();
}

void AnimatedModelGLTF::start() {
    _currentAnimation -> start();
}

void AnimatedModelGLTF::stop() {
    _currentAnimation -> stop();
}

void AnimatedModelGLTF::switchAnimation(std::string name, bool loop) {
    _currentAnimation -> stop();
    _currentAnimation = &_animations[_nameToAnimation[name]];
    _currentAnimation -> setLoop(loop);
    _currentAnimation -> start();
}

void AnimatedModelGLTF::draw(const Shader & shader) {
    _currentAnimation -> update(_skeleton, _timeAcceleration);
    _ubo.bind();
    _ubo.setData(_skeleton.jointMatrices.data(), _skeleton.jointMatricesByteLength);
    shader.setUniform("isAnimated", true);
    drawModelMesh(shader);
    _ubo.unbind();
}  

void AnimatedModelGLTF::drawInstanced(const Shader & shader, size_t numberOfInstance) {
    _currentAnimation -> update(_skeleton, _timeAcceleration);
    _ubo.bind();
    _ubo.setData(_skeleton.jointMatrices.data(), _skeleton.jointMatricesByteLength);
    shader.setUniform("isAnimated", true);
    drawModelMeshInstanced(shader, numberOfInstance);
    _ubo.unbind();
}

void AnimatedModelGLTF::processSkeleton(const tinygltf::Model & model) {
    if (model.skins.size() == 0) {
        return;
    }
    if (model.skins.size() > 1) {
        std::cerr << "Model have more than 1 skin!" << std::endl;
        throw std::runtime_error("Cannot load model animations!");
    }
    
    const tinygltf::Skin & skin = model.skins[0];
    if (skin.inverseBindMatrices < 0) {
        return;
    }

    size_t size = skin.joints.size();
    _skeleton.joints.resize(size);
    _skeleton.jointMatrices.resize(size);
    _skeleton.jointInverseBindMatrices.resize(size);
    _skeleton.jointMatricesByteLength = size * sizeof(Matrix4D);
    
    const Matrix4D * inverseBindMatrices;
    {
        loadAccessor<Matrix4D>(
            model,
            model.accessors[skin.inverseBindMatrices],
            inverseBindMatrices
        );
    }

    std::vector<int> nodeIndices(size);
    for (size_t i = 0; i < size; i ++) {
        Joint & joint = _skeleton.joints[i];
        nodeIndices[i] = skin.joints[i];
        _skeleton.jointInverseBindMatrices[i] = inverseBindMatrices[i];
        const tinygltf::Node & node = model.nodes[skin.joints[i]];
        if (node.translation.size() == 3) {
            joint.translation = glm::make_vec3(node.translation.data());
        }
        else {
            joint.translation = Vector3D(0.0f);
        }
        if (node.rotation.size() == 4) {
            joint.rotation = glm::make_quat(node.rotation.data());
        }
        else {
            joint.rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
        }
        if (node.scale.size() == 3) {
            joint.scale = glm::make_vec3(node.scale.data());
        }
        else {
            joint.scale = Vector3D(1.0f);
        }
        if (node.matrix.size() == 16) {
            joint.undeformedMatrix = glm::make_mat4x4(node.matrix.data());
        }
        else {
            joint.undeformedMatrix = Matrix4D(1.0f);
        }
        _skeleton.nodeToJoint[skin.joints[i]] = (int) i;
    }
   
    processJoint(model, ROOT_JOINT, NO_PARENT, nodeIndices);
}

void AnimatedModelGLTF::processJoint(
    const tinygltf::Model & model, 
    int joint, int parent, 
    const std::vector<int> & nodeIndices
) {
    _skeleton.jointParents[joint] = parent;
    const auto & nodes = model.nodes[nodeIndices[joint]];
    for (size_t i = 0; i < nodes.children.size(); i ++) {
        if (nodes.children[i] >= 0) {
            int child = _skeleton.nodeToJoint[nodes.children[i]];
            _skeleton.jointChildren[joint].push_back(child);
            processJoint(model, child, joint, nodeIndices);
        }
    }
}

void AnimatedModelGLTF::processAnimation(const tinygltf::Model & model) {
    for (const auto & animModel : model.animations) {
        std::vector<Animation::Sampler> samplers(animModel.samplers.size());

        for (size_t i = 0; i < animModel.samplers.size(); i ++) {
            const tinygltf::AnimationSampler & samplerModel = animModel.samplers[i];
            Animation::Sampler & sampler = samplers[i];
            sampler.interpolation = Animation::LINEAR;
            if (samplerModel.interpolation == "STEP") {
                sampler.interpolation = Animation::STEP;
            }
            else if (samplerModel.interpolation == "CUBICSPLINE") {
                sampler.interpolation = Animation::CUBICSPLINE;
            }

            /* Load elapsedTime between animations */
            {
                const float * elapsedTimesBuffer;
                const tinygltf::Accessor & accessor = model.accessors[samplerModel.input];
                loadAccessor<float>(model, accessor, elapsedTimesBuffer);
                sampler.elapsedTimes.resize(accessor.count);
                for (size_t i = 0; i < accessor.count; i ++) {
                    sampler.elapsedTimes[i] = elapsedTimesBuffer[i];
                }
            }   
            
            /* Load Transformation values of animated nodes */
            {
                const tinygltf::Accessor & accessor = model.accessors[samplerModel.output];
                sampler.pathValues.resize(accessor.count);
                if (accessor.type == TINYGLTF_TYPE_VEC3) {
                    const Vector3D * buffer;
                    loadAccessor<Vector3D>(model, accessor, buffer);
                    for (size_t i = 0; i < accessor.count; i ++) {
                        sampler.pathValues[i] = Vector4D(buffer[i], 0.0f);
                    }
                } else if (accessor.type == TINYGLTF_TYPE_VEC4) {
                    const Vector4D * buffer;
                    loadAccessor<Vector4D>(model, accessor, buffer);
                    for (size_t i = 0; i < accessor.count; i ++) {
                        sampler.pathValues[i] = Vector4D(buffer[i]);
                    }
                }
            }       
        }

        size_t numChannels = animModel.channels.size();
        std::vector<Animation::Channel> channels(numChannels);
        for (size_t i = 0; i < numChannels; i ++) {
            const tinygltf::AnimationChannel channelModel = animModel.channels[i];
            Animation::Channel & channel = channels[i];
            channel.samplerIndex = channelModel.sampler;
            channel.nodeTarget = channelModel.target_node;
            if (channelModel.target_path == "translation") {
                channel.path = Animation::TRANSLATION;
            } 
            else if (channelModel.target_path == "rotation") {
                channel.path = Animation::ROTATION;
            }
            else if (channelModel.target_path == "scale") {
                channel.path = Animation::SCALE;
            }
        }

        _animations.push_back(Animation(animModel.name, samplers, channels));
        _nameToAnimation[animModel.name] = (unsigned) _animations.size() - 1;
    }
}

};
