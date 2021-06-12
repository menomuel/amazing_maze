#version 450
in highp vec2 TexCoord;
in lowp vec4 color;

uniform sampler2D texMap;

void main()
{
    //gl_FragColor = color;
    gl_FragColor = texture(texMap, TexCoord);
}
