uniform sampler2D img; 
// Width of Image.
uniform float dX;
// Height of Image.
uniform float dY;
// Pixelation Factor
uniform float pix;

void main() 
{ 
	// Set dimensions for simulated pixel size
	float dx = pix*dX;
    float dy = pix*dY;
    // Sample the color of the pixel square at the coordinate
    vec2 coord = vec2(dx*floor(gl_TexCoord[0].x/dx), dy*floor(gl_TexCoord[0].y/dy));
    // Assign the color to the entire size of the simulated pixel
    gl_FragColor =  texture2D(img, coord);
}