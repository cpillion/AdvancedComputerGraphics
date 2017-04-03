#version 410
//  Input from previous shader
in vec3 FrontColor;

//  Fragment color
out vec4 Fragcolor;


void main()
{
   Fragcolor = vec4(FrontColor,1.0);
}
