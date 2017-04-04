#version 410

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

//  Vertex attributes (input)
in vec4 Vertex;
in vec3 Color;

//  Output to next shader
out vec3 FrontColor;


in float Start;     //  Start time
uniform float time;      //  Time
uniform float dim;         //  View Dim
uniform sampler3D Noise3D; //  Noise texture

//  Perlin noise function
float noise(vec3 X)
{
   vec4 nv = texture(Noise3D,X);
   return nv[0]+nv[1]+nv[2]+nv[3]+0.03135;
}

void main(void)
{
   //  Particle life is mod Start time (offset by 5 to get sim going)
   float t = mod(time+5.0,Start);
   //  Initial position
   vec4 vert = Vertex;
   // Displace more with higher wind. Assume percentage of wind for lateral accel
   vert.x += t*0.1+0.5*(0.1*0.1)*t*t;
   //  Noisy movement
   vec3 X = vec3(0.1*t,vert.x,vert.y)+Color.rgb;
   // Have snow fall at a more constant rate since air resistance and weight slow its accel
   vert.y -= 5.*t;
   if (vert.y < -2.0*dim) FrontColor = vec3(0, 0, 0);
   //vert.x += noise(X)-0.2;
   vert.z += noise(X)-0.2;
   //  Noisy yellow trending to red
   FrontColor = vec3(1.0, 1.0, 1.0);
   //  Transform particle location
   gl_Position =  ProjectionMatrix * ModelViewMatrix * vert;
}
