#ifndef RANDOM_H
#define RANDOM_H
/*!
* \file random.h
* \brief Fichier en-tête pour un tirage aléatoire
* 
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 02/04/2019
*/

/*!
 * \fn unsigned int tirageAleatoire(const unsigned int min, const unsigned int max)
 * \brief Fonction: Fait un tirage aléatoire d'un entier positif
 * \param[in] min un unsigned int, entier minimal positif tirable
 * \param[in] max un unsigned int, entier maxmimal positif tirable
 * \return Un unsigned
 */
unsigned int tirageAleatoire(const unsigned int min, const unsigned int max);

#endif
