#version 410

//  Input from previous shader
in vec3 Texcoord;

//  Fragment color
out vec4 Fragcolor;

// Texture
uniform samplerCube tex;

void main()
{
   Fragcolor = texture(tex, Texcoord);
}
