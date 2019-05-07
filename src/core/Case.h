#ifndef CASE_H
#define CASE_H 

#include <string> /*! \headerfile string*/
#include "Objet.h"/*! \headerfile Objet.h */
/*!
* \file Case.h
* \brief Fichier en-tête de la structure Case
* 
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 22/03/2019
*/
struct Case {
/*!
 * \struct Case Case.h
 * \brief Comprend les caractéristiques d'une case
 */
  unsigned int id = 0;/*!< Identifiant d'une case (= sa catégorie: un mur, un chemin, un bloc infranchissable...) (0 par défaut, la case est défini comme étant un mur)*/
  Objet * objet = NULL;/*!< Pointeur vers un Objet (à NULL par défaut, la case ne contient pas d'objet à sa création)*/
  bool traversable = false;/*!< Booléen indiquant si la case est traversable par une entité (joueur ou ennemi) (false par défaut, la case est infranchissable à sa création)*/
  string caractere; /*!< Chaîne de caractères à afficher pour représenter la case
   *\note On ne pouvait pas utiliser un char à la place d'un string car il ne permet pas d'afficher les caractères spéciaux qui étaient nécessaire pour l'affichage.*/
  };
  

#endif
