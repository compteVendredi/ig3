#include <point.h>

Point::Point(){

}


Point::Point(glm::vec3 coord, glm::vec3 norm, float u, float v){
    this->coord = coord;
    this->norm = norm;
    this->u = u;
    this->v = v;
    this->poids1 = 1.0;
    this->poids2 = 0.0;
}
