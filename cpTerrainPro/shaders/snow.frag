#version 410

uniform sampler2D tex;

in vec3 FrontColor;

out vec4 FragColor;

void main()
{
   //  Sample texture
   vec4 color = texture(tex,gl_PointCoord.st);
   //  Set alpha as 1/3 the color
   color.a = 0.3*length(color.rgb);
   //  Blend point color with texture
   FragColor = vec4(FrontColor, 1.0)*color;
}
