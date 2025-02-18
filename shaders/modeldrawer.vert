#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord0;
layout(location = 4) in vec2 aTexCoord1;

out vec3 color;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

uniform mat4 model;
uniform mat4 matNode;

vec3 currentPosition;

void main() {
    currentPosition = vec3(model * matNode * vec4(aPos, 1.0f));
    gl_Position = cameraMatrix * vec4(currentPosition, 1.0);

    color = aNormal;
}
