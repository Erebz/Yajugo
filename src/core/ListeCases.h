#ifndef LISTE_CASES_H
#define LISTE_CASES_H

#include "Case.h"/*! \headerfile Case.h*/
/*!
 * \file ListeCases.h
 * \brief Fichier en-tête d'une listes de Case
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */
struct ListeCases {
/*!
 *\struct ListeCases ListeCase.h
 *\brief Comprend les caractéristiques d'une liste de Case
 */
  unsigned int nbCases = 0;/*!< Nombre de cases  dans la liste (0 par défaut)*/
  Case * listeCases = NULL; /*!< Pointeur vers un tableau 1D de cases (vaut NULL par défaut)*/
};

void initialiserListeCases(ListeCases & liste);
/*!
 * \fn void initialiserListeCases(ListeCases & liste)
 * \brief Procédure: Initialise un ListeCases
 * \param[in,out] liste un ListeCases
 */
void effacerListeCases(ListeCases & liste);
/*!
 * \fn void effacerListeCases(ListeCases & liste)
 * \brief Procédure: Efface un ListeCases
 * \param[in,out] liste un ListeCases
 */
#endif
