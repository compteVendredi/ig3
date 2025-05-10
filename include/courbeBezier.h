#ifndef COURBEBEZIER_H
#define COURBEBEZIER_H


#include <vector>
#include <glm/glm.hpp>
#include <define.h>
#include <glad/glad.h>


class CourbeBezier {
    public:
        /*Mise en place de deux méthodes de discrétisation de l'espace paramétrique pour l'approximation de la courbe par des segments de droite*/


        //Uniforme dans l'espace paramétrique (à partir du nombre de segment donné par l'utilisateur)
        CourbeBezier(const std::vector<glm::vec3>& pointsControles, int nbSegment);

        //Uniforme en longueur de segment (à partir de la longueur d'un segment donné par l'utilisateur)
        //Pour une précision de + ou - 1% de la longueur
        CourbeBezier(const std::vector<glm::vec3>& pointsControles, float longueur);

        glm::vec3 evaluer(float t) const;


        /*Visualisation de la courbe et de son polygone de contrôle*/
        void charger(unsigned int *VBO, unsigned int *VAO);
        void afficherCourbe() const;
        void afficherPolygoneControle() const;
        

    private:
        std::vector<glm::vec3> pointsControles;
        std::vector<glm::vec3> points;
        unsigned int *VAO;
};



#endif
