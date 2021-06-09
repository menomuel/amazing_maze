#version 450
layout (location = 0) uniform highp mat4 model;
layout (location = 1) uniform highp mat4 view;
layout (location = 2) uniform highp mat4 projection;

layout (location = 0) in highp vec3 position;
layout (location = 1) in highp vec3 normal;

uniform lowp vec3 lightColor;

out lowp vec4 color;

void main(void)
{
    gl_Position = projection * view * model * vec4(position, 1.f);
    color = vec4(lightColor, 1.f);
}
