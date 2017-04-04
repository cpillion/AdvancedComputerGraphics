
varying vec3 View;            //  Eye position
varying vec3 Light;           //  Light direction
varying vec3 Normal;          //  Normal vector
uniform sampler2D RockTex;
uniform sampler2D SnowTex;
uniform sampler2D GrassTex;
uniform sampler2D alphaTex;   // RGB Map Storing what texture to use
uniform sampler2D normalMap;

void main(void)
{
   vec4 alpha   = texture2D( alphaTex, gl_TexCoord[0].xy);
   vec4 tex0    = texture2D( GrassTex,  gl_TexCoord[0].xy * 4.0 ); 
   vec4 tex1    = texture2D( RockTex, gl_TexCoord[0].xy * 4.0 ); 
   vec4 tex2    = texture2D( SnowTex,  gl_TexCoord[0].xy * 4.0 ); 

   vec4 encodedNormal = texture2D(normalMap, gl_TexCoord[0].xy);
   vec3 normCoords = 2.0 * encodedNormal.rgb - vec3(1.0);

   //  N is the object normal
   vec3 N = normalize(normCoords);
   //  L is the light direction
   vec3 L = normalize(Light);

   //  Diffuse light is cosine of light and normal vectors
   float Id = dot(L,N);

   //  Adjust day for specular
   if (Id>0.0)
   {
      //  R is the reflected light vector R = 2(L.N)N - L
      vec3 R = reflect(L,N);
      //  V is the view vector (eye vector)
      vec3 V = normalize(View);
      //  Specular is cosine of reflected and view vectors
      float Is = dot(R,V);
   }

   // Choose textures by multiplying the alpha texture. 1 - use texture, 0 - dont. 
   tex0 *= alpha.r; // Red channel
   tex1 = mix( tex0, tex1, alpha.g ); // Green channel
   vec4 outColor = mix( tex1, tex2, alpha.b ); // Blue channel
   
   gl_FragColor = outColor*Id;
}
