#ifndef OBJET_H
#define OBJET_H

#include <string>
using namespace std;/*! \namespace std*/
/*!
 * \file Objet.h
 * \brief Fichier en-tête d'un Objet
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 *
 */

struct Objet {
/*! \struct Objet Objet.h
 * \brief Comprend les caractéristiques d'un Objet
 */
  string nom; /*!< Nom de l'objet*/
  string description; /*!< Brève descritif de  l'objet*/
  int gainPv; /*!< Gain de PV éventuel à la consommation de l'objet (=0 si aucun gain)*/
  int gainMana; /*!< Gain de mana éventuel à la consommation de l'objet (=0 si aucun gain)*/
  int buffAtk; /*!< Bonus d'attaque éventuel à la consommation de l'objet (=0 si aucun bonus) */
  int buffDef; /*!< Bonus de défense éventuel à la consommation de l'objet (=0 si aucun bonus)*/
};

#endif // OBJET_H
