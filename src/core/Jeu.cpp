#include <iostream> /*! \headerfile iostream */
#include "Jeu.h" /*! \headerfile "Jeu.h" */
#include "random.h" /*! \headerfile "random.h" */
using namespace std; /*! \namespace *std */
/*!
 * \file Jeu.h
 * \brief Fichier cpp de la classe Jeu
 * \author J. Grosjean, Y. Hamdi, H. Messina
 * \version 1.0
 * \date 25/03/2019
 */



Jeu::Jeu() {
  initialiserListeCompetences(this->lcomp);
  initialiserListeObjets(this->lobj);
  initialiserListeTypesEnnemis(this->lenn);
  initialiserListeCases(this->lcase);
  initialiserListeDonjons(this->ldonj);
  cout << "listes crees" << endl;

  this->donjon = NULL;
  this->joueur = NULL;
}

Jeu::Jeu(const string& nom, const string& nomType) {

  initialiserListeCompetences(this->lcomp);
  initialiserListeObjets(this->lobj);
  initialiserListeTypesEnnemis(this->lenn);
  initialiserListeCases(this->lcase);
  initialiserListeDonjons(this->ldonj);

  this->joueur = new Joueur(nom, nomType, this->lcomp);
  this->donjon = NULL;
}

Jeu::Jeu(const unsigned int i) {
  initialiserListeCompetences(this->lcomp);
  initialiserListeObjets(this->lobj);
  initialiserListeCases(this->lcase);
  initialiserListeTypesEnnemis(this->lenn);
  initialiserListeDonjons(this->ldonj);

  this->joueur = new Joueur(i, lcomp, lobj);
  this->donjon = NULL;
}

Jeu::~Jeu() {
  delete this->donjon;
  this->donjon = NULL;
  delete this->joueur;
  this->joueur = NULL;

  effacerListeCompetences(this->lcomp);
  effacerListeObjets(this->lobj);
  effacerListeTypesEnnemis(this->lenn);
  effacerListeCases(this->lcase);
  effacerListeDonjons(this->ldonj);
  cout << "listes effacees" << endl;
}

void Jeu::genererDonjon(const unsigned int idDonjon) {
  if (this->donjon != NULL) delete this->donjon;
  this->donjon = new Donjon(ldonj.donjonsDisponibles[idDonjon], this->lcase, this->lenn, this->lobj, this->lcomp);
  this->placerJoueurDansEtageActif();
}

void Jeu::genererJoueur(const string& nom, const string& nomType){
    this->joueur = new Joueur(nom, nomType, this->lcomp);
}

void Jeu::genererJoueur(const unsigned int i){
    this->joueur = new Joueur(i, lcomp, lobj);
}

void Jeu::placerJoueurDansEtageActif() {
  const Etage* etage = &(this->donjon->getEtageActif());
  unsigned int x = 0, y = 0;
  do {
    x = tirageAleatoire(0, etage->getTailleX() - 1);
    y = tirageAleatoire(0, etage->getTailleY() - 1);
  } while (!etage->caseDisponible(x, y));

  this->joueur->setX(x);
  this->joueur->setY(y);
}

const Donjon& Jeu::getDonjon() const {
  return *(this->donjon);
}

const Joueur& Jeu::getJoueur() const {
  return *(this->joueur);
}

Donjon& Jeu::getDonjonOriginal() const {
  return *(this->donjon);
}

Joueur& Jeu::getJoueurOriginal() const {
  return *(this->joueur);
}

const ListeCompetences& Jeu::getListeCompetences() const {
  return this->lcomp;
}

const ListeTypesEnnemis& Jeu::getListeTypesEnnemis() const {
  return this->lenn;
}

const ListeCases& Jeu::getListeCases() const {
  return this->lcase;
}

const ListeObjets& Jeu::getListeObjets() const {
  return this->lobj;
}

const ListeDonjons& Jeu::getListeDonjons() const {
  return this->ldonj;
}

void Jeu::effacerDonjon(){
  if(this->donjon != NULL) delete this->donjon;
  this->donjon = NULL;
}

bool Jeu::iemeSauvegardeExistante(unsigned int i)const{
  bool existe = false;
  string nom = "data/Sauvegardes/Sauvegarde";
  string format = ".txt";
  char id = i + 48;
  string sauvegarde = nom + id + format;
  ifstream fichier(sauvegarde.c_str());
  char c;
  if(fichier.is_open()){
    fichier >> c;
    existe = (bool) (c - 48);
    fichier.close();
  }

  return existe;
}

