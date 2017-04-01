//  Basic vertex shader for Homework01.

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    //  Map from NDC (-1,1) to RBG (0, 1)
    gl_FrontColor = (gl_Position/gl_Position.w) * 0.5 + 0.5;

}
