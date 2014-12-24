#version 130

uniform mat4 mvp;
uniform bool is_player;
attribute vec4 vertex;

uniform int number_of_squares;
out vec2 v_texcoord;
in vec2 a_texcoord;


void main(void)
{
    gl_Position = mvp * vertex;
    if(is_player){
        v_texcoord = a_texcoord;
    } else{
        v_texcoord = vec2(vertex.x/number_of_squares, vertex.y/number_of_squares);
    }
}
