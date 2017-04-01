// Vertex shader

varying vec3 View;     //  Eye position
varying vec3 Light;    //  Light direction
varying vec3 Normal;   //  Normal vector

void main()
{
   //
   //  Lighting values needed by fragment shader
   //
   //Vertex location in modelview coordinates
   vec3 P = vec3(gl_ModelViewMatrix * gl_Vertex);
   //Light direction
   Light = vec3(gl_LightSource[0].position);
   //Normal
   Normal = gl_NormalMatrix * gl_Normal;
   //Eye position
   View  = -P;

   //  Texture coordinate for fragment shader
   gl_TexCoord[0] = gl_MultiTexCoord0;

   //  Set vertex position
   gl_Position = ftransform();
}
