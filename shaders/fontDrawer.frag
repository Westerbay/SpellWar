#version 430 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D fontSampler;
uniform vec3 fontColor;
uniform vec4 fillColor;

void main() {
	fragColor = texture(fontSampler, texCoords);
	if (fragColor.a == 0) {
		fragColor = fillColor;
	}
	else {
		fragColor.rgb = fontColor;
	}
}
