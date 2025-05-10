#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <glad/glad.h>

class Cubemap {
    public:
        Cubemap(std::string path);
        void free();
        void draw();
    private:
        unsigned int VAO, VBO, cubemapTexture;
};



#endif
