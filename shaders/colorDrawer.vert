#version 430 core

#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 aNormal;

struct CameraMatrices {
    mat4 background;
    mat4 world;   
    mat4 HUD; 
};

layout(std140, binding = 0) uniform CameraBlock {
    CameraMatrices cameraMatrices;
};

out vec3 fragPosition;
out vec3 fragNormal;
out vec4 color;

uniform mat4 model;
uniform int drawInstanced;
uniform int drawMode;

vec4 getGLPosition(vec3 position, int mode) {
    if (mode == BACKGROUND_MODE) {
        return cameraMatrices.background * vec4(position, 1.0);
    }
    if (mode == WORLD_MODE) {
        return cameraMatrices.world * vec4(position, 1.0);
    }
    return cameraMatrices.HUD * vec4(position, 1.0);
}

void main() {
    color = aColor;
    fragNormal = vec3(transpose(inverse(model)) * vec4(aNormal, 1.0));
    fragPosition = vec3(model * vec4(aPos, 1.0));
    gl_Position = getGLPosition(fragPosition, drawMode);
}
