#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;
layout(location = 4) in vec3 aTexCoord1;
layout(location = 5) in ivec4 aJoint;
layout(location = 6) in vec4 aWeight;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

layout(std140, binding = 2) uniform JointsBlock {
    mat4 jointsMatrices[1000];
};

out vec2 texCoord0;

uniform int isAnimated;
uniform mat4 model;


void main() {
    if (isAnimated == 1) {
        vec4 animatedPosition = vec4(0.0f);
        mat4 jointTransform = mat4(0.0f);

        for (int i = 0; i < 4; i ++) {
            if (aWeight[i] == 0) {
                continue;
            }
            if (aJoint[i] >= 1000) {
                animatedPosition = vec4(aPos, 1.0f);
                jointTransform = mat4(1.0f);
                break;
            }
            mat4 jointMatrix = jointsMatrices[aJoint[i]];
            vec4 localPosition = jointMatrix * vec4(aPos, 1.0f);
            animatedPosition += localPosition * aWeight[i];
            jointTransform += jointMatrix * aWeight[i];
        }
        gl_Position = cameraMatrix * model * animatedPosition;
    } else {
        gl_Position = cameraMatrix * model * vec4(aPos, 1.0);
    }    

    texCoord0 = aTexCoord0;
}
