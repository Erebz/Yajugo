#ifndef LISTE_COMPETENCES_H
#define LISTE_COMPETENCES_H

#include "Competence.h" /*! \headerfile Competence.h*/
/*!
 * \file ListeCompetences.h
 * \brief Fichier en-tête d'une liste de Competence
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 22/03/2019
 */
struct ListeCompetences {
    /*!
     * \struct ListeCompetences
     * \brief Comprend les caractéristiques d'une liste de Competence.
     */
    unsigned int nbCompetences;/*!< Entier comptant le nombre de compétences total de la liste.*/
    Competence * listeCompetences;/*!< Pointeur vers un tableau de compétences.*/
};
/*!
 * \fn void initialiserListeCompetences(ListeCompetences & liste)
 * \brief Procédure: Initialise une ListeCompetences
 * \param[in,out] liste un ListeCompetences
 */
void initialiserListeCompetences(ListeCompetences & liste);
/*!
 * \fn void effacerListeCompetences(ListeCompetences & liste)
 * \brief Procédure: Efface la liste de compétences passée en paramètre
 * \param[in,out] liste un ListeCompetences, qui sera effacée à la sortie de la procédure
 */
void effacerListeCompetences(ListeCompetences & liste);

#endif // LISTE_COMPETENCES_H
