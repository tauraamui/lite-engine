#version 460 core

in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D u_texture;
uniform vec3 u_color;

void main()
{
   FragColor = texture(u_texture, texCoord) * vec4(u_color, 1.0);
}
