#include "Joueur.h" /*! \headerfile "Joueur.h" */
#include <iostream> /*! \headerfile iostream */
#include <fstream> /*! \headerfile fstream */
#include <cassert> /*! \headerfile cassert */
#include "random.h" /*! \headerfile "random.h" */
using namespace std; /*! \namespace std */

#define LIM_INV 10; /*! \def LIM_INV */
/*!
 * \file Joueur.cpp
 * \brief Fichier en-tête de la classe Joueur
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 25/03/2019
 */


Joueur::Joueur() {
  nom = "";
  x = 0;
  y = 0;

  direction = 3;
  //le joueur regarde vers le bas par defaut

  niveau = 0;
  exp = 0;
  expNivSup = 0;

  nbCompetencesApprises = 0;
  competences = NULL;

  limiteInventaire = 0;
  nbObjets = 0;
  inventaire = NULL;
}

Joueur::Joueur(const string &nom, const string &nomType, const ListeCompetences & lcomp) {
  this->nom = nom;
  x = 0;
  y = 0;

  direction = 3;

  this->lcomp = &lcomp;

  initialiserTypeJoueur(this->type, nomType);
  initialiserStats(this->stats, nomType);

  niveau = 1;
  exp = 0;
  expNivSup = niveau * 100;

  nbCompetencesApprises = 0; //apprentissage de l'attaque normale d'id 0
  this->competences = NULL;
  actualiserCompetences();

  limiteInventaire = LIM_INV;
  nbObjets = 0;
  inventaire = new Objet * [limiteInventaire];
}

Joueur::Joueur(const unsigned int i, const ListeCompetences & lcomp, const ListeObjets &lobj){
  this->lcomp = &lcomp;
  string emplacement = "data/Sauvegardes/Sauvegarde";
  string format = ".txt";
  char id = i + 48;
  string sauvegarde = emplacement + id + format;

  ifstream fichier(sauvegarde.c_str());
  if(fichier.is_open()){
   string nomType;
   char c;
   fichier >> c >> c;
   getline(fichier, this->nom, ';');
   getline(fichier, nomType, ';');
   initialiserTypeJoueur(this->type, nomType);
   fichier >> this->niveau >> c;
   fichier >> this->exp >> c;
   this->expNivSup = this->niveau * 100;
   this->x = 0;
   this->y = 0;
   this->direction = 3;

   //apprentissage des compétences :
   this->nbCompetencesApprises = 0;
   this->competences = NULL;
   actualiserCompetences();

   //lecture stats :
   fichier >> stats.pvMax >> c;
   this->stats.pv = this->stats.pvMax;
   fichier >> stats.manaMax >> c;
   this->stats.mana = this->stats.manaMax;
   fichier >> stats.atk >> c;
   fichier >> stats.def >> c;
   this->stats.buffAtk = 0;
   this->stats.buffDef = 0;

   //lecture objets :
   fichier >> this->nbObjets >> c;
   limiteInventaire = LIM_INV;
   inventaire = new Objet * [limiteInventaire];
   unsigned int idObjet;
   for(unsigned int i=0; i < this->nbObjets; i++){
     fichier >> idObjet >> c;
     inventaire[i] = &(lobj.listeObjets[idObjet]);
   }

   fichier.close();
  }
}

Joueur::~Joueur() {
  delete [] competences;
  delete [] inventaire;
  effacerTypeJoueur(this->type);
}

// void Joueur::apprendreIemeCompetenceDuType(const unsigned int i){
//
//   Competence ** temp;
//   temp = new Competence* [this->nbCompetencesApprises + 1];
//   for(unsigned int j = 0; j < this->nbCompetencesApprises; ++j) {
//   	temp[j] = this->competences[j];
//   }
//   temp[this->nbCompetencesApprises] =  &(this->lcomp->listeCompetences[this->type.competences[i]]);
//   if (this->competences != NULL) delete [] this->competences;
//   competences = temp;
//   this->nbCompetencesApprises++;
// }
//
// void Joueur::apprendreCompetence(){ //teste si le joueur peut apprendre une competence et lui fait apprendre
//   bool peutApprendre = false;
//   unsigned int k=0;
//   while(k < this->type.nbApprentissagesMax){
//     if(niveau == this->type.caps[k]) {
//       peutApprendre = true;
//       break;
//     }
//     k++;
//   }
//   if(peutApprendre){
//     apprendreIemeCompetenceDuType(k);
//   }
// }

