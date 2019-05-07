#include <iostream>
#include <string.h>
#include <cassert>
#include <stdlib.h>
#include <time.h>
#include "Joueur.h"
#include "Ennemi.h"
#include "Objet.h"
#include "ListeCompetences.h"
#include "ListeObjets.h"
#include "ListeTypesEnnemis.h"
#include "ListeDonjons.h"
#include "ListeCases.h"
#include "TypeJoueur.h"
#include "Stats.h"
#include "Etage.h"
#include "Donjon.h"
#include "Jeu.h"
#include "random.h"
using namespace std;


void afficherInfosCompetence(const Competence & c){
  cout <<"Nom : " << c.nom << endl;
  cout << "Description : " << c.description << endl;
  cout << "Degats : " << c.degats << endl;
  cout << "Buff Atk/Def : " << c.buffAtk << "/" << c.buffDef << endl;
  cout << "Buff Atk/Def de la cible : " << c.buffAtkCible << "/" << c.buffDefCible << endl;
  cout << "Precision : " << c.precision << endl;
  cout << "Portee : " << c.portee << " cases" <<endl;
  cout << "Cout : " << c.coutMana << " PM" << endl;
  cout << "Soin + " << c.gainPv << "PV" << endl;
  cout << "Regen Mana + " << c.gainMana << "PM" << endl<<endl;
}

void afficherInfosObjet(const Objet &o){
  cout << "Nom : " << o.nom << endl;
  cout << "Description : " << o.description << endl;
  cout << "Gain PV : " << o.gainPv << endl;
  cout << "Gain PM : " << o.gainMana << endl;
  cout << "Buff Atk/Def : " << o.buffAtk << "/" << o.buffDef << endl<<endl;
}

void afficherInfosTypeEnnemi(const TypeEnnemi &t){
  cout << "Nom : " <<t.nom << endl;
  cout << "Coeff Pv : " << t.coeffPv << endl;
  cout << "Coeff Mana : " << t.coeffMana << endl;
  cout << "Coeff ATK : " << t.coeffAtk << endl;
  cout << "Coeff DEF : " << t.coeffDef << endl;
  cout << "Nombre de compétences : " <<t.nbCompetencesMax << endl;
  for(unsigned int i=0; i< t.nbCompetencesMax; i++) cout << "Compétence #"<< i+1 <<" : " << t.competences[i] << endl;
  cout<<endl;
}

void afficherInfosTypeJoueur(const Joueur &j, const ListeCompetences &l){
  TypeJoueur t = j.getType();
  cout << "Nom du type : " <<t.nom << endl;
  cout << "Coeff PV : " <<t.coeffPvMin << endl;
  cout << "Coeff Mana : " <<t.coeffManaMin << endl;
  cout << "Coeff ATK : " <<t.coeffAtkMin << endl;
  cout << "Coeff DEF : " <<t.coeffDefMin << endl;
  cout << "Coeff PV : " <<t.coeffPvMax << endl;
  cout << "Coeff Mana : " <<t.coeffManaMax << endl;
  cout << "Coeff ATK : " <<t.coeffAtkMax << endl;
  cout << "Coeff DEF : " <<t.coeffDefMax << endl;
  cout << "Nombre de competences : " << t.nbApprentissagesMax << endl << "Tranches d'apprentissage : ";
  for(unsigned int i=0; i< t.nbApprentissagesMax; i++) cout << "Niv." << t.caps[i] << " ";
  cout << endl <<"Nom des competences :" << endl;
  for(unsigned int i=0; i< t.nbApprentissagesMax; i++) cout << "Compétence #" << i+1<<" : " << l.listeCompetences[t.competences[i]].nom << endl;
}

void testsInventaire(Joueur &p1, const ListeObjets& lo){
  cout << endl << "Ajout d'objets dans l'inventaire du joueur..." << endl;
  for (unsigned int i = 0; i < 5; i++) {
    p1.ajouterObjet(&(lo.listeObjets[i]));
  }
  cout << endl;
  for (unsigned int i = 0; i < p1.getNbObjets(); i++) {
    cout << "Objet " << i+1 << " : " << p1.getObjet(i)->nom << endl;
  }
  cout << endl << "Retrait du deuxieme objet..." << endl;
  p1.retirerObjet(1);
  cout << endl;
  for (unsigned int i = 0; i < p1.getNbObjets(); i++) {
    cout << "Objet " << i+1 << " : " << p1.getObjet(i)->nom << endl;
  }
  cout << endl << "Retrait des deux derniers objets..." << endl;
  p1.retirerObjet(p1.getNbObjets()-1);
  p1.retirerObjet(p1.getNbObjets()-1);
  cout << endl;
  for (unsigned int i = 0; i < p1.getNbObjets(); i++) {
    cout << "Objet " << i+1 << " : " << p1.getObjet(i)->nom << endl;
  }
  cout << endl << "Ajout d'un objet qqcque..." << endl;
  p1.ajouterObjet(&(lo.listeObjets[6]));
  cout << endl;
  for (unsigned int i = 0; i < p1.getNbObjets(); i++) {
    cout << "Objet " << i+1 << " : " << p1.getObjet(i)->nom << endl;
  }
}

