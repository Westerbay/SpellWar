#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

out vec3 color;

void main() {
    gl_Position = cameraMatrix * vec4(aPos, 1.0);
    color = aColor;
}
