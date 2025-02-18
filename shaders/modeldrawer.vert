#version 420 core

layout(location = 0) in vec3 aPos;


layout(std140, binding = 0) uniform CameraBlock {
    mat4 cameraMatrix;
};

uniform mat4 model;
uniform mat4 matNode;

vec3 currentPosition;

void main() {
    currentPosition = vec3(model * matNode * vec4(aPos, 1.0f));
    gl_Position = cameraMatrix * vec4(currentPosition, 1.0);
}
