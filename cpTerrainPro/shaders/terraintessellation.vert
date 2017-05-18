#version 410

in vec2 Vertex;

out terrainVertex {
    vec2 position;
} Out;

void main()
{
    Out.position = Vertex;
}
