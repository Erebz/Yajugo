#ifndef TYPEJOUEUR_H
#define TYPEJOUEUR_H

#include <string> /*! \headerfile string*/
using namespace std; /*! \namespace std*/
/*!
* \file TypeJoueur.h
* \brief Fichier en-tête d'un TypeJoueur
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 22/03/2019
*/
struct TypeJoueur { /*! \struct TypeJoueur
    * \brief Comprend les caractéristiques d'un type de Joueur*/
    string nom; /*!< Nom du type de joueur*/
    float coeffPvMin; /*!< Coefficient à appliquer aux PV d'un joueur de ce type quand il monte de niveau*/
    float coeffManaMin; /*!< Coffecient min à appliquer aux points de mana d'un joueur de ce type quand il monte de niveau*/
    float coeffAtkMin; /*!< Coefficient min à appliquer à l'attaque d'un joueur de ce type quand il monte de niveau*/
    float coeffDefMin; /*!< Coefficient min à appliquer à la défense d'un joueur de ce type quand il monte de niveau*/
    float coeffPvMax; /*!< Coefficient max à appliquer aux PV d'un joueur de ce type quand il monte de niveau*/
    float coeffManaMax; /*!< Coffecient max à appliquer aux points de mana d'un joueur de ce type quand il monte de niveau*/
    float coeffAtkMax; /*!< Coefficient max à appliquer à l'attaque d'un joueur de ce type quand il monte de niveau*/
    float coeffDefMax; /*!< Coefficient max à appliquer à la défense d'un joueur de ce type quand il monte de niveau*/
    unsigned int nbApprentissagesMax; /*!< Nombre maximum de compétences que peut apprendre un joueur de ce type*/
    unsigned int * caps; /*!< Pointeur vers un tableau d'entiers. Chaque entier indique un niveau où un joueur de ce type apprend une nouvelle copmpétence*/
    unsigned int * competences; /*!< Pointeur vers un tableau d'entiers. Chaque entier correspond à l'identifiant d'une compétence. \fn
    Une compétence de ce dernier tableau n'est utilisable que si le niveau du joueur de ce type est spérieur ou égal au nombre dans la case de même indice dans le tableau "caps"*/
};

/*!
 * \fn void initialiserTypeJoueur(TypeJoueur &t, const string &nomType)
 * \brief Procédure: Initialise un type de joueur.
 * \details Initialise le TypeJoueur \a t à partir de son nom \a nomType.
 * \param[in,out] t un TypeJoueur
 * \param[in] nomType un string
 */
void initialiserTypeJoueur(TypeJoueur &t, const string &nomType);

/*!
 * \fn void effacerTypeJoueur(TypeJoueur &t)
 * \brief Procédure: Efface le TypeJoueur passé en paramètre
 * \param[in,out] t un TypeJoueur
 */
void effacerTypeJoueur(TypeJoueur &t);

#endif // TYPEJOUEUR_H
