#ifndef BONE_H
#define BONE_H


#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cylindre.h>
#include <iostream>
#include <point.h>

class Bone{
    public:
        Bone(glm::vec3 debut, glm::vec3 fin, unsigned int indiceBone);   
        void mettreParent(Bone *parent);  //fictif      
        void mettreEnfant(Bone *enfant);  //fictif
        glm::mat4 matRotation(float angle, glm::vec3 axe);//Centré sur glm::vec3 debut
        void attacherCylindre(Cylindre *cylindre);
        void afficher();
        void normaliserPoids();
		void actualiser();
        void free();
        
    private:
        void calculerPoids();
        std::vector<Point> points;
        Bone* parent;
        Bone* enfant;
        glm::vec3 debut, fin;
        Cylindre* cylindre;
        unsigned int VAO, VBO, indiceBone;
        
        
};

#endif
