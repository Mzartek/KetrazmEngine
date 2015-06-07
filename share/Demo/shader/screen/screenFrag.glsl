#version 440

uniform sampler2D backgroundTexture;

layout(binding = 0) uniform colorBuffer
{
	vec4 color;
};

in VertexData
{
	vec2 texCoord;
} FragIn;

layout(location = 0) out vec4 fragColor;

void main(void)
{
	fragColor = texture(backgroundTexture, FragIn.texCoord) * color;
}
