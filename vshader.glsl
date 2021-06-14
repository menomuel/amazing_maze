#version 450
layout (location = 0) uniform highp mat4 model;
layout (location = 1) uniform highp mat4 view;
layout (location = 2) uniform highp mat4 projection;

layout (location = 0) in highp vec3 position;
layout (location = 2) in highp vec2 texCoord;

out highp vec2 TexCoord;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.f);
    TexCoord = texCoord;
}
