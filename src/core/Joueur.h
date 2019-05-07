#ifndef JOUEUR_H
#define JOUEUR_H

#include <string> /*! \headerfile string */
#include "TypeJoueur.h" /*! \headerfile TypeJoueur.h*/
#include "Stats.h" /*! \headerfile Stats.h*/
#include "Competence.h" /*! \headerfile Competence.h*/
#include "ListeCompetences.h" /*! \headerfile ListeCompetences.h*/
#include "ListeObjets.h" /*! \headerfile ListeObjets.h*/
#include "Objet.h" /*! \headerfile Objet.h*/
#include "Ennemi.h" /*! \headerfile Ennemi.h*/
/*!
* \file Joueur.h
* \brief Fichier en-tête d'un Joueur
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 22/03/2019
*/
using namespace std;/*! \namespace std*/

/*!
 * \class Joueur Joueur.h
 * \brief La classe Joueur
 */
class Joueur {

public:
    /*!
     * \fn Joueur()
     * \brief Constructeur par défaut
     *
     * Le joueur regardera vers le bas par défaut.
     */
  Joueur();
  /*!
   * \fn Joueur(const string& nom, const string& nomType, const ListeCompetences & lcomp)
   * \brief Constructeur par copie
   * \param[in] nom un string
   * \param[in] nomType un string
   * \param[in] lcomp un e ListeCompetences
   */
  Joueur(const string& nom, const string& nomType, const ListeCompetences & lcomp);
  /*!
   * \fn Joueur(const unsigned int i, const ListeCompetences & lcomp, const ListeObjets &lobj)
   * \brief Constructeur par copie
   * \param[in] i un unsigned int
   * \param[in] lcomp un ListeCompetences
   * \param[in] lobj un ListeObjets
   */
  Joueur(const unsigned int i, const ListeCompetences & lcomp, const ListeObjets &lobj);
  /*!
   * \brief Destruteur
   */
  ~Joueur();
  /*!
   * \fn string getNom() const
   * \brief Fonction: Retourne le nom du Joueur
   * \return Un string
   */
  string getNom() const;
  /*!
   * \fn unsigned int getX() const
   * \brief Fonction: Retourne la coordonnée X du joueur
   * \return Un unsigned int
   */
  unsigned int getX() const;
  /*!
   * \fn unsigned int getY() const
   * \brief Fonction: Retourne la coordonnée Y du joueur
   * \return Un unsigned int
   */
  unsigned int getY() const;
  /*!
     * \fn unsigned int getDirection() const
     * \brief Fonction: Retourne la direction
     * \details Un nombre correspond à une direction \n
     * Nord  = 1 \n
     * Est   = 2 \n
     * Sud   = 3 \n
     * Ouest = 4 \n
     *
     *\return Un unsigned int
     */
  unsigned int getDirection() const;
  /*!
     * \fn unsigned int getNiveau() const
     * \brief Fonction: Retourne le niveau du joueur
     * \return Un unsigned int
     */
  unsigned int getNiveau() const;
  /*!
   * \fn unsigned int getExp() const
   * \brief Fonction: Retourne le nombre de points d'expérience du joueur
   * \return Un unsigned int
   */
  unsigned int getExp() const;
  /*!
   * \fn unsigned int getExpNivSup() const
   * \brief Fonction: Retourne le nombre de points d'expérience nécessaire pour atteindre le niveau supérieur
   * \return Un unsigned int
   */
  unsigned int getExpNivSup() const;
  /*!
   * \fn const TypeJoueur& getType() const
   * \brief Fonction: Retourne le TypeJoueur du Joueur
   * \details Par exemple mage, guerrier, etc.
   * \return Un TypeJoueur
   */
  const TypeJoueur& getType() const;
  /*!
   *\fn const Stats& getStats() const
   *\brief Fonction: Retourne les statistiques du joueur
   *\return Un Stats
   */
  const Stats& getStats() const;
  /*!
   * \fn unsigned int getNbCompetencesApprises() const
   * \brief Fonction: Retourne le nombre de compétences apprises par le joueur
   * \return Un unsigned int
   */
  unsigned int getNbCompetencesApprises() const;
  /*!
   * \fn Competence * getCompetence(const unsigned int i) const
   * \brief Fonction: Retourne la compétence du joueur
   * \details L'indice de la compétence à retourner est passé en paramètre.
   * \param[in] i un unsigned int, l'indice de la compétence à retourner
   * \return Un pointeur vers une Competence
   */
  Competence * getCompetence(const unsigned int i) const;
  /*!
   * \fn unsigned int getNbObjets() const
   * \brief Fonction: Retourne le nombre d'objets que possède le joueur
   * \return Un unsigned int
   */
  unsigned int getNbObjets() const;
  /*!
   * \fn Objet * getObjet(const unsigned int i) const
   * \brief Fonction: Retourne un objet possédé du joueur
   * \details L'indice de l'objet à retourner est passé en paramètre.
   * \param[in] i un unsigned int, indice de l'objet à retourner
   * \return Un pointeur vers un Objet
   */
  Objet * getObjet(const unsigned int i) const;
  /*!
   * \fn bool inventairePlein() const
   * \brief Fonction: Indique si l'inventaire a atteint sa limite
   * \return Un booléen, true si la limite de l'inventaire est atteinte, false sinon
   */
  bool inventairePlein() const;
  /*!
   * \fn bool estMort() const
   * \brief Fonction: Indique si le joueur est mort
   * \return Un booléen, true si le joueur est mort, false sinon
   */
  bool estMort() const;
  /*!
   * \fn void setX(const unsigned int x)
   * \brief Procédure: Change la coordonnée X
   * \param[in] x un int
   */
  void setX(const unsigned int x);
  /*!
   * \fn void setY(const unsigned int y)
   * \brief Procédure: Change la coordonnée Y
   * \param[in] y un int
   */
  void setY(const unsigned int y);
  /*!
     * \fn void setDirection(const unsigned int dir)
     * \brief Procédure: Oriente le joueur
     * \details La direction à appliquer est donner par un nombre passé en paramètre. \n
     * Nord  = 1 \n
     * Est   = 2 \n
     * Sud   = 3 \n
     * Ouest = 4 \n
     * \param[in] dir un unsigned int, indique la direction à appliquer au joueur
     */
  void setDirection(const unsigned int dir);
  /*!
   * \fn void soinPvMana(const unsigned int gainPv, const unsigned int gainMana)
   * \brief Procédure: Rend des points de vie et du mana au joueur
   * \param[in] gainPv un unsigned int, le nombre de PV à rendre
   * \param[in] gainMana un unsigned int, le nombre de mana à rendre
   */
  void soinPvMana(const unsigned int gainPv, const unsigned int gainMana);
  /*!
     * \fn unsigned int subirDegats(const unsigned int degats)
     * \brief Fonction: Retire les dommages reçus aux points de vie du joueur.
     * \details Le nombre de dommages reçus est passé en paramètre.
     * \param[in] degats un unsigned int, le nombre de dégâts à appliquerau joueur
     * \return Un unsigned int
     */
  unsigned int subirDegats(const unsigned int degats);
  /*!
   * \fn void payerCoutMana(const unsigned int cout)
   * \brief Procédure: Retire le coût de mana d'une compétence au mana du joueur
   * \param[in] cout un unsigned int, coût en mana à retirer de la réserve du joueur
   */
  void payerCoutMana(const unsigned int cout);
  /*!
     * \fn void modifBuffAtkDef(const int buffAtk, const int buffDef)
     * \brief Procédure: Applique les bonus/malus d'attaque et de défense passés en paramètres
     * \param[in] buffAtk un int, le bonus/malus d'attaque à appliquer
     * \param[in] buffDef un int, le bonus/malus de défense à appliquer
     */
  void modifBuffAtkDef(const int buffAtk, const int buffDef);
  /*!
   * \fn void reinitialiserStats()
   * \brief Procédure: Reset total des stats.
   */
  void reinitialiserStats();
  /*!
   * \fn void reinitialiserPvMana()
   * \brief Procédure: Reset de la vie et du mana.
   */
  void reinitialiserPvMana();
  /*!
   * \fn void reinitialiserBuffs()
   * \brief Procédure: Reset des buffs.
   */
  void reinitialiserBuffs();
  /*!
   * \fn void obtenirExp(const unsigned int expGagne)
   * \brief Procédure: Augmente le nombre de points d'expérience
   * \param[in] expGagne un unsigned int, le nombre de points d'expérience à ajouter
   */
  void obtenirExp(const unsigned int expGagne);
  /*!
   * \fn bool peutUtiliserIemeCompetence(const unsigned int i)const
   * \brief Fonction: Vérifie si le joueur peut utiliser une certaine compétence
   * \param[in] i un unsigned int, indice de la compétence
   * \return Un booléen, true si le joueur peut utiliser la compétence,false sinon.
   */
  bool peutUtiliserIemeCompetence(const unsigned int i)const;
  /*!
   * \fn void utiliserIemeObjet(const unsigned int i)
   * \brief Procédure: Utilise un Objet
   * \param[in] i un unsigned int, indice de l'Objet à utiliser
   */
  void utiliserIemeObjet(const unsigned int i);
  /*!
   * \fn void ajouterObjet(Objet * objet)
   * \brief Procédure: Ajoute un objet à l'inventaire
   * \param[in,out] objet un pointeur d'Objet, l'objet ajouté à l'inventaire
   */
  void ajouterObjet(Objet * objet);
  /*!
   * \fn void retirerObjet(const unsigned int i)
   * \brief Procédure: Retire un objet de l'inventaire
   * \param[in] i un unsigned int, indice de l'Objet à retirer
   */
  void retirerObjet(const unsigned int i);

  //postcondition : l'ieme objet est supprimé de l'inventaire et celui ci est reorganisé

private:
  string nom;
  Stats stats;
  TypeJoueur type;
  unsigned int x,y;
  unsigned int direction;
  unsigned int niveau;
  unsigned int exp;
  unsigned int expNivSup;

  unsigned int nbCompetencesApprises;
  Competence ** competences; //un tableau de pointeurs de compétences qui fonctionnera avec "liste compétence")
  unsigned int limiteInventaire;
  unsigned int nbObjets;
  Objet ** inventaire; //un tableau de pointeurs vers objets (qui fonctionnera avec "liste objets")

  const ListeCompetences * lcomp;

  void augmenterNiveau();
//   void apprendreIemeCompetenceDuType(const unsigned int i);
//   void apprendreCompetence();
  void actualiserCompetences();
};

#endif // JOUEUR_H