string Jeu::getInfosIemeSauvegarde(unsigned int i) const{
  string infos="";
  string emplacement = "data/Sauvegardes/Sauvegarde";
  string format = ".txt";
  char id = i + 48;
  string sauvegarde = emplacement + id + format;
  ifstream fichier(sauvegarde.c_str());

  string nom="";
  string type;
  unsigned int niveau=0;
  char c;
  if(fichier.is_open()){
    fichier >> c >> c;
    getline(fichier, nom, ';');
    getline(fichier, type, ';');
    fichier >> niveau;
    fichier.close();
  }
  infos = nom + ", " + type + " de niveau " + std::to_string(niveau);
  return infos;
}

unsigned int Jeu::idObjet(const Objet * obj)const{
  unsigned int k=0;
  while (k < lobj.nbObjets){
    if (obj == &(lobj.listeObjets[k])) break;
    k++;
  }
  return k;
}

unsigned int Jeu::idEnnemi(const Ennemi * ennemi)const{
  unsigned int k=0;
  while (k < lenn.nbTypesEnnemis){
    if (ennemi->getType().nom == lenn.listeTypesEnnemis[k].nom) break;
    k++;
  }
  return k;
}

void Jeu::sauvegarderDansIemeFichier(unsigned int i)const{
  string emplacement = "data/Sauvegardes/Sauvegarde";
  string format = ".txt";
  char id = i + 48;
  string sauvegarde = emplacement + id + format;
  ofstream fichier(sauvegarde.c_str());
  if(fichier.is_open()){
    Stats s = this->joueur->getStats();
    string info;
    fichier << std::to_string(1);
    fichier << "\n>";
    fichier << this->joueur->getNom() + ";";
    fichier << this->joueur->getType().nom + "; ";
    fichier << std::to_string(this->joueur->getNiveau()) + " , ";
    fichier << std::to_string(this->joueur->getExp()) + " ,\n";
    fichier << std::to_string(s.pvMax) + " / ";
    fichier << std::to_string(s.manaMax) + " / ";
    fichier << std::to_string(s.atk) + " / ";
    fichier << std::to_string(s.def) + " / \n";
    fichier << std::to_string(this->joueur->getNbObjets()) + " : ";
    for(unsigned int j=0; j < this->joueur->getNbObjets(); j++){
      fichier << std::to_string((idObjet(this->joueur->getObjet(j)))) + " / ";
    }

    fichier.close();
  }
}

void Jeu::supprimerIemeSauvegarde(const unsigned int i)const{
  string emplacement = "data/Sauvegardes/Sauvegarde";
  string format = ".txt";
  char id = i + 48;
  string sauvegarde = emplacement + id + format;
  ofstream fichier(sauvegarde.c_str());
  if(fichier.is_open()){
    fichier << std::to_string(0);
    fichier.close();
  }
}

bool Jeu::deplacerJoueurHaut() {
  bool deplacementEffectue = false;

  if (this->joueur->getDirection() != 1) {
    this->joueur->setDirection(1);
  } else {
    unsigned int x = this->joueur->getX();
    unsigned int y = (this->joueur->getY()) - 1;
    if (this->donjon->getEtageActif().caseDisponible(x, y)) {
      this->joueur->setY(y);
      deplacementEffectue = true;
    }
  }

  return deplacementEffectue;
}

bool Jeu::deplacerJoueurGauche() {
  bool deplacementEffectue = false;
  if (this->joueur->getDirection() != 4) {
    this->joueur->setDirection(4);
  } else {
    unsigned int x = this->joueur->getX() - 1;
    unsigned int y = (this->joueur->getY());
    if (this->donjon->getEtageActif().caseDisponible(x, y)) {
      this->joueur->setX(x);
      deplacementEffectue = true;
    }
  }

  return deplacementEffectue;
}

bool Jeu::deplacerJoueurBas() {
  bool deplacementEffectue = false;

  if (this->joueur->getDirection() != 3) {
    this->joueur->setDirection(3);
  } else {
    unsigned int x = this->joueur->getX();
    unsigned int y = (this->joueur->getY()) + 1;
    if (this->donjon->getEtageActif().caseDisponible(x, y)) {
      this->joueur->setY(y);
      deplacementEffectue = true;
    }
  }

  return deplacementEffectue;
}

bool Jeu::deplacerJoueurDroite() {
  bool deplacementEffectue = false;

  if (this->joueur->getDirection() != 2) {
    this->joueur->setDirection(2);
  } else {
    unsigned int x = this->joueur->getX() + 1;
    unsigned int y = (this->joueur->getY());
    if (this->donjon->getEtageActif().caseDisponible(x, y)) {
      this->joueur->setX(x);
      deplacementEffectue = true;
    }
  }

  return deplacementEffectue;
}

