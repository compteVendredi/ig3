#include <cylindre.h>

Cylindre::Cylindre(unsigned int subdivisionsH, unsigned int subdivisionsV){

    genererCylindre(subdivisionsH, subdivisionsV);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);   

    actualiser();

}

void Cylindre::actualiser(){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), points.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(2*sizeof(glm::vec3)+sizeof(float)*2));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

std::vector<Point>* Cylindre::getPoints(){
    return &points;
}


void Cylindre::genererCylindre(unsigned int subdivisionsH, unsigned int subdivisionsV) {
    float radius = 1.0f;
    float height = 5.0f;

    for (unsigned int i = 0; i <= subdivisionsV; i++) {
        float y = (i / float(subdivisionsV)) * height - height / 2.0f;

        for (unsigned int j = 0; j < subdivisionsH; j++) {
            float angle = (j / float(subdivisionsH)) * 2.0f * M_PI;
            float x = radius * cos(angle);
            float z = radius * sin(angle);
            Point point = Point(glm::vec3(x, y, z), glm::vec3(0., 0., 0.), 0., 0.);
            points.push_back(point);
        }
    }

    for (unsigned int i = 0; i < subdivisionsV; i++) {
        for (unsigned int j = 0; j < subdivisionsH; j++) {
            unsigned int nextI = (i + 1) % (subdivisionsV + 1);
            unsigned int nextJ = (j + 1) % subdivisionsH;

            unsigned int idx0 = i * subdivisionsH + j;
            unsigned int idx1 = nextI * subdivisionsH + j;
            unsigned int idx2 = nextI * subdivisionsH + nextJ;
            unsigned int idx3 = i * subdivisionsH + nextJ;

            indices.push_back(idx0);
            indices.push_back(idx1);
            indices.push_back(idx2);

            indices.push_back(idx0);
            indices.push_back(idx2);
            indices.push_back(idx3);
        }
    }
}



void Cylindre::afficher(){
    actualiser();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}




void Cylindre::free(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


