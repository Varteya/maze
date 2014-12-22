#version 130

uniform mat4 mvp;

attribute vec4 vertex;

uniform int number_of_squares;
out vec2 v_texcoord;

void main(void)
{
    gl_Position = mvp * vertex;
    v_texcoord = vec2(vertex.x/number_of_squares, vertex.y/number_of_squares);
}
