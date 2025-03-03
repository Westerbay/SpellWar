#version 430 core

struct LightInfo {
    vec4 cameraPosition; 
    vec4 position;
    vec4 color;    
    int display;
    float ambient;
    float specularFactor; 
    int specularExponent;
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
};

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
layout(location = 7) in vec3 aTangent;

out vec3 fragPos;
out vec2 texCoord;
out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragPos;

uniform mat4 model;

void main() {
    vec3 position = vec3(model * vec4(aPos, 1.0));
    gl_Position = cameraMatrixDynamic * vec4(position, 1.0);

    fragPos = position;
    texCoord = aTexCoord;

    vec3 T = normalize(mat3(model) * aTangent);
    vec3 N = normalize(mat3(model) * aNormal);
    vec3 B = cross(N, T);
    mat3 TBN = transpose(mat3(T, B, N));

    tangentLightPos = TBN * light.position.xyz;
    tangentViewPos = TBN * light.cameraPosition.xyz;
    tangentFragPos = TBN * fragPos;
}
