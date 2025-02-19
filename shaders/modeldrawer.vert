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

out vec2 texCoord0;

uniform mat4 model;
uniform mat4 matNode;

void main() {
    vec3 currentPosition = vec3(model * matNode * vec4(aPos, 1.0f));
    gl_Position = cameraMatrix * vec4(currentPosition, 1.0);

    texCoord0 = aTexCoord0;
}
