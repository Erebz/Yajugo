#ifndef LISTE_DONJONS
#define LISTE_DONJONS

#include <string> /*! \headerfile string*/
using namespace std; /*! \namespace std*/

/*!
* \file ListeDonjons.h
* \brief Fichier en-tête des structures InfosEtage, InfosDonjon et ListeDonjons
*
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 02/04/2019
*/
struct InfosEtage{
    /*!
     * \struct InfosEtage ListeDonjons.h
     * \brief Renseigne les données d'un Etage
     */
  unsigned int nbEnnemis;/*!< Nombre d'ennemis dans l'étage*/
  unsigned int nbEnnemisRencontrables; /*!< Nombres de types d'ennemis différents dans l'étage*/
  unsigned int * ennemisRencontrables; /*!< Lien vers les types d'Ennemi*/ //id de types ennemis
  unsigned int niveauMax;/*!< Niveau max attribuable à un Ennemi de l'Etage à sa génération*/
  unsigned int niveauMin;/*!< Niveau min attribuable à un Ennemi de l'Etage à sa génération*/
  unsigned int nbObjets;/*!< Nombre d'Objet dans l'Etage*/
  unsigned int nbObjetsTrouvables; /*!< Nombre de types d'Objet différents dans l'Etage*/
  unsigned int * objetsTrouvables; /*!< Lien vers les types d'Objet*/ //id d'objets
  unsigned int tailleX;
  unsigned int tailleY;
  unsigned int nbIdSalles;
  unsigned int * idSalles;
  unsigned int nbSalles;
};

struct InfosDonjon{
    /*!
     * \struct InfosDonjon ListeDonjons.h
     * \brief Renseigne les données d'un Donjon
     */
  string nom;/*!< Nom du donjon*/
  unsigned int niveauNecessaire;/*!< Niveau minimal à avoir pour accéder au donjon*/
  unsigned int nbEtages; /*!< Nombre d'Etage dans le Donjon*/
  InfosEtage * etages;/*!< Lien vers un tableau d'InfosEtage*/
};

struct ListeDonjons{
    /*!
     * \struct ListeDonjons ListeDonjons.h
     * \brief Renseignements sur les Donjon du Jeu
     */
  unsigned int nbDonjons;/*!< Nombre de Donjon dans le Jeu*/
  InfosDonjon * donjonsDisponibles;/*!< Lien vers un tableau d'InfosDonjon*/
};

/*!
 * \fn void initialiserListeDonjons(ListeDonjons & ldonj)
 * \brief Procédure: Initialise la liste des donjons
 * \param[in,out] ldon un ListeDonjons
 */
void initialiserListeDonjons(ListeDonjons & ldonj);
/*!
 * \fn void effacerListeDonjons(ListeDonjons & ldonj)
 * \brief Procédure: Efface la liste des donjons
 * \param[in,out] ldonj un ListeDonjons
 */
void effacerListeDonjons(ListeDonjons & ldonj);

#endif // LISTE_DONJONS