void afficherInfosJoueur(const Joueur &j){
  Stats s = j.getStats();
  cout << "Niveau du joueur : " << j.getNiveau() << endl;
  cout << "PV : " << s.pv << "/"<< s.pvMax << endl;
  cout << "PM : " << s.mana << "/"<<s.manaMax << endl;
  cout << "ATK : " << s.atk << endl;
  cout << "DEF : " << s.def << endl;
  cout << "Buff ATK/DEF : " << s.buffAtk << "/"<< s.buffDef << endl;
  cout <<"XP : " << j.getExp() << endl;
  cout <<"XP avant niveau sup : " << j.getExpNivSup() << endl;
  cout << "Competences : " << endl;
  for (unsigned int i = 0; i < j.getNbCompetencesApprises(); ++i) {cout <<"-" << j.getCompetence(i)->nom << endl;}
  cout << "Inventaire : " << endl;
  for (unsigned int i = 0; i < j.getNbObjets(); ++i) {
    cout << "Objet " << i+1 << " : " << j.getObjet(i)->nom << endl;
  }
  cout << endl;
}

void afficherInfosEnnemi(const Ennemi &cpu){
  cout << "Nom : " << cpu.getType().nom << endl;
  cout << "Niveau : " << cpu.getNiveau() << endl;
  cout << "PV : " << cpu.getStats().pv << "/"<< cpu.getStats().pvMax << endl;
  cout << "PM : " << cpu.getStats().mana << "/"<< cpu.getStats().manaMax << endl;
  cout << "ATK : " << cpu.getStats().atk << endl;
  cout << "DEF : " << cpu.getStats().def << endl;
  cout << "XP donné : " << cpu.getExpDonnee() << endl;
  cout << "Buff ATK/DEF : " << cpu.getStats().buffAtk << "/"<< cpu.getStats().buffDef << endl;
  cout << "Affichage des competences : " << endl;
  for (unsigned int i = 0; i < cpu.getType().nbCompetencesMax; i++) {cout <<"-" <<cpu.getCompetence(i)->nom << endl;}
}

void afficherEtage(const Etage & etage, const Joueur & joueur){
  bool presenceEnnemi = false;
  for(unsigned int y = 0; y < etage.getTailleY(); y++){
    for (unsigned int x = 0; x < etage.getTailleX(); x++) {

      presenceEnnemi = false;
      for (unsigned int i = 0; i < etage.getNbEnnemis(); i++) {
        if (etage.getEnnemi(i).getX() == x && etage.getEnnemi(i).getY() == y) presenceEnnemi = true;
      }

      if (joueur.getX() == x && joueur.getY() == y) {
        cout << "J";
      } else if (presenceEnnemi) {
        cout << "e";
      } else if(etage.getCase(x, y).objet != NULL){
        cout << "O";
      }else{
        cout << etage.getCase(x, y).caractere;
      }
    }
    cout << endl;
  }
  cout << endl;
}

void afficherCarteEtage(const Etage & etage){
  for(unsigned int y = 0; y < etage.getTailleY(); y++){
    for (unsigned int x = 0; x < etage.getTailleX(); x++) {
      cout << etage.getCase(x, y).caractere;
    }
    cout << endl;
  }
  cout << endl;
}

