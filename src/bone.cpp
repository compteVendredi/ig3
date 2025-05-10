#include <bone.h>



Bone::Bone(glm::vec3 debut, glm::vec3 fin, unsigned int indiceBone){
    points.push_back(Point(debut, glm::vec3(0,0,0),0,0));
    points.push_back(Point(fin, glm::vec3(0,0,0),0,0));
    this->debut = debut;
    this->fin = fin;
    this->indiceBone = indiceBone;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    actualiser();
}

void Bone::actualiser(){

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(Point), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)(2*sizeof(glm::vec3)+sizeof(float)*2));
    glEnableVertexAttribArray(3);


    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

}

void Bone::afficher(){
	actualiser();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, points.size());
    glBindVertexArray(0);
}


void Bone::mettreParent(Bone *parent){
    this->parent = parent;
}


void Bone::mettreEnfant(Bone* enfant){
    this->enfant = enfant;
}


void Bone::attacherCylindre(Cylindre *cylindre){
    this->cylindre = cylindre;
    calculerPoids();
}

void Bone::calculerPoids() {
    std::vector<Point>* pointsCylindre = cylindre->getPoints();

    for (unsigned int i = 0; i < pointsCylindre->size(); i++) {
        glm::vec3 coord = pointsCylindre->at(i).coord; 

        float distanceToBone = glm::distance(coord, debut);   
        if(indiceBone == 0)
			pointsCylindre->at(i).poids1 = 1./distanceToBone;
        else
			pointsCylindre->at(i).poids2 = 1./distanceToBone;
    }
}

void Bone::normaliserPoids(){
    std::vector<Point>* pointsCylindre = cylindre->getPoints();

    for (unsigned int i = 0; i < pointsCylindre->size(); i++) {
		float poids1 = pointsCylindre->at(i).poids1;
		float poids2 = pointsCylindre->at(i).poids2;		
		pointsCylindre->at(i).poids1 /= (poids1 + poids2);
		pointsCylindre->at(i).poids2 /= (poids1 + poids2);
	}	
}



glm::mat4 Bone::matRotation(float angle, glm::vec3 axe){
    glm::mat4 trans = glm::mat4(1.0f);

    trans = glm::rotate(trans, glm::radians(angle), axe);

    glm::vec4 res = trans * glm::vec4(points[0].coord[0], points[0].coord[1], points[0].coord[2], 1.0f);

    points[0].coord[0] = res[0];
    points[0].coord[1] = res[1];
    points[0].coord[2] = res[2];

    return trans;
}


void Bone::free(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
