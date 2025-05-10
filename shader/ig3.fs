#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 UV;
in vec4 FragPosLightSpace;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform sampler2D roughnessTex;
uniform sampler2D shadowMap;

const float PI = 3.14159265359;


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

vec3 specular_brdf(vec3 V, vec3 L, vec3 N, vec3 H, float alpha){
    float NdotH = dot(N,H);
    float G, D;
    float alpha2 = pow(alpha,2);

    if(NdotH > 0){
        D = alpha2/(PI*(pow(pow(NdotH,2)*(alpha2-1)+1,2)));
    }
    else{
        D = 0;
    }

    float HdotL = dot(H,L);
    float NdotV = dot(N,V);
    float NdotL = dot(N,L);

    if(HdotL > 0 && NdotV > 0){
        G = ((2*normalize(NdotL))/(normalize(NdotL)+sqrt(alpha2+(1-alpha2)*(pow(NdotL,2)))))
        *((2*normalize(NdotV))/(normalize(NdotV)+sqrt(alpha2+(1-alpha2)*(pow(NdotV,2)))));
    }
    else{
        G = 0;
    }

    return (vec3(1.0f,1.0f,1.0f)*G*D)/(4*normalize(NdotL)*normalize(NdotV));
}

vec3 diffuse_brdf(vec3 color) {
    return (1/PI) * color;
}

float conductor_fresnel(float VdotH, float f0, float bsdf) {
    return bsdf * (f0 + (1 - f0) * (1 - pow(abs(VdotH),5)));
}

vec3 fresnel_mix(vec3 V, vec3 H, float ior, vec3 base, vec3 layer, float f0, float fr) {
    float VdotH = dot(V,H);
    f0 = pow(((1-ior)/(1+ior)),2);
    fr = f0 + (1 - f0)*pow((1 - abs(VdotH)),5);
    return mix(base, layer, fr);
}


void main(){
    vec3 V, L, N, H;

    V = normalize(viewPos - FragPos);
    L = normalize(lightPos - FragPos);
    N = normalize(Normal);
    H = normalize(L+V);

    float VdotH = dot(V,H);
    vec3 baseColor = objectColor;

    float roughness = texture(roughnessTex, UV).r;

    float metallic = texture(roughnessTex, UV).g;

    vec3 metal_brdf = specular_brdf(V, L, N, H, pow(roughness,2)) * (baseColor + (1 - baseColor) * (1 - pow(abs(VdotH),5)));
    
    vec3 dielectric_brdf = mix(diffuse_brdf(baseColor), specular_brdf(V, L, N, H, pow(roughness,2)), 0.04 + (1 - 0.04) * (1 - pow(abs(VdotH),5)));

    vec3 material = mix(dielectric_brdf, metal_brdf, metallic);

    FragColor = vec4(material, 1.0f)*(1.0-ShadowCalculation(FragPosLightSpace));
}