void Joueur::actualiserCompetences() { //fait en sorte que les competences du joueur soient en adequation avec ce qu'il est censé savoir à son niveau
    Competence ** temp = new Competence* [this->type.nbApprentissagesMax];
    unsigned int i = 0;
    while (i < this->type.nbApprentissagesMax && niveau >= this->type.caps[i]) {
        temp[i] = &(this->lcomp->listeCompetences[this->type.competences[i]]);
        ++i;
    }
    if (i > this->nbCompetencesApprises) {
        this->nbCompetencesApprises = i;
        delete [] competences;
        competences = new Competence* [this->nbCompetencesApprises];
        for(unsigned int j = 0; j < this->nbCompetencesApprises; ++j) {
            this->competences[j] = temp[j];
        }
    }
    delete [] temp;
}

void Joueur::augmenterNiveau(){
  niveau = niveau + 1;
  expNivSup = niveau * 100;
//   this->stats.pvMax *= this->type.coeffPv; //ajouter du random ici si on veut
//   this->stats.pv = this->stats.pvMax;
//   this->stats.manaMax *= this->type.coeffMana;
//   this->stats.mana = this->stats.manaMax;
//   this->stats.atk *= this->type.coeffAtk;
//   this->stats.def *= this->type.coeffDef;
  this->stats.pvMax += tirageAleatoire(this->type.coeffPvMin, this->type.coeffPvMax);
  this->stats.manaMax += tirageAleatoire(this->type.coeffManaMin, this->type.coeffManaMax);
  this->reinitialiserPvMana();
  this->stats.atk += tirageAleatoire(this->type.coeffAtkMin, this->type.coeffAtkMax);
  this->stats.def += tirageAleatoire(this->type.coeffDefMin, this->type.coeffDefMax);
  if(this->stats.buffAtk < 0) this->stats.buffAtk = 0;
  if(this->stats.buffDef < 0) this->stats.buffDef = 0;
  actualiserCompetences();
}

void Joueur::obtenirExp(const unsigned int expGagne){
  this->exp += expGagne;
  while(this->exp >= this->expNivSup){
    this->exp = this->exp - this->expNivSup;
    this->augmenterNiveau();
  }
}
bool Joueur::peutUtiliserIemeCompetence(const unsigned int i) const{
  bool peutUtiliser = true;
  Competence * comp = this->competences[i];
  //la compétence a un cout de mana et potentiellement des dégats de recul
  if(this->stats.mana < comp->coutMana || comp->gainPv + (int) this->stats.pv <= 0) peutUtiliser = false;

  return peutUtiliser;
}

void Joueur::utiliserIemeObjet(const unsigned int i){ //precondition : i est un indice valide
  Objet* obj = this->getObjet(i);
  this->soinPvMana(obj->gainPv, obj->gainMana);
  this->modifBuffAtkDef(obj->buffAtk, obj->buffDef);
  this->retirerObjet(i);
}//postcondition : l'ieme objet est supprimé de l'inventaire et celui ci est reorganisé


void Joueur::ajouterObjet(Objet * objet) {  //precondition : l'inventaire n'est pas plein
    assert(this->nbObjets < this->limiteInventaire);
    this->inventaire[nbObjets] = objet;
    this->nbObjets++;
}

