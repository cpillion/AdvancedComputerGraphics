#version 410

//  Transformation matrices
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

//  Vertex attributes (input)
in vec3 Vertex;

//  Output to next shader
out vec3 Texcoord;

void main()
{

    gl_Position =  ProjectionMatrix * mat4(mat3(ModelViewMatrix)) * vec4(Vertex, 1.0);
    Texcoord = Vertex;
}

