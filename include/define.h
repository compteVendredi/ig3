#ifndef DEFINE_H
#define DEFINE_H

// settings ---------------------------------------

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//shadow map --------------------------------------

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

//courbes et surfaces de Bézier -------------------

//Pour le calcul des courbes (+ = mieux)
const unsigned int MAX_COMPTEUR = 100000;
//Pour le calcul de la dérivée (- = mieux)
//Remarque : instabilité numérique quand trop petit
const float EPSILON = 0.00001;

#endif
