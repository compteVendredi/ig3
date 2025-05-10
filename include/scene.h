#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <glad/glad.h>
#include <cubemap.h>
#include <surfaceBezier.h>
#include <shader.h>
#include <camera.h>
#include <cylindre.h>
#include <bone.h>



class Scene{
    public:
        Scene(std::string pathCubemap, std::string pathTexture, Camera *camera);
        void renderCubemap();
        void renderDepthMap();
        void renderObjectScene(int rotationInDegree);
        void free();
        void show();
        glm::vec3 lightPos;
    private:
        void renderScene(const Shader *shader, int beginObjectNumber, int endObjectNumber);
        void makeShader(std::string pathTexture);
        void makeFloor();
        void makeObject();
        void configureDepthMap();
        void configureGBuffer();
        unsigned int VBO[2], VAO[2], floorVAO, floorVBO;
        unsigned int VBO_surface[2], VAO_surface[2], EBO[2];
        unsigned int texture, depthMapFBO, depthMap;
        unsigned int gBuffer, gPosition, gNormal, gAlbedo;
        Cubemap *cubemap;
        SurfaceBezier *surface;
        Shader *shader_ig3, *shader_cubemap, *simpleDepthShader, *boneShader, *shaderScene;
        Camera *camera;
        Cylindre *cylindre;
        Bone *bone1, *bone2;
        glm::mat4 matRotation;
};


#endif