void afficherInfosEtage(const Etage &etage){
  Ennemi ennemi;

  cout << "taille x : " << etage.getTailleX() << endl << "taille y : " << etage.getTailleY() << endl << endl;

  for (unsigned int i = 0; i < etage.getNbEnnemis(); i++) {
    ennemi = etage.getEnnemi(i);
    cout << "Ennemi " << i+1 << " :" << endl;
    //     cout << "Nom : " << ennemi.getType().nom << endl << "Niveau : " << ennemi.getNiveau() << endl;
    //     cout << "Emplacement : (" << ennemi.getX() << ", " << ennemi.getY() << ")" << endl;
    //     for (unsigned int k = 0; k < ennemi.getType().nbCompetencesMax; k++) {
    //       cout << ennemi.getCompetence(k)->nom << endl;
    //     }
    afficherInfosEnnemi(ennemi);
    cout << endl;
  }

  Objet * objet;
  for(unsigned int y = 0; y < etage.getTailleY(); y++){
    for (unsigned int x = 0; x < etage.getTailleX(); x++) {
      if(etage.getCase(x, y).objet != NULL){
        objet = etage.getCase(x, y).objet;
        cout << "Objet à la case (" << x << "," << y <<") : ";
        cout << objet->nom << endl;
      }
    }
  }
}

void afficherInfosDonjon(const Donjon &d){
  cout << "Nombre d'étages : " << d.getNbEtages() << endl;
  cout << "Nombre d'étages parcourus : " << d.getNbEtagesParcourus() << endl;
  for(unsigned int i=0; i<d.getNbEtages();i++){
    cout << "Nombre d'ennemis dans l'étage " << i+1 <<" : " << d.getEtage(i).getNbEnnemis() << endl;
  }
}

void afficherResumeDonjon(const InfosDonjon &donjon){
  cout << "Nom : " << donjon.nom << endl;
  cout << "Niveau nécessaire : " << donjon.niveauNecessaire << endl;
  cout << "Nombre d'étages : " << donjon.nbEtages << endl;
  for(unsigned int i=0; i < donjon.nbEtages; i++){
    cout << endl << "Etage #" << i+1 << " : " << endl;
    cout << "Nombre d'ennemis : " << donjon.etages[i].nbEnnemis << endl;
    cout << "Tranche de niveau : " << donjon.etages[i].niveauMin << " à " << donjon.etages[i].niveauMax << endl;
    cout << "Nombre d'objets : " << donjon.etages[i].nbObjets << endl;
    cout << "Ennemis : " << endl;
    for(unsigned int k=0; k < donjon.etages[i].nbEnnemisRencontrables; k++){
      cout << "-" << donjon.etages[i].ennemisRencontrables[k] << endl;
    }
    cout << "Objets : " << endl;
    for(unsigned int k=0; k < donjon.etages[i].nbObjetsTrouvables; k++){
      cout << "-" << donjon.etages[i].objetsTrouvables[k] << endl;
    }
  }
}

