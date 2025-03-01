#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;
layout(location = 5) in ivec4 aJoint;
layout(location = 6) in vec4 aWeight;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

layout(std140, binding = 2) uniform JointsBlock {
    mat4 jointsMatrices[1000];
};

layout(std140, binding = 5) uniform TransformsBlock {
    mat4 transformsModel[1000];
};

out vec3 currentPosition;
out vec3 fragNormal;
out vec2 texCoord0;

uniform int isAnimated;
uniform int drawInstanced;
uniform mat4 model;


void main() {

    mat4 transform;
    if (drawInstanced == 1) {
        transform = transformsModel[gl_InstanceID] * model;
    } else {
        transform = model;
    }

    if (isAnimated == 1) {
        mat4 skinningMatrix = mat4(0.0);
        for (int i = 0; i < 4; i ++) {
            skinningMatrix += aWeight[i] * jointsMatrices[aJoint[i]];
        }
        fragNormal = transpose(inverse(mat3(skinningMatrix))) * aNormal;
        fragNormal = mat3(transpose(inverse(transform))) * fragNormal;
        currentPosition = vec3(transform * skinningMatrix * vec4(aPos, 1.0));
        gl_Position = cameraMatrixDynamic * transform * skinningMatrix * vec4(aPos, 1.0);
    } else {
        fragNormal = transpose(inverse(mat3(transform))) * aNormal;
        currentPosition = vec3(transform * vec4(aPos, 1.0));
        gl_Position = cameraMatrixDynamic * transform * vec4(aPos, 1.0);
    }    

    texCoord0 = aTexCoord0;
}