void Joueur::retirerObjet(const unsigned int i) { //precondition : i est un indice valide
    assert(i < this->nbObjets);
    for (unsigned int k = 0; k < this->nbObjets; k++) {
        if (k > i) this->inventaire[k-1] = this->inventaire[k];
    }
    this->nbObjets--;
    this->inventaire[this->nbObjets] = NULL;
}

string Joueur::getNom() const {
  return nom;
}

unsigned int Joueur::getX() const {
  return x;
}

unsigned int Joueur::getY() const {
  return y;
}

unsigned int Joueur::getDirection() const {
  return direction;
}

unsigned int Joueur::getNiveau() const {
  return niveau;
}

unsigned int Joueur::getExp() const {
  return exp;
}

unsigned int Joueur::getExpNivSup() const {
  return expNivSup;
}

const TypeJoueur& Joueur::getType() const {
  return type;
}

const Stats& Joueur::getStats() const {
  return stats;
}

unsigned int Joueur::getNbCompetencesApprises() const {
  return nbCompetencesApprises;
}

Competence * Joueur::getCompetence(const unsigned int i) const { //precondition : i est un indice valide
    assert(i < this->nbCompetencesApprises);
    return competences[i];
}

Objet * Joueur::getObjet(const unsigned int i) const { //precondition : i est un indice valide
    assert(i < this->nbObjets);
    return inventaire[i];
}

unsigned int Joueur::getNbObjets() const {
    return this->nbObjets;
}

bool Joueur::inventairePlein() const {
    return this->nbObjets >= this->limiteInventaire;
}

bool Joueur::estMort() const{
  return this->stats.pv <= 0;
}

void Joueur::setX(const unsigned int x) {
    this->x = x;
}

void Joueur::setY(const unsigned int y) {
    this->y = y;
}

void Joueur::setDirection(const unsigned int dir) {
    this->direction = dir;
}

void Joueur::soinPvMana(const unsigned int gainPv, const unsigned int gainMana){
  this->stats.pv += gainPv;
  if(this->stats.pv > this->stats.pvMax) this->stats.pv = this->stats.pvMax;
  this->stats.mana += gainMana;
  if(this->stats.mana > this->stats.manaMax) this->stats.mana = this->stats.manaMax;
}

unsigned int Joueur::subirDegats(const unsigned int degats) {
  unsigned int defenseActuelle = this->stats.def + (int) (this->stats.def*this->stats.buffDef*0.25);
  unsigned int degatsApplique = 0;

  if (degats > defenseActuelle) {
    degatsApplique = degats - defenseActuelle;
  } else {
    degatsApplique = 0;
  }

  unsigned int delta = degats - degatsApplique;
  degatsApplique += delta*0.25;

    if (degatsApplique >= this->stats.pv) {
        this->stats.pv = 0;
    } else {
     this->stats.pv -= degatsApplique;
    }

    return degatsApplique;
}

void Joueur::payerCoutMana(const unsigned int cout){ //précondition le cout peut etre payé
  assert(this->stats.mana >= cout);
  this->stats.mana -= cout;
}

void Joueur::modifBuffAtkDef(const int buffAtk, const int buffDef){
  this->stats.buffAtk += buffAtk;
  if (this->stats.buffAtk > MAX_BUFF) this->stats.buffAtk = MAX_BUFF;
  else if (this->stats.buffAtk < MIN_BUFF) this->stats.buffAtk = MIN_BUFF;

  this->stats.buffDef += buffDef;
  if (this->stats.buffDef > MAX_BUFF) this->stats.buffDef = MAX_BUFF;
  else if (this->stats.buffDef < MIN_BUFF) this->stats.buffDef = MIN_BUFF;

}

void Joueur::reinitialiserStats(){
  this->reinitialiserPvMana();
  this->reinitialiserBuffs();
}

void Joueur::reinitialiserPvMana(){
  this->stats.pv = this->stats.pvMax;
  this->stats.mana = this->stats.manaMax;
}

void Joueur::reinitialiserBuffs(){
  this->stats.buffAtk = 0;
  this->stats.buffDef = 0;
}
