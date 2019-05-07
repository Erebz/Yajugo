#ifndef LISTE_TYPES_ENNEMIS_H
#define LISTE_TYPES_ENNEMIS_H

#include "TypeEnnemi.h"/*! \headerfile TypeEnnemi.h*/
/*!
 * \file ListeTypesEnnemis.h
 * \brief Fichier en-tête d'une liste de TypeEnnemi
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */
struct ListeTypesEnnemis {
/*! \struct ListeTypesEnnemis
 *\brief Comprend les caractéristiques d'une liste de TypeEnnemi
 */
    unsigned int nbTypesEnnemis;/*!< Entier représentant le nombre de TypeEnnemi dans la liste*/
    TypeEnnemi * listeTypesEnnemis;/*!< Pointeur vers un tableau de TypeEnnemi*/
};

/*!
 * \fn void initialiserListeTypesEnnemis(ListeTypesEnnemis & liste)
 * \brief Procédure: Initalise une liste de TypeEnnemi
 * \param[in,out] liste un ListeTypesEnnemis
 */
void initialiserListeTypesEnnemis(ListeTypesEnnemis & liste);

/*!
 *\fn void effacerListeTypesEnnemis(ListeTypesEnnemis & liste)
 *\brief Efface une liste de TypeEnnemi
 *\param[in,out] liste un ListeTypesEnnemis
 */
void effacerListeTypesEnnemis(ListeTypesEnnemis & liste);


#endif // LISTE_TYPES_ENNEMIS_H
