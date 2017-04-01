#version 410
//  Input from previous shader
in vec3 FrontColor;
in vec2 Texcoord;

//  Fragment color
out vec4 Fragcolor;

// Texture
uniform sampler2D tex;

void main()
{
   Fragcolor = vec4(FrontColor,1.0)*texture(tex, Texcoord);
}
