// Image texture.
uniform sampler2D img;
// Width of Image.
uniform float dX;
// Height of Image.
uniform float dY;


vec4 sample(float dx,float dy)
{
   return texture2D(img,gl_TexCoord[0].st+vec2(dx,dy));
}

void main()
{   
   vec4 H = -sample(-dX,+dY) - 2.0*sample(0.0,+dY) - sample(+dX,+dY)
            +sample(-dX,-dY) + 2.0*sample(0.0,-dY) + sample(+dX,-dY);

   vec4 V =     sample(-dX,+dY)  -     sample(+dX,+dY)
          + 2.0*sample(-dX,0.0)  - 2.0*sample(+dX,0.0)
          +     sample(-dX,-dY)  -     sample(+dX,-dY);

   vec4 filtered = sqrt(H*H+V*V);

   // Creating cartoon effect by combining edge information and original image data. Add blur in the future?
   gl_FragColor = mix(filtered, texture2D(img, vec2( gl_TexCoord[0].s, gl_TexCoord[0].t)), 0.5);
}
