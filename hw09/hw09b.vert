#version 120

//  Lame fire

attribute float Start;     //  Start time
uniform   float time;      //  Time
uniform float fall;        //  Snowfall Speed
uniform float wind;        //  X Wind Speed
uniform float dim;         //  View Dim
uniform sampler3D Noise3D; //  Noise texture

//  Perlin noise function
float noise(vec3 X)
{
   vec4 nv = texture3D(Noise3D,X);
   return nv[0]+nv[1]+nv[2]+nv[3]+0.03135;
}

void main(void)
{
   //  Particle life is mod Start time (offset by 5 to get sim going)
   float t = mod(time+5.0,Start);
   //  Initial position
   vec4 vert = gl_Vertex;
   // Displace more with higher wind. Assume percentage of wind for lateral accel
   vert.x += t*wind+0.5*(wind*0.1)*t*t;
   //  Noisy movement
   vec3 X = vec3(0.1*t,vert.x,vert.y)+gl_Color.rgb;
   // Have snow fall at a more constant rate since air resistance and weight slow its accel
   vert.y -= fall*t;
   if (vert.y < -2.0*dim) gl_FrontColor = vec4(0, 0, 0, 1);
   //vert.x += noise(X)-0.2;
   vert.z += noise(X)-0.2;
   //  Noisy yellow trending to red
   gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
   //  Transform particle location
   gl_Position = gl_ModelViewProjectionMatrix*vert;
}

