#version 330 core

in vec2 TexCoord;
in vec3 ourCols;

out vec4 FragColor;

uniform sampler2D container;
uniform sampler2D tree;


void main() {
    FragColor = mix(texture(container, TexCoord), texture(tree, TexCoord), .6);
}