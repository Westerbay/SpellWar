#version 430 core

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

in vec3 fragNormal;
in vec3 tangentLightPos;
in vec3 tangentViewPos;
in vec3 tangentFragPos;
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D depthMap;

uniform float heightScale;
uniform bool activeParallaxMapping;

uniform bool activeLight;


vec2 parallaxMapping(vec2 texCoords, vec3 viewDir) {
    const float minLayers = 16.0;
    const float maxLayers = 32.0;
    float numLayers = mix(maxLayers, minLayers, max(dot(vec3(0.0, 0.0, 1.0), viewDir), 0.0));

    float layerDepth = 1.0 / numLayers;
    float currentLayerDepth = 0.0;
    vec2 P = viewDir.xy * heightScale; 
    vec2 deltaTexCoords = P / numLayers;

    vec2 currentTexCoords = texCoords;
    float currentDepthMapValue = texture(depthMap, currentTexCoords).r;
    
    while(currentLayerDepth < currentDepthMapValue) {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(depthMap, currentTexCoords).r;  
        currentLayerDepth += layerDepth;  
    }

    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    float afterDepth  = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(depthMap, prevTexCoords).r - currentLayerDepth + layerDepth;
    
    float weight = afterDepth / (afterDepth - beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords; 
}

void main() {
    if (light.display && activeLight) {
        vec3 normal;
        vec2 newTexCoord;
        vec3 viewDirection = normalize(tangentViewPos - tangentFragPos);
        if (activeParallaxMapping) {
            newTexCoord = parallaxMapping(texCoord, viewDirection);
            normal = texture(normalMap, newTexCoord).rgb;
            normal = normalize(normal * 2.0 - 1.0);
        } else {
            normal = normalize(fragNormal);
            newTexCoord = texCoord;
        }        
        
        vec3 lightDirection = normalize(tangentLightPos - tangentFragPos);
        float diffuse = max(dot(normal, lightDirection), 0.0);
        
        vec3 reflectionDirection = reflect(-lightDirection, normal);
        float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), light.defaultSpecularExponent);
        float specular = specAmount * light.defaultSpecularFactor;

        vec4 color = texture(diffuseMap, newTexCoord);
        color.xyz = color.xyz * light.color.xyz * (diffuse + light.defaultAmbient + specular);
        fragColor = color;
    } 
    else {
        vec4 color = texture(diffuseMap, texCoord);
        fragColor = color;
    }
}