int main(void) {
  srand(time(NULL));
  ListeCompetences l;
  ListeObjets lo;
  ListeTypesEnnemis e;
  ListeCases lc;
  ListeDonjons ldonj;
  cout << endl <<"Creation des listes de données..." << endl << endl;
  initialiserListeCompetences(l);
  initialiserListeObjets(lo);
  initialiserListeTypesEnnemis(e);
  initialiserListeCases(lc);
  initialiserListeDonjons(ldonj);

  for(unsigned int i=0; i<l.nbCompetences; i++){
    cout << "Competence #" << i+1 << endl;
    afficherInfosCompetence(l.listeCompetences[i]);
  }

  for(unsigned int i=0; i<lo.nbObjets; i++){
    cout << "Objet #" << i+1 << endl;
    afficherInfosObjet(lo.listeObjets[i]);
  }

  for(unsigned int i=0; i < e.nbTypesEnnemis; i++){
    cout << "Ennemi #"<< i+1 << endl;
    afficherInfosTypeEnnemi(e.listeTypesEnnemis[i]);
  }

  cout << endl <<"Creation d'un ennemi... (depuis liste Types d'Ennemis)"<< endl;
  Ennemi * cpu = new Ennemi(e.listeTypesEnnemis[2], 10, l);
  afficherInfosEnnemi(*cpu);
  delete cpu;

  cout << endl << "Creation d'un joueur..." << endl;
  Joueur * p1 =  new Joueur("Yacine", "Mage", l);
  afficherInfosTypeJoueur(*p1, l);
  afficherInfosJoueur(*p1);
  cout << endl << "+ 1000 XP..." <<endl;
  p1->obtenirExp(1000);
  cout << "Atk + 8 et Def -8..." <<endl;
  p1->modifBuffAtkDef(3,-3);
  p1->modifBuffAtkDef(8,-8);
  afficherInfosJoueur(*p1);
  cout << endl << "Inflthis->stats.pviger 20 degats..." << endl;
  cout << "Résistance potentielle : " << p1->getStats().def + (((int)p1->getStats().def)* p1->getStats().buffDef * 0.25) << endl;
  p1->subirDegats(20);
  afficherInfosJoueur(*p1);
  testsInventaire(*p1, lo);

  delete p1;

  for(unsigned int i=0; i < ldonj.nbDonjons; i++){
    cout << "Donjon " << i+1 << " :" << endl;
    afficherResumeDonjon(ldonj.donjonsDisponibles[i]);
    cout << endl;
  }


  cout << "Creation du jeu..." << endl;
  Jeu j("Ruquier", "Voleur");
  cout << endl << "Compétences du jeu : " << endl;
  for(unsigned int i=0; i<j.getListeCompetences().nbCompetences; i++){
    cout << "Competence #" << i+1 << endl;
    afficherInfosCompetence(j.getListeCompetences().listeCompetences[i]);
  }
  cout << "Objets du jeu : " << endl;
  for(unsigned int i=0; i<j.getListeObjets().nbObjets; i++){
    cout << "Objet #" << i+1 << endl;
    afficherInfosObjet(j.getListeObjets().listeObjets[i]);
  }
  cout << "Ennemis du jeu : " << endl;
  for(unsigned int i=0; i < j.getListeTypesEnnemis().nbTypesEnnemis; i++){
    cout << "Ennemi #"<< i+1 << endl;
    afficherInfosTypeEnnemi(j.getListeTypesEnnemis().listeTypesEnnemis[i]);
  }

  j.genererDonjon(0);
  cout << endl << "Infos sur le donjon créé : " << endl;

  cout << j.getJoueur().getX() << " " << j.getJoueur().getY() << endl;
  afficherInfosDonjon(j.getDonjon());
  for(unsigned int i = 0; i < j.getDonjon().getNbEtages(); i++){
    afficherInfosEtage(j.getDonjon().getEtage(i));
    cout << endl;
  }

  cout << endl << "Infos sur le joueur créé : " << endl;
  afficherInfosTypeJoueur(j.getJoueur(), j.getListeCompetences());
  afficherInfosJoueur(j.getJoueur());
  cout << endl << "Tests sur l'inventaire du joueur : " << endl;
  testsInventaire(j.getJoueurOriginal(), j.getListeObjets());
  cout << endl << "+ 1000 XP..." <<endl;
  j.getJoueurOriginal().obtenirExp(1000);
  cout << "Atk + 8 et Def -8..." <<endl;
  j.getJoueurOriginal().modifBuffAtkDef(8,-8);
  afficherInfosJoueur(j.getJoueur());
  cout << endl << "Infliger 20 degats..." << endl;
  cout << "Résistance potentielle : " << j.getJoueurOriginal().getStats().def + (((int)j.getJoueurOriginal().getStats().def)* j.getJoueurOriginal().getStats().buffDef * 0.25) << endl;
  j.getJoueurOriginal().subirDegats(20);
  afficherInfosJoueur(j.getJoueur());

  afficherInfosJoueur(j.getJoueur());
  afficherInfosEtage(j.getDonjon().getEtageActif());

  afficherInfosJoueur(j.getJoueur());

  char c;
  do {
    cout << endl << j.getJoueur().getDirection() << endl;
    afficherEtage(j.getDonjon().getEtageActif(), j.getJoueur());
    cin >> c;
    j.actionClavierDeplacementJoueur(c);
  } while (c != 'm');

  afficherInfosJoueur(j.getJoueur());
  afficherEtage(j.getDonjon().getEtageActif(), j.getJoueur());

  for (unsigned int i = 0; i < (j.getDonjon().getEtageActif().getNbEnnemis()); i++) {
    cout << j.getDonjon().getEtageActif().getEnnemi(i).getType().nom << endl;
  }

  j.getDonjonOriginal().getEtageActifOriginal().retirerIemeEnnemi(0);
  j.getDonjonOriginal().getEtageActifOriginal().retirerIemeEnnemi(j.getDonjon().getEtageActif().getNbEnnemis() - 1);

  cout << endl;
  for (unsigned int i = 0; i < (j.getDonjon().getEtageActif().getNbEnnemis()); i++) {
    cout << j.getDonjon().getEtageActif().getEnnemi(i).getType().nom << endl;
  }

  effacerListeCompetences(l);
  effacerListeObjets(lo);
  effacerListeTypesEnnemis(e);
  effacerListeCases(lc);
  effacerListeDonjons(ldonj);

  return 0;
}
