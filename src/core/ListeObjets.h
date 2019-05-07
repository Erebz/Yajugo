#ifndef LISTE_OBJETS_H
#define LISTE_OBJETS_H

#include "Objet.h"
/*!
 * \file ListeObjets.h
 * \brief Fichier en-tête d'une liste d'Objet
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */
struct ListeObjets {
/*!
 * \struct ListeObjets ListeObjets.h
 * \brief Comprend les caractéristiques d'une liste d'Objet
 */
    unsigned int nbObjets;/*!< Nombre d'objets dans la liste*/
    Objet * listeObjets; /*!< Pointeur vers un tableau 1D de liste d'objets*/
};

void initialiserListeObjets(ListeObjets & liste);
/*!
 * \fn void initialiserListeObjets(ListeObjets & liste)
 * \brief Procédure initialisant un ListeObjets passé en paramètre
 * 
 * \param liste : ListeObjets qui va être initialisé (en donnée-résultat)
 */
void effacerListeObjets(ListeObjets & liste);
/*!
 * \fn void effacerListeObjets(ListeObjets & liste)
 * \brief Procédure effaçant un ListeObjets passé en paramètre
 * 
 * \param liste : ListeObjets qui va être effacé (en donnée-résultat)
 */
#endif // LISTE_OBJETS_H
