#ifndef JEU_H
#define JEU_H

#include <iostream> /*! \headerfile iostream*/
#include "ListeCases.h" /*! \headerfile ListeCases.h*/
#include "ListeCompetences.h" /*! \headerfile ListeCompetences.h*/
#include "ListeTypesEnnemis.h" /*! \headerfile ListeTypesEnnemis.H*/
#include "ListeObjets.h" /*! \headerfile ListeObjets.h*/
#include "ListeDonjons.h" /*! \headerfile ListeDonjons.h*/
#include "Donjon.h" /*! \headerfile Donjon.h*/
#include "Joueur.h" /*! \headerfile Joueur.h*/
#include <string>
#include <fstream>
using namespace std;/*! \namespace std*/
/*!
 * \file Jeu.h
 * \brief Fichier en-tête de la classe Jeu
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 25/03/2019
 */
/*!
 * \class Jeu Jeu.h
 * \brief La classe Jeu qui contient un Joueur et un Donjon
 * \details La classe Jeu est la classe qui instancie la partie (hors-menu principal et options)
 */
class Jeu {
public:
    /*!
     * \brief Constructeur par défaut
     *
     */
  Jeu();
  /*!
   * \brief Constructeur pour nouvelle partie
   * \param[in] nom un string
   * \param[in] nomType un string
   */
  Jeu(const string& nom, const string& nomType);
  /*!
   * \brief Constructeur pour lecture depuis fichier
   * \param[in] i un unsigned int
   */
  Jeu(const unsigned int i);
  /*!
   * \brief Destructeur
   */
  ~Jeu();
  /*!
   * \fn void genererDonjon(onst unsigned int idDonjon)
   * \brief Procédure: Génère et initialise un Donjon à partir de données prédéfinies
   * \param[in] idDonjon un unsigned int , l'indice du Donjon
   */
  void genererDonjon(const unsigned int idDonjon);
  /*!
   * \fn void genererJoueur(const string nom, const string& nomType)
   * \brief Procédure: Génère un Joueur à partir de données prédéfinies
   * \param[in] nom un string, le nom du Joueur
   * \param[in] nomType un string
   */
  void genererJoueur(const string& nom, const string& nomType);
  /*!
   * \fn void genererJoueur(const unsigned int i)
   * \brief Procédure: Génère et initialise un Joueur à partir de données prédéfinies
   * \param i un unsigned int, indice du Joueur
   */
  void genererJoueur(const unsigned int i);
  /*!
   * \fn const Donjon& getDonjon()const
   * \brief Fonction: Retourne la référence du Donjon
   * \details Le Donjon retourné est constant et non modifiable.
   * \return Un Donjon
   */
  const Donjon& getDonjon()const;
  /*!
   * \fn const Joueur& getJoueur()const
   * \brief Fonction: Retourne la référence du Joueur
   * \details Le Joueur retourné est constant et non modifiable
   * \return Un Joueur
   */
  const Joueur& getJoueur()const;
  /*!
   * \fn Donjon& getDonjonOriginal()const
   * \brief Fonction: Retourne la référence du Donjon
   * \return Un Donjon
   */
  Donjon& getDonjonOriginal()const;
  /*!
   * \fn Joueur& getJoueurOriginal()const
   * \brief Fonction: Retourne la référence du Joueur
   * \return Un Joueur
   */
  Joueur& getJoueurOriginal()const;
  /*!
   * \fn const ListeCompetences& getListeCompetences()const
   * \brief Fonction: Retourne la référence de la ListeCompetences
   * \details La ListeCompetences retournée est constante et non modifiable.
   * \return Un ListeCompetences
   */
  const ListeCompetences& getListeCompetences()const;
  /*!
   * \fn const ListeTypesEnnemis& getListeTypesEnnemis()const
   * \brief Fonction: Retourne la référence de la ListeTypesEnnemis
   * \details La ListeTypesEnnemis retournée est constante et non modifiable.
   * \return Un ListeTypesEnnemis
   */
  const ListeTypesEnnemis& getListeTypesEnnemis()const;
  /*!
   * \fn const ListeCases& getListeCases() const
   * \brief Fonction: Retourne la référence de la ListeCases
   * \details La ListeCases retournée est constante et non modifiable.
   * \return Une ListeCases
   */
  const ListeCases& getListeCases()const;
  /*!
   * \fn const ListeObjets& getListeObjets()const
   * \brief Fonction: Retourne la référence de la ListeObjets
   * \details La ListeObjets retournée est constante et non modifiable.
   * \return Une ListeObjets
   */
  const ListeObjets& getListeObjets()const;
  /*!
   * \fn const ListeDonjons& ListeDonjons()const
   * \brief Fonction: Retourne la référence de la ListeDonjons
   * \details La ListeDonjons retournée est constante et non modifiable.
   * \return Une ListeDonjons
   */
  const ListeDonjons& getListeDonjons()const;

