#version 430 core

#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
layout(location = 7) in vec3 aTangent;


struct CameraMatrices {
    mat4 background;
    mat4 world;   
    mat4 HUD; 
};

struct LightInfo {
    vec4 cameraPosition; 
    vec4 position;
    vec4 color;    
    float defaultAmbient;
    float defaultSpecularFactor; 
    int defaultSpecularExponent;
    bool display;
    bool activeNormalMap;
    bool activeParallaxMapping;
};

layout(std140, binding = 0) uniform CameraBlock {
    CameraMatrices cameraMatrices;
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};


out vec3 fragNormal;
out vec2 texCoord;
out vec3 tangentLightPos;
out vec3 tangentViewPos;
out vec3 tangentFragPos;

uniform mat4 model;
uniform int drawInstanced;
uniform int drawMode;
uniform bool activeParallaxMapping;

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
    
    vec3 fragPos = vec3(model * vec4(aPos, 1.0));    
    fragNormal = transpose(inverse(mat3(model))) * aNormal;
    texCoord = aTexCoord;    

    if (activeParallaxMapping && light.activeParallaxMapping && light.display && light.activeNormalMap) {
        vec3 T = normalize(mat3(model) * aTangent);
        vec3 N = normalize(mat3(model) * aNormal);
        vec3 B = cross(N, T);
        mat3 TBN = transpose(mat3(T, B, N));

        tangentLightPos = TBN * light.position.xyz;
        tangentViewPos = TBN * light.cameraPosition.xyz;
        tangentFragPos = TBN * fragPos;
    }
    else {
        tangentLightPos = light.position.xyz;
        tangentViewPos = light.cameraPosition.xyz;
        tangentFragPos = fragPos;
    }

    gl_Position = getGLPosition(fragPos, drawMode);
    
}
