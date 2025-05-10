#version 330 core
out vec4 FragColor;

in float poids1;
in float poids2;

uniform vec3 objectColor;


void main()
{
    FragColor = vec4(poids1, poids2, 0.0, 1.0);
} 

