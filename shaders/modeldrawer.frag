#version 420 core

in vec2 texCoord0;

out vec4 fragColor;

uniform sampler2D textureDiffuse;

void main() {
    vec4 color = texture(textureDiffuse, texCoord0);
    fragColor = color;
}
