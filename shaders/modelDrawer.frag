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

in vec3 currentPosition;
in vec3 fragTangent;
in vec3 fragBitangent;
in vec3 fragNormal;
in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D textureDiffuse;
uniform sampler2D textureMetallicRoughness;
uniform sampler2D textureNormal;

uniform bool hasMetallicRoughness;
uniform bool hasNormalMap;

uniform vec4 baseColorFactor;  
uniform float metallicFactor;  
uniform float roughnessFactor;  

uniform bool activeLight;


const vec3 F0_DIELECTRIC = vec3(0.04);
const float alphaThreshold = 0.2;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float distributionGGX(float NdotH, float roughness) {
    float alpha = roughness * roughness;
    float alpha2 = alpha * alpha;
    float denom = (NdotH * NdotH) * (alpha2 - 1.0) + 1.0;
    return alpha2 / (3.14159265 * denom * denom);
}

float geometrySmith(float NdotV, float NdotL, float roughness) {
    float k = (roughness + 1.0) * (roughness + 1.0) / 8.0;
    float G1 = NdotV / (NdotV * (1.0 - k) + k);
    float G2 = NdotL / (NdotL * (1.0 - k) + k);
    return G1 * G2;
}

vec3 getNormalFromMap() {
    vec3 tangentNormal = texture(textureNormal, texCoord0).rgb * 2.0 - 1.0; 

    vec3 T = normalize(fragTangent);
    vec3 B = normalize(fragBitangent);
    vec3 N = normalize(fragNormal);

    mat3 TBN = mat3(T, B, N);
    return normalize(TBN * tangentNormal);
}

void main() {  
    vec4 baseColor = texture(textureDiffuse, texCoord0) * baseColorFactor;
    if (baseColor.a <= alphaThreshold) discard;

    if (light.display != 0 && activeLight) {

        vec2 metallicRoughness = hasMetallicRoughness ? texture(textureMetallicRoughness, texCoord0).bg : vec2(0.0);    
        float metallic = metallicRoughness.r * metallicFactor;
        float roughness = clamp(metallicRoughness.g * roughnessFactor, 0.04, 1.0);
        
        vec3 normal = hasNormalMap ? getNormalFromMap() : normalize(fragNormal);

        vec3 lightDir = normalize(light.position.xyz - currentPosition);
        vec3 viewDir = normalize(light.cameraPosition.xyz - currentPosition);
        vec3 halfVec = normalize(lightDir + viewDir);

        float NdotL = max(dot(normal, lightDir), 0.0);
        float NdotV = max(dot(normal, viewDir), 0.0);
        float NdotH = max(dot(normal, halfVec), 0.0);

        vec3 F0 = mix(F0_DIELECTRIC, baseColor.rgb, metallic);
        vec3 F = fresnelSchlick(max(dot(halfVec, viewDir), 0.0), F0);

        float D = distributionGGX(NdotH, roughness);
        
        float G = geometrySmith(NdotV, NdotL, roughness);

        vec3 specular = (D * G * F) / max(4.0 * NdotV * NdotL, 0.001);
        vec3 diffuse = (1.0 - F) * baseColor.rgb * (1.0 - metallic);

        vec3 lightColor = light.color.rgb;
        vec3 color = (diffuse + specular) * lightColor * NdotL;
        
        color += baseColor.rgb * light.ambient;

        fragColor = vec4(color, baseColor.a);
    } 
    else {
        fragColor = baseColor;
    } 

}
