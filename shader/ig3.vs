#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 coordUV;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;
out vec4 FragPosLightSpace;


uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;


void main()
{
	//gl_Position = trans * projection * view * model * vec4(aPos, 1.0f);

    //Normal = aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    UV = coordUV;
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0f);    
    gl_Position = projection * view * vec4(FragPos, 1.0f);
}


