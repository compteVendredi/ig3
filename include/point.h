#ifndef POINT_H
#define POINT_H

#include <vector>
#include <glm/glm.hpp>

class Point{
    public:
        Point();
        Point(glm::vec3 coord, glm::vec3 norm, float u, float v);

        glm::vec3 coord;
        glm::vec3 norm;
        float u, v, poids1, poids2;
};



#endif
