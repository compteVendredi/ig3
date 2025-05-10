#version 330 core

in vec3 FragPos;
in vec4 FragPosLightSpace;

out vec4 FragColor;



uniform sampler2D shadowMap;

//https://learnopengl.com/code_viewer_gh.php?code=src/5.advanced_lighting/3.1.2.shadow_mapping_base/3.1.2.shadow_mapping.fs
float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
     projCoords = projCoords * 0.5 + 0.5;
     float closestDepth = texture(shadowMap, projCoords.xy).r; 
     float currentDepth = projCoords.z;
     float shadow = currentDepth > closestDepth + 0.01  ? 1.0 : 0.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}


void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0)*(1.0-ShadowCalculation(FragPosLightSpace));
} 