  /*!
   * \fn void monterEtageSuivant
   * \brief Procédure: Change d'étage
   */
  void monterEtageSuivant();
  /*!
   * \fn bool actionClavierDeplacementJoueur(const char touche)
   * \brief Fonction: Indique si le joueur appuie sur une flèche du clavier
   * \param[in] touche un char
   * \return Un booléen
   */
  bool actionClavierDeplacementJoueur(const char touche);
  //void executionTourEnnemis();
  //void actionClavierInventaire(const char touche);
  //void actionClavierMenu(const char touche);
  //etc...
  /*!
   * \fn bool joueurUtiliseCompetence(Competence * comp, unsigned int &nbEnnemisTouches, string * &ennemis, unsigned int * &degats, unsigned int &xp)
   * \brief Fonction: Traite l'utilisation d'une compétence
   * \details Si la compétence passe le test de précision, la fonction renvoie true et la compétence est effectivement appliquée.
   * Les paramètres en données-résultats sont modifiés en conséquence.\n
   * Si la compétence échoue au test de précision, la fontion renvoie false, la compétence n'est pas appliquée et les paramètres en données-résultats ne sont pas modifiés.\n
   * La compétence utilisée est passée en paramètre.
   * \param[in,out] comp un pointeur vers une Competence, pointe vers la compétence que le joueur veut utiliser
   * \param[in,out] nbEnnemisTouches un unsigned int, compte le nombre d'ennemis touchés (si la compétence passe le test de précision)
   * \param[in,out] ennemis un pointeur vers un tableau de string, chaîne de caractères, listant les noms des ennemis touchés par la compétence respectivement (si la compétence passe le test de précision)
   * \param[in,out] degats un pointeur vers un tableau d'unsigned int, listant les dégâts des ennemis touchés par la compétence respectivement (si la compétence passe le test de précision)
   * \param[in,out] xp un unsigned int, somme les points d'expérience gagnés des ennemis vaincus par la compétence (si la compétence passe le test de précision)
   * \return Un booléen, true si la compétence passe le test de précision, false si elle échoue.
   */
  bool joueurUtiliseCompetence(Competence * comp, unsigned int &nbEnnemisTouches, string * &ennemis, unsigned int * &degats, unsigned int &xp);
  /*!
   * \fn bool iemeEnnemiUtiliseCompetence(unsigned int i, Competence * comp, unsigned int &degats)
   * \brief Applique une compétence connue d'un ennemi$
   * \details Si la compétence passe le test de précision, la fonction renvoie true et la compétence est effectivement appliquée.
   * Les paramètres en données-résultats sont modifiés en conséquence.\n
   * Si la compétence échoue au test de précision, la fontion renvoie false, la compétence n'est pas appliquée et les paramètres en données-résultats ne sont pas modifiés.\n
   * La compétence et l'indice de l'ennemi sont passés en paramètres.
   * \param[in,out] i un unsigned int, indice de l'ennemi qui utilise la compétence
   * \param[in,out] comp un pointeur de Compétence, la compétence utilisée
   * \param[in,out] degats un unsigned int, le nombre de dégâts que produit la compétence
   * \return Un booléen, true si la compétence passe le test de précision, false si elle échoue.
   */
  bool iemeEnnemiUtiliseCompetence(unsigned int i, Competence * comp, unsigned int &degats);
  /*!
   * \fn bool iemeEnnemiPresDeJoueur(unsigned int idEnnemi)
   * \brief Fonction: Indique si un certain ennemi se situe sur une case adjacente au joueur
   * \param[in,out] idEnnemi un unsigned int, indice de l'ennemi
   * \return Un booléen, true si l'ennemi se trouve sur une case adjacente au joueur, false sinon.
   */
  bool iemeEnnemiPresDeJoueur(unsigned int idEnnemi); //fait tourner l'ennemi vers le joueur si true
  /*!
   * \fn void deplacerIemeEnnemi(unsigned int i)
   * \brief Procédure: Change la position d'un ennemi
   * \param[in] i un unsigned int, lindice de l'ennemi
   */
  void deplacerIemeEnnemi(unsigned int i);
  /*!
   * \fn bool iemeSauvegardeExistante(unsigned int i) const
   * \brief Fonction: Vérifie si une certaine sauvegarde existe
   * \param[in,out] i un unsigned int, indice de la suavegarde à vérifier
   * \return Un booléen, true si la sauvegarde existe, false sinon
   */
  bool iemeSauvegardeExistante(unsigned int i)const;
  /*!
   * \fn string getInfosIemeSauvegarde(unsigned int i) const
   * \brief Fonction: Retourne les info d'une certaine sauvegarde
   * \param[in] i un unsigned int, indice de la sauvegard à charger
   * \return Un string
   */
  string getInfosIemeSauvegarde(unsigned int i) const;
  /*!
   * \fn void sauvegarderDansIemeFichier(unsigned int i) const
   * \brief Procédure: Sauvegarde les infos du jeu dans un certain fichier
   * \param[in] i un unsigned int, l'indice du fichier de sauvegarde
   */

  void effacerDonjon();
  void sauvegarderDansIemeFichier(unsigned int i)const;
  void supprimerIemeSauvegarde(const unsigned int i)const;
  unsigned int idObjet(const Objet * obj)const;
  unsigned int idEnnemi(const Ennemi * ennmi)const;

private:
  Donjon * donjon;
  Joueur * joueur;

  ListeCompetences lcomp;
  ListeTypesEnnemis lenn;
  ListeCases lcase;
  ListeObjets lobj;
  ListeDonjons ldonj;


  void placerJoueurDansEtageActif();

  bool deplacerJoueurHaut();
  bool deplacerJoueurGauche();
  bool deplacerJoueurBas();
  bool deplacerJoueurDroite();

};

#endif
