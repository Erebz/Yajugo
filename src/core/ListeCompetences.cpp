#include "ListeCompetences.h"
#include <fstream>
#include <string>
using namespace std;

void initialiserListeCompetences(ListeCompetences & liste) {
  ifstream fichierListe("./data/listeCompetences.txt");
  if (fichierListe.is_open()){
    char c;
    fichierListe >> liste.nbCompetences;
    liste.listeCompetences = new Competence[liste.nbCompetences];

    for(unsigned int i=0; i < liste.nbCompetences; i++){
      fichierListe >> c;
      getline(fichierListe, liste.listeCompetences[i].nom, ';');
      getline(fichierListe, liste.listeCompetences[i].description, ';');
      fichierListe >> liste.listeCompetences[i].degats >> c;
      fichierListe >> liste.listeCompetences[i].buffAtk >> c;
      fichierListe >> liste.listeCompetences[i].buffDef >> c;
      fichierListe >> liste.listeCompetences[i].buffAtkCible >> c;
      fichierListe >> liste.listeCompetences[i].buffDefCible >> c;
      fichierListe >> liste.listeCompetences[i].precision >> c;
      fichierListe >> liste.listeCompetences[i].portee >> c;
      fichierListe >> liste.listeCompetences[i].transperce >> c;
      fichierListe >> liste.listeCompetences[i].coutMana >> c;
      fichierListe >> liste.listeCompetences[i].gainPv >> c;
      fichierListe >> liste.listeCompetences[i].gainMana >> c;
    }
    fichierListe.close();
  }
}

void effacerListeCompetences(ListeCompetences & liste){
  delete[] liste.listeCompetences;
  liste.listeCompetences = NULL;
}
