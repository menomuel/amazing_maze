#version 450
in highp vec2 TexCoord;

uniform sampler2D texMap;

void main()
{
    gl_FragColor = texture(texMap, TexCoord);
}
