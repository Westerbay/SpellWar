#version 430 core


#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

#define MAX_JOINTS 1000
#define MAX_TRANSFORMS 10000


layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;
layout(location = 5) in ivec4 aJoint;
layout(location = 6) in vec4 aWeight;
layout(location = 7) in vec3 aTangent;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

layout(std140, binding = 2) uniform JointsBlock {
    mat4 jointsMatrices[MAX_JOINTS];
};

layout(std430, binding = 5) buffer TransformsBlock {
    mat4 transformsModel[MAX_TRANSFORMS];
};

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 fragTangent;
out vec3 fragBitangent;
out vec2 texCoord0;

uniform bool isAnimated;
uniform bool hasNormalMap;

uniform mat4 model;
uniform int drawInstanced;
uniform int drawMode;

vec4 getGLPosition(vec3 position, int mode) {
    if (mode == BACKGROUND_MODE) {
        return cameraMatrixStatic * vec4(position, 1.0);
    }
    if (mode == WORLD_MODE) {
        return cameraMatrixDynamic * vec4(position, 1.0);
    }
    return vec4(position, 1.0);
}

void main() {

    mat4 transform;
    if (drawInstanced == 1) {
        transform = transformsModel[gl_InstanceID] * model;
    } else {
        transform = model;
    }

    if (isAnimated) {
        mat4 skinningMatrix = mat4(0.0);
        for (int i = 0; i < 4; i ++) {
            skinningMatrix += aWeight[i] * jointsMatrices[aJoint[i]];
        }
        fragNormal = transpose(inverse(mat3(skinningMatrix))) * aNormal;
        fragNormal = transpose(inverse(mat3(transform))) * fragNormal;
        fragPosition = vec3(transform * skinningMatrix * vec4(aPos, 1.0));
    } else {
        fragNormal = transpose(inverse(mat3(transform))) * aNormal;
        fragPosition = vec3(transform * vec4(aPos, 1.0));
    }    

    gl_Position = getGLPosition(fragPosition, drawMode);
    texCoord0 = aTexCoord0;

    if (hasNormalMap) {
        fragTangent = normalize(mat3(transform) * aTangent);
        fragBitangent = normalize(cross(fragNormal, fragTangent));
    } else {
        fragTangent = vec3(0.0, 0.0, 0.0);
        fragBitangent = vec3(0.0, 0.0, 0.0);
    }

}
