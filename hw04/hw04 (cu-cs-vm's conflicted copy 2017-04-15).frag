#version 330 core

//  Input from previous shader
in vec3 FrontColor;
in vec2 Texcoord;

//  Fragment color
layout (location=0) out vec4 Fragcolor;

// Texture
uniform sampler2D tex;

void main()
{
   Fragcolor = vec4(FrontColor,1.0)*texture2D(tex, Texcoord);
}
