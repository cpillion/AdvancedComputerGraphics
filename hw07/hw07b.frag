// Image texture.
uniform sampler2D img;
// Width of Image.
uniform float dX;
// Height of Image.
uniform float dY;


void main() {
	// Get initial color
    vec4 FragColor = texture2D(img, gl_TexCoord[0].st);
    // Popular method to get black and white is to add all the color values and divide by 3.  
    // Wanted a faded color look, so used dot products to weight each color rather than simply divide by 3.
    // Initial vectors for dot product found on GLBasic.com and modified for desired output
    FragColor.r = dot(vec3(FragColor), vec3(.40, .77, .19));
    FragColor.g = dot(vec3(FragColor), vec3(.35, .69, .17));
    FragColor.b = dot(vec3(FragColor), vec3(.27, .53, .13));
    // Send the new RGB values to fragment
    gl_FragColor = FragColor;
}
