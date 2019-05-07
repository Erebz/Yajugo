#ifndef ETAGE_H
#define ETAGE_H

#include "Case.h" /*! \headerfile Case.h*/
#include "ListeCases.h" /*! \headerfile ListeCases.h*/
#include "ListeCompetences.h" /*! \headerfile ListeCompetences.h*/
#include "ListeTypesEnnemis.h" /*! \headerfile ListeTypesEnnemis.h*/
#include "ListeObjets.h" /*! \headerfile ListeObjets.h*/
#include "ListeDonjons.h" /*! \headerfile ListeDonjons.h */
#include "Ennemi.h" /*! \headerfile Ennemi.h*/

/*!
* \def TAILLE_X
* \brief Définit la largeur maximale de l'étage.
*/
#define TAILLE_X 50
/*!
* \def TAILLE_Y
* \brief Définit la longueur maximale de l'étage.
*/
#define TAILLE_Y 50

/*!
* \file Etage.h
* \brief Fichier en-tête de la classe Etage
*
* \author J. Grosjean, Y. Hamdi,H. Messina
* \version 1.0
* \date 22/03/2019
*/
/*!
* \class Etage Etage.h
* \brief La classe Etage qui contient des Case.
*/
class Etage {
public:
  /*!
  * \brief Constructeur
  *
  * Constructeur par défaut de la classe Etage
  */
  Etage();
  /*!
  * \brief Constructeur par copie de la classe étage
  * \param[in] lc un ListeCases
  * \param[in] lcomp un ListeCompetences
  * \param[in] lt un ListeTypesEnnemis
  * \param[in] lo un ListeObjets
  * \param[in] idEtage un unsigned int
  */
  Etage(unsigned int x, unsigned int y, const ListeCases & lc);
  //Etage(const ListeCases & lc, const ListeTypesEnnemis & lt, const ListeObjets & lo);
  Etage(const InfosEtage& infos, const ListeCases & lc, const ListeCompetences & lcomp, const ListeTypesEnnemis & lt, const ListeObjets & lo);
  /*!
  * \brief Déstructeur de la classe Etage
  */
  ~Etage();

  /*!
  * \fn unsigned int getTailleX() const
  * \brief Fonction: Retourne la largeur de l'étage.
  * \return Un unsigned int
  */
  unsigned int getTailleX() const;
  /*!
  * \fn unsigned int getTailleY() const
  * \brief Fonction: Retourne la longueur de l'étage.
  * \return Un unsigned int
  */
  unsigned int getTailleY() const;
  /*!
  * \fn const Case& getCase(const unsigned int x, const unsigned int y) const
  * \brief Fonction: Retourne la case demandée
  * \details * Retourne la case se situant aux coordonnées (x,y) passées en paramètres.
  * \param[in] x un unsigned int
  * \param[in] y un unsigned int
  * \return Un Case
  */
  const Case& getCase(const unsigned int x, const unsigned int y) const;
  /*!
  * \fn void ajouterObjetCase(const unsigned int x, const unsigned int y, Objet* obj)
  * \brief Procédure: Ajoute un objet dans une case
  * \param[in] x un unsigned int, la coordonnée X de la case
  * \param[in] y un unsigned int, la coordonnée Y de la case
  * \param[in,out] obj un pointeur d'Objet, pointant vers l'objet à ajouter
  */
  void ajouterObjetCase(const unsigned int x, const unsigned int y, Objet* obj);
  /*!
  * \fn void retirerObjetCase(const unsigned int x, const unsigned int y)
  * \brief Procédure: Retire à une case l'objet qu'elle contient
  * \param[in] x un unsigned int, la coordonnée X de la case
  * \param[in] y un unsigned int, la coordonnée Y de la case
  */
  void retirerObjetCase(const unsigned int x, const unsigned int y);
  /*!
  * \fn unsigned int getNbEnnemis() const
  * \brief Fonction: Retourne le nombre d'ennemis dans l'étage actif.
  * \return Un unsigned int
  */

  unsigned int getNbEnnemis() const;
  /*!
  * \fn const Ennemi& getEnnemi(const unsigned int i) const
  * \brief Fonction: Retourne l'ennemi demandé.
  * \details L'indice de l'ennemi à retourner est passé en paramètre. \n
  * L'Ennemi est constant et n'est pas modifiable.
  * \param[in] i un unsigned int
  * \return Un Ennemi
  */
  const Ennemi& getEnnemi(const unsigned int i) const;
  /*!
  * \fn Ennemi& getEnnemiOriginal(const unsigned int i) const
  * \brief Fonction: Retourne l'ennemi désiré
  * \details L'indice de l'ennemi à retourner est passé en paramètre.
  * \param[in] i un unsigned int, l'indice de l'ennemi à retourner
  * \return Un Ennemi
  */
  Ennemi& getEnnemiOriginal(const unsigned int i) const;
  /*!
  * \fn void retirerIemeEnnemi(const unsigned int i)
  * \brief Procédure: Supprime un ennemi de l'étage
  * \details L'indice de l'ennemi à supprimr de l'étage est passé en paramètre.
  * \param[in] i un unsigned int, indice de l'ennemi à supprimer
  */
  void retirerIemeEnnemi(const unsigned int i);
  /*!
  * \fn bool caseDisponible(const unsigned int x, const unsigned int y) const
  * \brief Fonction: Indique si la case est libre
  * \details Retourne vrai si la case est libre, faux sinon.\n
  * Les coordonnées (x,y) de la case vérifiée sont passées en paramètres.
  * \param[in] x un unsigned int
  * \param[in] y un unsigned int
  * \return Un booléen
  */
  bool caseDisponible(const unsigned int x, const unsigned int y) const;
  /*!
  * \fn const Etage& operator = (const Etage & etage)
  * \brief Opérateur: Surcharge de l'opérateur =
  * \details Lit l'étage passé en paramètre
  * \param[in] etage un Etage
  */
  const Etage& operator = (const Etage & etage);


private:
  unsigned int tailleX = 0;
  unsigned int tailleY = 0;
  Case cases [TAILLE_Y][TAILLE_X];
  unsigned int nbEnnemis = 0;
  Ennemi * ennemis = NULL;

  void genererEnnemis(const unsigned int nbEnnemis, const unsigned int nbTypesEnnemis, const unsigned int * typesEnnemis, const ListeCompetences& lcomp,const ListeTypesEnnemis & lenn, const unsigned int nivMin, const unsigned int nivMax);
  void genererObjets(const unsigned int nbObjets, const unsigned int nbTypesObjets, const unsigned int * typeObjets, const ListeObjets &lobj);
  void genererSalles(const unsigned int nbIdSalles, const unsigned int * idSalles, const unsigned int nbSalles, const ListeCases & lcase);
  bool sallePosable(unsigned int positionX, unsigned int positionY, unsigned int dimX, unsigned int dimY);
  void genererMurs(const ListeCases & lc);
};


#endif
