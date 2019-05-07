#include "Donjon.h" /*! \headerfile "Donjon.h" */
#include <iostream> /*! \headerfile iostream */
#include <cassert> /*! \headerfile cassert */
/*!
 * \file Donjon.cpp
 * \brief Fichier cpp de Donjon
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 25/03/2019
 */

Donjon::Donjon() {
  this->nbEtages = 1;
  this->nbEtagesParcourus = 0;
  this->etages = NULL;
}

Donjon::Donjon(const InfosDonjon &infos, const ListeCases & lcase, const ListeTypesEnnemis & lenn, const ListeObjets & lobj, const ListeCompetences & lcomp) {
this->nom = infos.nom;
  this->nbEtages = infos.nbEtages;
  this->nbEtagesParcourus = 0;
  this->etages = new Etage[this->nbEtages];
  for(unsigned int i=0; i < this->nbEtages; i++){
    Etage etage(infos.etages[i], lcase, lcomp, lenn, lobj);
    this->etages[i] = etage;
  }
  //etageActif = Etage(lc, lt, lo);
}

Donjon::~Donjon() {
  //rien à faire pour l'instant, mais pour générer etage.txt
  //on aura des infos allouées sur le tas
  delete[] this->etages;
  this->etages = NULL;
}


string Donjon::getNom()const{
    return this->nom;
 }

// const Etage& Donjon::getEtageActif()const{
//   return this->etageActif;
// }
const Etage& Donjon::getEtage(const unsigned int i) const { //precondition : i est un indice valide
    assert(i < this->nbEtages);
    return this->etages[i];
}

const Etage& Donjon::getEtageActif() const {
    return this->etages[this->nbEtagesParcourus];
}

Etage& Donjon::getEtageOriginal(const unsigned int i) { //precondition : i est un indice valide
    assert(i < this->nbEtages);
    return this->etages[i];
}

Etage& Donjon::getEtageActifOriginal() {
    return this->etages[this->nbEtagesParcourus];
}

unsigned int Donjon::getNbEtages() const {
  return this->nbEtages;
}

unsigned int Donjon::getNbEtagesParcourus() const {
  return this->nbEtagesParcourus;
}

void Donjon::augmenterNbEtagesParcourus() {
    this->nbEtagesParcourus++;
}
