
void main(void)
{
   //  Particle location
   gl_FrontColor = gl_Color;

   gl_Position = gl_ModelViewProjectionMatrix*gl_Vertex;
}
