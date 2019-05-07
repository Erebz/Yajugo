#ifndef COMPETENCE_H
#define COMPETENCE_H

#include <string> /*! \headerfile string*/
using namespace std;/*! \namespace std*/
/*!
 * \file Competence.h
 * \brief Fichier en-tête de la structure Competence
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
*
 */

struct Competence {
   /*!
    * \struct Competence Competence.h
    * \brief Comprend les caractéristiques d'une compétence
    */
    string nom; /*!< Nom de la compétence.*/
    string description; /*!< Description de la compétence.*/
    unsigned int degats; /*!< Dégâts infligés à l'utilisation de la compétence.*/
    int buffAtk; /*!< Bonus/malus d'attaque appliqué à l'utilisateur de la compétence (0 par défaut)*/
    int buffDef; /*!< Bonus/malus de défense appliqué à l'utilisateur de la compétence (0 par défaut)*/
    int buffAtkCible; /*!< Bonus/malus d'attaque appliqué à la cible de la compétence (0 par défaut) */
    int buffDefCible; /*!< Bonus/malus de défense appliqué à la cible de la compétence (0 par défaut)*/
    unsigned int precision; /*!< Pourcentage de chance que la compétence s'applique avec succès (entier compris entre 0 et 100)*/
    unsigned int portee; /*!< Nombre de cases où s'applique la compétences dans la direction de l'utilisateur*/
    bool transperce; /*!< Indique si la compétence peut traverser plusieurs ennemis dans la direction*/
    unsigned int coutMana; /*< Coût de la compétence à soustraire au mana du lanceur*/
    int gainPv; /*!< éventuel gain de points de vie (0 par défaut). La valeur peut être négative : dégats de recul*/
    unsigned int gainMana; /*!< éventuel gain de mana (0 par défaut)*/
};

#endif // COMPETENCE_H
