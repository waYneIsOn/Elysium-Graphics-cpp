#version 450

layout (binding = 1) uniform sampler2D InputTexture;

layout (location = 0) in vec2 InputUVCoordinates;

layout(location = 0) out vec4 OutputColor;

void main() 
{
	ivec2 TextureDimensions = textureSize(InputTexture, 0);

	OutputColor = texture(InputTexture, InputUVCoordinates);
}