void Jeu::monterEtageSuivant() {
  this->donjon->augmenterNbEtagesParcourus();
  this->joueur->reinitialiserBuffs();
  this->placerJoueurDansEtageActif();
}

bool Jeu::actionClavierDeplacementJoueur(const char touche) {
  bool deplacementEffectue = false;
  switch(touche) {
    case 'z' : deplacementEffectue = deplacerJoueurHaut();
    break;
    case 'q' : deplacementEffectue = deplacerJoueurGauche();
    break;
    case 's' : deplacementEffectue = deplacerJoueurBas();
    break;
    case 'd' : deplacementEffectue = deplacerJoueurDroite();
    break;
    default: break;
  }

  //bool monteeEtage = false;
  if (deplacementEffectue) {
    unsigned int x = this->joueur->getX();
    unsigned int y = this->joueur->getY();
    Case caseJoueur = this->donjon->getEtageActif().getCase(x, y);

    if ((caseJoueur.objet != NULL) && (!this->joueur->inventairePlein())) {
      this->joueur->ajouterObjet(caseJoueur.objet);
      this->donjon->getEtageActifOriginal().retirerObjetCase(x, y);
    }
  }

  //return monteeEtage;
  return deplacementEffectue;
}

bool Jeu::joueurUtiliseCompetence(Competence * comp, unsigned int &nbEnnemisTouches, string * &ennemis, unsigned int * &degats, unsigned int &xp){
  bool attaqueReussie = true;

  if(tirageAleatoire(0, 100) <= comp->precision){
    this->joueur->payerCoutMana(comp->coutMana);
    if(comp->portee > 0) {
      //comptence sur un ennemi

      bool presenceEnnemi = false;
      bool arret = false;
      Ennemi * cible;
      unsigned int k=1;
      unsigned int idEnnemi;
      unsigned int jY = this->joueur->getY();
      unsigned int jX = this->joueur->getX();
      Etage * etage = &(this->donjon->getEtageActifOriginal());
      unsigned int coordCaseX;
      unsigned int coordCaseY;
      while(k < comp->portee + 1 && !arret){
        switch(joueur->getDirection()){
          case 1:
          coordCaseX = jX;
          coordCaseY = jY - k;
          break;
          case 2:
          coordCaseX = jX + k;
          coordCaseY = jY;
          break;
          case 3:
          coordCaseX = jX;
          coordCaseY = jY + k;
          break;
          case 4:
          coordCaseX = jX - k;
          coordCaseY = jY;
          break;
          default: break;
        }

        if(etage->getCase(coordCaseX,coordCaseY).traversable){
          for (unsigned int i = 0; i < etage->getNbEnnemis(); i++) {
            presenceEnnemi = false;
            if (etage->getEnnemi(i).getX() == coordCaseX && etage->getEnnemi(i).getY() == coordCaseY){
              presenceEnnemi = true;
              idEnnemi = i;
            }

            if(presenceEnnemi){
              unsigned int *tempDegats = NULL;
              string * tempEnnemis = NULL;

              cible = &(etage->getEnnemiOriginal(idEnnemi));
              //calcul dgats :
              // int degatsRealises = comp->degats + (int) joueur->getStats().buffAtk*0.25*joueur->getStats().atk;
              unsigned int degatsRealises = comp->degats + joueur->getStats().atk + (int) (joueur->getStats().buffAtk*0.25*joueur->getStats().atk);
              // degatsRealises = 1000;
              unsigned int degatsEffectifs = cible->subirDegats(degatsRealises);

              //stockage des informations du combat
              tempDegats = new unsigned int[nbEnnemisTouches + 1];
              tempEnnemis = new string[nbEnnemisTouches + 1];
              for(unsigned int j=0; j<nbEnnemisTouches; j++){
                tempDegats[j] = degats[j];
                tempEnnemis[j] = ennemis[j];
              }
              tempDegats[nbEnnemisTouches] = degatsEffectifs;
              tempEnnemis[nbEnnemisTouches] = cible->getType().nom;
              delete[] degats;
              delete[] ennemis;
              nbEnnemisTouches ++;
              degats = tempDegats;
              ennemis = tempEnnemis;

              //appliquer les effets de la comptence  l'ennemi
              cible->modifBuffAtkDef(comp->buffAtkCible, comp->buffDefCible);

              if(cible->getStats().pv == 0){
                xp += cible->getExpDonnee();
                joueur->obtenirExp(cible->getExpDonnee());
                etage->retirerIemeEnnemi(idEnnemi);
              }

              if(!comp->transperce) arret = true; //si l'attaque ne transperce pas, on s'arrete au premier ennemi
              cible = NULL;
            }
          }
        }else{
          arret = true; //les murs stoppent les attaques
        }
        k++;
      }
      //if(nbEnnemisTouches == 0) attaqueReussie = false;
    }

    //applique les effets de la comptence au joueur
    this->joueur->modifBuffAtkDef(comp->buffAtk, comp->buffDef);
    this->joueur->soinPvMana(comp->gainPv, comp->gainMana);

  } else {
    attaqueReussie = false; // test de prcision chou
  }



  return attaqueReussie;
}

