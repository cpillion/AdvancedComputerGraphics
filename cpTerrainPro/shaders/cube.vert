#version 410

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat3 NormalMatrix;

uniform vec4 Position;

//  Vertex attributes (input)
in vec4 Vertex;
in vec3 Color;
in vec3 Normal;
in vec2 Texture;

//  Output to next shader
out vec3 FrontColor;
out vec2 Texcoord;

vec3 phong()
{
        vec3 Ambient = vec3(0, 0, 0);
        vec3 Diffuse = vec3(1., 1., 1.);
        vec3 Specular = vec3(1., 1., 1.);

	//  vertex coordinate on body
	vec3 P = vec3(ModelViewMatrix * Vertex);
	//  object normal at P
	vec3 N = normalize(NormalMatrix * Normal);
	//  light vector
        vec3 L = normalize(vec3(ViewMatrix * Position) - P);

	// Emission and ambient color
	vec3 color = Ambient;

	float Id = dot(L,N);
	if (Id>0.0)
	{
		// Add diffuse
		color += Id*Diffuse;
		// Reflected light vector
		vec3 R = reflect(-L, N);
		// view vector
		vec3 V = normalize(-P);
		// Add specular
		float Is = dot(R,V);
		if (Is>0.0) color += pow(Is, 32.0)*Specular;
	}
        return color*Color;
}

void main()
{	
   //  Pass colors to fragment shader (will be interpolated)
   FrontColor = phong();
   //  Pass texture coords
   Texcoord = Texture;
   //  Set transformed vertex location
   gl_Position =  ProjectionMatrix * ModelViewMatrix * Vertex;
}
