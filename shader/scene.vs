#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 FragPos;
out vec4 FragPosLightSpace;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;



void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);  
    gl_Position = projection * view * vec4(FragPos, 1.0f);
}