bool Jeu::iemeEnnemiPresDeJoueur(unsigned int idEnnemi){
  bool presDeJoueur = false;
  Ennemi * ennemi = &(this->donjon->getEtageActifOriginal().getEnnemiOriginal(idEnnemi));
  bool stop = false;
  unsigned int direction = 1;

  unsigned int eX = ennemi->getX();
  unsigned int eY = ennemi->getY();
  unsigned int jX = this->joueur->getX();
  unsigned int jY = this->joueur->getY();
  unsigned int x;
  unsigned int y;

  while(direction <= 4 && !stop){
    switch(direction){
      case 1:
      x = eX;
      y = eY - 1;
      break;
      case 2:
      x = eX + 1;
      y = eY;
      break;
      case 3:
      x = eX;
      y = eY + 1;
      break;
      case 4:
      x = eX - 1;
      y = eY;
      stop = true;
      break;
      default:
      stop = true;
      break;
    }

    if(x == jX && y== jY){
      ennemi->setDirection(direction);
      presDeJoueur = true;
      stop = true;
    }

    direction ++;
  }

  return presDeJoueur;
}

void Jeu::deplacerIemeEnnemi(unsigned int i){
  Ennemi * ennemi = &(this->donjon->getEtageActifOriginal().getEnnemiOriginal(i));
  const Etage * etage = &(this->donjon->getEtageActif());
  bool deplacementPossible = false;
  unsigned int direction = 1;

  unsigned int eX = ennemi->getX();
  unsigned int eY = ennemi->getY();
  unsigned int caseX;
  unsigned int caseY;

  for(unsigned int k=1; k <= 4; k++){
    switch(k){
      case 1:
      caseX = eX;
      caseY = eY - 1;
      break;
      case 2:
      caseX = eX + 1;
      caseY = eY;
      break;
      case 3:
      caseX = eX;
      caseY = eY + 1;
      break;
      case 4:
      caseX = eX - 1;
      caseY = eY;
      break;
    }

    if(etage->caseDisponible(caseX, caseY)) deplacementPossible = true;
  }

  if(deplacementPossible){
    do{
      direction = tirageAleatoire(1,4);
      switch(direction){
        case 1:
        caseX = eX;
        caseY = eY - 1;
        break;
        case 2:
        caseX = eX + 1;
        caseY = eY;
        break;
        case 3:
        caseX = eX;
        caseY = eY + 1;
        break;
        case 4:
        caseX = eX - 1;
        caseY = eY;
        break;
      }
    }while(!etage->caseDisponible(caseX, caseY));

    ennemi->setDirection(direction);
    ennemi->avancer();

  }

}

bool Jeu::iemeEnnemiUtiliseCompetence(unsigned int i, Competence * comp, unsigned int &degats){
  bool attaqueReussie = true;
  Ennemi * ennemi = &(this->donjon->getEtageActifOriginal().getEnnemiOriginal(i));

  if(tirageAleatoire(0, 100) <= comp->precision){
    if(comp->portee > 0) {
      //comptence sur le joueur
      unsigned int degatsRealises = comp->degats + ennemi->getStats().atk + (int) (ennemi->getStats().buffAtk*0.25*ennemi->getStats().atk);
      //stockage des infos de combats
      degats = this->joueur->subirDegats(degatsRealises);
      //appliquer les effets de la comptence au joueur
      this->joueur->modifBuffAtkDef(comp->buffAtkCible, comp->buffDefCible);
    }

    //applique les effets de la comptence  l'ennemi
    ennemi->modifBuffAtkDef(comp->buffAtk, comp->buffDef);
    ennemi->soinPvMana(comp->gainPv, comp->gainMana);
  } else {
    attaqueReussie = false; // test de prcision chou
  }

  ennemi->payerCoutMana(comp->coutMana);

  return attaqueReussie;
}
