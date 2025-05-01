#version 330 core

in vec3 ourCols;

out vec4 FragColor;

void main() {
    FragColor = vec4(ourCols, 1);
}