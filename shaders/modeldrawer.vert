#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;
layout(location = 5) in ivec4 aJoint;
layout(location = 6) in vec4 aWeight;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

layout(std140, binding = 2) uniform JointsBlock {
    mat4 jointsMatrices[1000];
};

out vec3 fragNormal;
out vec2 texCoord0;

uniform int isAnimated;
uniform mat4 model;


void main() {
    if (isAnimated == 1) {
        mat4 skinningMatrix = mat4(0.0);
        for (int i = 0; i < 4; i ++) {
            skinningMatrix += aWeight[i] * jointsMatrices[aJoint[i]];
        }
        fragNormal = normalize(mat3(skinningMatrix) * aNormal);
        gl_Position = cameraMatrix * model * skinningMatrix * vec4(aPos, 1.0);
    } else {
        fragNormal = normalize(aNormal);
        gl_Position = cameraMatrix * model * vec4(aPos, 1.0);
    }    

    texCoord0 = aTexCoord0;
}
