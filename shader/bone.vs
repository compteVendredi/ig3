#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 3) in vec2 poids;

out float poids1;
out float poids2;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

uniform mat4 matRotation;



void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0); 

    vec4 transformedPos = model * matRotation * vec4(aPos, 1.0);

    poids1 = poids.x;
    poids2 = poids.y;

    gl_Position = projection * view * vec4(poids1 * vec3(worldPos) + poids2 * vec3(transformedPos), 1.0f);

}


