#version 430 core

#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

out vec3 fragPosition;
out vec3 fragNormal;
out vec3 color;

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
    color = aColor;
    fragNormal = vec3(transpose(inverse(model)) * vec4(aNormal, 1.0));
    fragPosition = vec3(model * vec4(aPos, 1.0));
    gl_Position = getGLPosition(fragPosition, drawMode);
}
