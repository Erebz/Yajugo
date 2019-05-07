#include "Ennemi.h" /*! \headerfile "Ennemi.h" */
#include <iostream> /*! \headerfile iostream */
#include <cassert> /*! \headerfile cassert */
#include "random.h" /*! \headerfile "random.h" */

using namespace std; /*! \namespace std*/
/*!
 * \file Ennemi.cpp
 * \brief Fichier cpp de la classe Jeu
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 25/03/2019
 */

Ennemi::Ennemi() {
  x = 0;
  y = 0;
  direction = 0;
  niveau = 0;
  expDonnee = 0;
  competences = NULL;
}

Ennemi::Ennemi(const TypeEnnemi &t, const unsigned int niveau, const ListeCompetences& lcomp) {
  this->niveau = niveau;
  this->type = t;
  initialiserStats(this->stats, this->type, this->niveau); //une fonction d'initialisation de Stats pour les ennemis
  x = 0;
  y = 0;
  direction = 0;
  expDonnee = this->type.coeffXp * niveau;
  this->competences = new Competence* [this->type.nbCompetencesMax];
  for (unsigned int i = 0; i < this->type.nbCompetencesMax; ++i) {
    unsigned int id = this->type.competences[i];
    this->competences[i] = &(lcomp.listeCompetences[id]);
  }
  //cout << "OKIKIDEKIDEKI" << endl;
}

Ennemi::~Ennemi() {
  delete [] this->competences;
  competences = NULL;
}

unsigned int Ennemi::subirDegats(const unsigned int degats) {
  unsigned int defenseActuelle = this->stats.def + (int) (this->stats.def*this->stats.buffDef*0.25);
  unsigned int degatsApplique = 0;

  if (degats > defenseActuelle) {
    degatsApplique = degats - defenseActuelle;
  } else {
    degatsApplique = 0;
  }

  unsigned int delta = degats - degatsApplique;
  degatsApplique += delta*0.25;

  // cout << this->stats.pv << endl;
  // cout << this->stats.def << " " << this->stats.buffDef << endl;
  // cout << degatsApplique << endl;

  //qqchose de bizarre se passe avec Berserker
  //j'ai eu l'impression de faire plus de degats apres que l'ennemi mette son buffDef à -4
  //la formule est foireuse ?

    if (degatsApplique >= this->stats.pv) {
        this->stats.pv = 0;
    } else {
     this->stats.pv -= degatsApplique;
    }

    return degatsApplique;
}

void Ennemi::soinPvMana(const unsigned int gainPv, const unsigned int gainMana){
  this->stats.pv += gainPv;
  if(this->stats.pv > this->stats.pvMax) this->stats.pv = this->stats.pvMax;
  this->stats.mana += gainMana;
  if(this->stats.mana > this->stats.manaMax) this->stats.mana = this->stats.manaMax;
}

void Ennemi::payerCoutMana(const unsigned int cout){ //précondition le cout peut etre payé
  assert(this->stats.mana >= cout);
  this->stats.mana -= cout;
}

void Ennemi::modifBuffAtkDef(const int buffAtk, const int buffDef){

    this->stats.buffAtk += buffAtk;
    if (this->stats.buffAtk > MAX_BUFF) this->stats.buffAtk = MAX_BUFF;
        else if (this->stats.buffAtk < MIN_BUFF) this->stats.buffAtk = MIN_BUFF;

    this->stats.buffDef += buffDef;
    if (this->stats.buffDef > MAX_BUFF) this->stats.buffDef = MAX_BUFF;
        else if (this->stats.buffDef < MIN_BUFF) this->stats.buffDef = MIN_BUFF;

}


unsigned int Ennemi::getX()const{
  return x;
}

unsigned int Ennemi::getY()const{
  return y;
}

unsigned int Ennemi::getDirection()const{
  return direction;
}

unsigned int Ennemi::getNiveau()const{
  return niveau;
}

unsigned int Ennemi::getExpDonnee()const{
  return expDonnee;
}

const TypeEnnemi& Ennemi::getType() const{
  return type;
}

const Stats& Ennemi::getStats()const{
  return stats;
}

Competence* Ennemi::getCompetence(const unsigned int i) const { //precondition : i est un indice valide
    assert(i < this->type.nbCompetencesMax);
    return competences[i];
}

bool Ennemi::peutUtiliserIemeCompetence(unsigned int i)const{
  bool peutUtiliser = true;
  Competence * comp = this->competences[i];
  //la compétence a un cout de mana et potentiellement des dégats de recul
  if(this->stats.mana < comp->coutMana || comp->gainPv + (int) this->stats.pv <= 0) peutUtiliser = false;

  return peutUtiliser;
}

void Ennemi::setCoordonnees(const unsigned int x, const unsigned int y) { //precondition : x et y sont des coordondonnees valides
  this->x = x;
  this->y = y;
}

void Ennemi::setDirection(const unsigned int dir){
  this->direction = dir;
}

void Ennemi::avancer(){
  unsigned int caseX;
  unsigned int caseY;
    switch(this->direction){
    	case 1:
    	  caseX = this->x;
    	  caseY = this->y - 1;
    	break;
    	case 2:
    	  caseX = this->x + 1;
    	  caseY = this->y;
    	break;
    	case 3:
    	  caseX = this->x;
    	  caseY = this->y + 1;
    	break;
    	case 4:
    	  caseX = this->x - 1;
    	  caseY = this->y;
    	break;
    	}

    this->setCoordonnees(caseX, caseY);
}

Competence * Ennemi::choixCompetenceAleatoire()const{ //cette compétence existe toujours : l'attaque normale
  Competence * compChoisie = NULL;
  unsigned int id;

  do{
  id = tirageAleatoire(0, this->getType().nbCompetencesMax -1);
  }while(!this->peutUtiliserIemeCompetence(id));

  compChoisie = this->getCompetence(id);
  return compChoisie;
}

const Ennemi& Ennemi::operator = (const Ennemi & ennemi) {
  this->type = ennemi.getType();
  this->stats = ennemi.getStats();
  this->x = ennemi.getX();
  this->y = ennemi.getY();
  this->direction = ennemi.getDirection();
  this->niveau = ennemi.getNiveau();
  this->expDonnee = ennemi.getExpDonnee();

  if (this->competences != NULL) delete [] this->competences;
  this->competences = new Competence* [this->getType().nbCompetencesMax];
  for (unsigned int i = 0; i < this->getType().nbCompetencesMax; i++) {
    this->competences[i] = ennemi.getCompetence(i);
  }

  return *this;
}
