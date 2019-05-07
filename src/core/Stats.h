#ifndef STATS_H
#define STATS_H

#include <string>/*! \headerfile string*/
#include "TypeEnnemi.h" /*! \headerfile TypeEnnemi.h*/
using namespace std;/*! \namespace std */
/*!
 * \file Stats.h
 * \brief Fichier en-tête des statistiques d'une entité (un Joueur ou un Ennemi)
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */

#define MAX_BUFF 8
/*! \def MAX_BUFF
 * Plus haut bonus applicable
 */
#define MIN_BUFF -4
/*! \def MIN_BUFF
 * Plus bas malus applicable
 */

struct Stats {
/*! \struct Stats Stats.h
 *\brief Comprend les statistiques d'une entité (Ennemi ou Joueur)
 */
  unsigned int pv; /*!< Nombre de point de vie de l'entité (pvMax>=pv) */
  unsigned int pvMax; /*!< Nombre de point de vie maximum de l'entité (>0) */
  unsigned int mana; /*!< Nombre de point de mana de l'entité (manaMax>=mana) */
  unsigned int manaMax; /*!< Nombre de point de mana maximum de l'entité (>0) */
  unsigned int atk; /*!< Attaque effective de l'entité*/
  int buffAtk; /*!< Bonus/malus d'attaque de l'entité */
  unsigned int def; /*!< Défense effective de l'entité*/
  int buffDef; /*!< Bonus/malus défense de l'entité */
};

/*!
 * \fn void initialiserStats(Stats & s, const string &nomType)
 * \brief Procédure: initialise les statistiques du joueur
 * \details Initialise les statistiques \a s à partir des infos de \a nomType
 * \param[in,out] s un Stats
 * \param[in] nomType un string
 */
void initialiserStats(Stats & s, const string &nomType); // Une procédure qui prend en paramètre deux arguments
/*!
 * \fn void initialiserStats(Stats & s, const TypeEnnemi &t, const unsigned int niveau)
 * \brief Procédure: initialise les statistiques d'un ennemi
 * \details Initialise les statistiques \a s d'un ennmi à partir de son type \a t et de son niveau \a niveau
 * \param[in,out] s un Stats
 * \param[in] t un TypeEnnemi, la référence du type de l'ennemi (pour initialiser les bonnes statistiques)
 * \param[in] niveau un unsigned int, niveau de l'ennemi
 */
void initialiserStats(Stats & s, const TypeEnnemi &t, const unsigned int niveau); //pour les ennemis


#endif // STATS_H
