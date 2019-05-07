#ifndef TYPEENNEMI_H
#define TYPEENNEMI_H

#include <string> /*! \headerfile string*/
using namespace std; /*! \namespace std*/
/*!
 * \file TypeEnnemi.h
 * \brief Fichier en-tête d'un TypeEnnemi
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */

struct TypeEnnemi { /*! \struct TypeEnnemi TypeEnnemi.h
    * \brief Comprend les caractéristiques d'un type d'Ennemi*/
    string nom; /*!< Nom du type d'ennemi*/
    float coeffPv; /*!< Coefficient à appliquer aux PV de ce type d'ennemi à chaque augmentation de niveau*/
    float coeffMana; /*!< Coefficient à appliquer aux points de mana de ce type d'ennemi à chaque augmentation de niveau*/
    float coeffAtk; /*!< Coefficient à appliquer à l'attaque des ennemis de ce type à chaque augmentation de niveau*/
    float coeffDef; /*!< Coefficient à appliquer à la défense des ennemis de ce type à chaque augmentation de niveau*/
    float coeffXp; /*!< Coefficient à appliquer aux point d'expériences de ce type d'ennemi (donné quand il est battu) à chaque augmentation de niveau*/
    unsigned int nbCompetencesMax; /*!< Nombre maximum de compétences maximum utilisables par ce type d'ennemi*/
    unsigned int * competences; /*!< Pointeur vers un tableau 1D d'entiers faisant référence aux compétences utilisables par ce type d'ennemi*/
};

/*!
 * \fn effacerTypeEnnemi(TypeEnnemi &t)
 * \brief Procédure: initialise les statistiques du joueur
 * \param[in,out] t un TypeEnnemi
 */
void effacerTypeEnnemi(TypeEnnemi &t);

#endif // TYPEENNEMI_H
