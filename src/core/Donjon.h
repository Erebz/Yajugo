#ifndef DONJON_H
#define DONJON_H

#include "ListeCases.h" /*! \headerfile ListeCases.h */
#include "ListeCompetences.h"/*! \headerfile ListeCompetences.h */
#include "ListeTypesEnnemis.h" /*! \headerfile ListeTypesEnnemis.h */
#include "ListeObjets.h" /*! \headerfile ListeObjets.h */
#include "ListeDonjons.h" /*! \headerfile ListeDonjons.h */
#include "Etage.h" /*! \headerfile Etage.h */
/*!
 * \file Donjon.h
 * \brief Fichier en-tête de la classe Donjon
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 *
 * \details Donjon est la classe qui va posséder les étages.
 *
 *
 * \date 22/03/2019
 *
 */
/*!
 * \class Donjon Donjon.h
 * \brief La classe Donjon qui contient les étages.
 */
class Donjon{
public:
  /*!
   * \brief Constructeur par défaut
   *
   *
   */
  Donjon();
  /*!
   * \brief Constructeur par copie
   * \param[in] nbEtagesMax un nombre d'étages maximum
   * \param[in] lc un ListeCases
   * \param[in] lt un ListeTypesEnnemis
   * \param[in] lo un ListeObjetsconst Etage& getEtage(const unsigned int i) const
   * \param[in] lcomp un ListeCompetences
   */
  Donjon(const InfosDonjon &infos, const ListeCases & lc, const ListeTypesEnnemis & lt, const ListeObjets & lo, const ListeCompetences & lcomp);
  /*!
   * \brief Destructeur
   *
   * Destructeur de la classe Donjon.
   */
  ~Donjon();
  //const Etage& getEtageActif()const;
  /*!
   * \fn string getNom()const
   * \brief Fonction: Retourne le nom du Donjon
   * \return Un string
   */
  string getNom()const;
  /*!
   * \fn const Etage& getEtage(const unsigned int i) const
   * \brief Fonction: Retourne l'étage demandé
   * \details L'indice de l'Etage à retourner etst pasé en paramètre. \n
   * L'Etage est constant et n'est pas modifiable.
   * \param[in] i un unsigned int, indice de l'étage à retourner
   * \return Un Etage
   */
  const Etage& getEtage(const unsigned int i) const;
  /*!
   * \fn const Etage& getEtageActif() const
   * \brief Fonction: Retourne l'étage actif
   * \details L'Etage est constant et n'est pas modifiable.
   * \return Un Etage
   */
  const Etage& getEtageActif() const;
  /*!
   * \fn Etage& getEtageOriginal(const unsigned int i)
   * \brief Fonction: Retourne l'étage demandé
   * \details L'indice de l'étage demandé est passé en paramètre.
   * \param[in] i un unsigned int, l'indice de l'Etage à retourner
   * \return Un Etage
   */
  Etage& getEtageOriginal(const unsigned int i);
  /*!
   * \fn const Etage& getEtageActifOriginal() const
   * \brief Fonction: Retourne l'étage actif
   * \return Un Etage
   */
  Etage& getEtageActifOriginal();

  /*!
   * \fn unsigned int getNbEtages() const
   * \brief Fonction: Retourne le nombre d'étages
   * \return Un unsigned int
   */
  unsigned int getNbEtages() const;
  /*!
   * \fn unsigned int getNbEtagesParcourus() const
   * \brief Fonction: Retourne le nombre d'étages parcourus
   * \return Un unsigned
   */
  unsigned int getNbEtagesParcourus() const;

  /*!
   * \todo Faire la génération procédurale.\n
   *Pour la generation procédurale, le donjon devra recevoir des infos :
   *nombre d'étage, items et monstres trouvables, échelles de niveau
   *depuis une Liste de donjons*/
  /*!
   * \fn void augmenterNbEtagesParcourus()
   * \brief Procédure: Incrémente le nombre d'étages parcourus
   */
  void augmenterNbEtagesParcourus();
private:
  //Etage etageActif; //solution à adopter à termes mais sans génération procédurale c'est pas utile
  string nom;
  /*!
   * \var Etage * etages
   * \brief Pointeur vers un tableau d'étages.
   * \todo Faire une énération procédurale d'un étage pour n'avoir qu'un Etage pointé à la place d'un tableau.
   */
  Etage * etages;
  /*!
   * \var unsigned int nbEtages
   * \brief Entier non signé indiquant le nombre d'étages dans le tableau d'Etages.
   */
  unsigned int nbEtages;
  /*!
   * \var unsigned int nbEtagesParcourus
   * \brief Entier non signé indiquant le nombre d'étages déjà parcourus.
   */
  unsigned int nbEtagesParcourus;
};

#endif // DONJON_H
