#version 430 core

#define BACKGROUND_MODE 0
#define WORLD_MODE 1
#define HUD_MODE 2

layout(location = 0) in vec3 aPos;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec2 aTexCoord;
layout(location = 7) in vec3 aTangent;

struct LightInfo {
    vec4 cameraPosition; 
    vec4 position;
    vec4 color;    
    bool display;
    float defaultAmbient;
    float defaultSpecularFactor; 
    int defaultSpecularExponent;
};

layout(std140, binding = 1) uniform LightBlock {
    LightInfo light;
};

layout(std140, binding = 0) uniform CameraMatrices {
    mat4 cameraMatrixStatic;
    mat4 cameraMatrixDynamic;
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
        return cameraMatrixStatic * vec4(position, 1.0);
    }
    if (mode == WORLD_MODE) {
        return cameraMatrixDynamic * vec4(position, 1.0);
    }
    return vec4(position, 1.0);
}

void main() {
    
    vec3 fragPos = vec3(model * vec4(aPos, 1.0));    
    fragNormal = transpose(inverse(mat3(model))) * aNormal;
    texCoord = aTexCoord;    

    if (activeParallaxMapping) {
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
