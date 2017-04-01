//  Checkerboard fragment shader
//  Based upon the Brick Shader from class

//  Hardwire drop dimensions
const vec3 BackColor  = vec3(0.0,0.0,0.0);
const vec2 SquareSize = vec2(0.2,0.4);
const vec2 SquarePct  = vec2(1.0,0.50);
const vec3 SquareColor  = vec3(0.8,0.2,0.2);

//  Model coordinates and light from vertex shader
varying float LightIntensity;
varying vec2  ModelPos;
uniform float time;

void main()
{
   //  Divide by brick size for unit coordinates
   vec2 position = ModelPos / SquareSize;
   //  Stagger rows
   if (fract(0.5*position.x)>0.5) position.y += 0.5;
   //  Scroll bricks at 2.5 bricks per second
   position.y += 3.0*time;
   //  Don't care about the integer part
   position = fract(position);
   //  Snap to 0 or 1
   vec2 useSquare = step(position,SquarePct);
   //  Interpolate color (0 or 1 gives sharp transition)
   vec3 color  = mix(BackColor, SquareColor, useSquare.x*useSquare.y);
   //  Adjust color intensity for lighting (interpolated from vertex shader values)
   color *= LightIntensity;
   //  Pad color with alpha
   gl_FragColor = vec4(color,1.0);
}