#include <iostream> /*! \headerfile iostream*/
#include "Jeu_sfml.h" /*! \headerfile "Jeu_sfml.h"*/

using namespace std; /*! \namespace std*/
/*!
 * \file main_sfml.cpp
 * \brief Fichier main pour SFML
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 15/04/2019
 */

int main(int argc, char** argv){
    srand(time(NULL));
    Jeu_sfml jeu;
    bool continuer = true;
    while(continuer && jeu.fenetreOuverte()){
      jeu.boucleSFML();
      continuer = jeu.demanderContinuer();
    }

    return 0;
}
