#ifndef ENNEMI_H
#define ENNEMI_H

#include <string> /*! \headerfile string*/
#include "TypeEnnemi.h" /*! \headerfile TypeEnnemi.h*/
#include "ListeCompetences.h" /*! \headerfile ListeCompetences.h*/
#include "Stats.h" /*! \headerfile Stats.h */
#include "Competence.h" /*! \headerfile Competence.h*/
using namespace std; /*! \namespace std*/
/*!
* \file Ennemi.h
* \brief Fichier en-tête de la classe Ennemi
* 
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 22/03/2019
*/
/*!
 * \class Ennemi Ennemi.h
 * \brief La classe Ennemi
 */
class Ennemi {
 public:
     /*!
      * \brief Constructeur par défaut
      * 
      * 
      */
    Ennemi();
    /*!
     * \brief Constructeur par copie
     * 
     * \param[in] t un TypeEnnemi
     * \param[in] niveau un unsigned int
     * \param[in] lcomp un ListeCompetences
     */
    Ennemi(const TypeEnnemi &t, const unsigned int niveau, const ListeCompetences& lcomp);
    /*!
     * \brief Destructeur
     * 
     * Destructeur de la classe Ennemi.
     */
    ~Ennemi();

    /*!
     * \fn unsigned int getX() const
     * \brief Fonction: Retourne la coordonnée X de l'ennemi
     * \return Un unsigned int
     */
    unsigned int getX() const;
    /*!
     * \fn unsigned int getY() const
     * \brief Fonction: Retourne la coordonnée Y de l'ennemi
     * \return Un unsigned int
     */
    unsigned int getY() const;
    /*!
     * \fn unsigned int getDirection() const
     * \brief Fonction: Retourne la direction 
     * \details Chaque nombre correspond à une direction \n
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
     * \brief Fonction: Retourne le niveau de l'ennemi
     * \return Un unsigned int
     */
    unsigned int getNiveau() const;
    /*!
     * \fn unsigned int getExpDonnee() const
     * \brief Fonction: Retourne le nombre de points d'expérience donnés quand l'ennemi est vaincu
     * \return Un unsigned int
     */
    unsigned int getExpDonnee()const;
    /*!
     * \fn const TypeEnnemi& getType() const
     * \brief Fonction: Retourne le type de l'ennemi.
     * \details Par exemple un blob, un gobelin, une chauve-souris, etc.
     * \return Un TypeEnnemi
     */
    const TypeEnnemi& getType() const;
    /*!
     * \fn const Stats& getStats() const
     * \brief Fonction: Retourne les statistiques de l'ennemi
     * \return Un Stats
     */
    const Stats& getStats() const;
    /*!
     * \fn Competence* getCompetence(const unsigned int i) const
     * \brief Fonction: Retourne le pointeur d'une compétence de l'ennemi
     * \details L'indice de la compétence à retourner est passé en paramètre.
     * \param[in] i un unsigned int, indice de la compétence à retourner
     * \return Un pointeur vers une Competence
     */
    Competence* getCompetence(const unsigned int i) const;
    bool peutUtiliserIemeCompetence(unsigned int i)const;
    /*!
     * \fn void setCoordonnees(const unsigned int x, const unsigned int y)
     * \brief Procédure: Positionne l'ennemi via les coordonnées passées en paramètres.
     * \param[in] x un unsigned int, abscisse à appliquer
     * \param[in] y un unsigned int, ordonnée à appliquer
     */
    void setCoordonnees(const unsigned int x, const unsigned int y);
    /*!
     * \fn void setDirection(const unsigned int dir)
     * \brief Procédure: Oriente l'ennemi
     * \details La direction à appliquer est donner par un nombre passé en paramètre. \n
     * Nord  = 1 \n
     * Est   = 2 \n
     * Sud   = 3 \n
     * Ouest = 4 \n
     * \param[in] dir un unsigned int, indique la direction à appliquer à l'ennemi
     */
    void setDirection(const unsigned int dir);
    /*!
     * \fn void avancer()
     * \brief Procédure: Fait avancer l'ennemi
     */
    void avancer();
    Competence * choixCompetenceAleatoire()const;
    /*!
     * \fn void subirDegats(const unsigned int degats)
     * \brief Procédure: Retire les dommages reçus aux points de vie de l'ennemi.
     * \details Le nombre de dommages reçus est passé en paramètre.
     * \param[in] degats un unsigned int, le nombre de dégâts à appliquer à l'ennemi
     */
    unsigned int subirDegats(const unsigned int degats);
    /*!
     * \fn void modifBuffAtkDef(const int buffAtk, const int buffDef)
     * \brief Procédure: Applique les bonus/malus d'attaque et de défense passés en paramètres
     * \param[in] buffAtk un int, le bonus/malus d'attaque à appliquer
     * \param[in] buffDef un int, le bonus/malus de défense à appliquer
     */
    void soinPvMana(const unsigned int gainPv, const unsigned int gainMana);
    void payerCoutMana(const unsigned int cout);
    void modifBuffAtkDef(const int buffAtk, const int buffDef);
    /*!
     * \fn const Ennemi& operator = (const Ennemi & ennemi)
     * \brief Opérateur: Surcharge de l'opérateur =
     * \details Initalise l'ennemi par copie de celui passé en paramètre.
     * \param[in] ennemi un Ennemi
     */
    const Ennemi& operator = (const Ennemi & ennemi);

private:
    TypeEnnemi type;
    Stats stats;
    unsigned int x,y;
    unsigned int direction;
    unsigned int niveau;
    unsigned int expDonnee;
    
    //à faire un TableauDynamique
    Competence ** competences; //un tableau de pointeurs de compétences qui fonctionnera avec "liste compétence")
    //sa taille est égale à type.nbCompetenceMax.
};

#endif // ENNEMI_H
