#version 130

uniform sampler2D texture;

in vec2 v_texcoord;

void main(void)
{

    gl_FragColor = texture2D(texture, v_texcoord);
//    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
