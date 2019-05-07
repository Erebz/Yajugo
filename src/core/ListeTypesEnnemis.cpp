#include "ListeTypesEnnemis.h"
#include <fstream>
#include <string>
using namespace std;

void initialiserListeTypesEnnemis(ListeTypesEnnemis & liste) {
  ifstream fichierListe("./data/listeTypesEnnemis.txt");
  if (fichierListe.is_open()){
    char c;
    fichierListe >> liste.nbTypesEnnemis;
    liste.listeTypesEnnemis = new TypeEnnemi[liste.nbTypesEnnemis];

    for(unsigned int i=0; i < liste.nbTypesEnnemis; i++){
      fichierListe >> c;
      getline(fichierListe, liste.listeTypesEnnemis[i].nom, ';');
      fichierListe >> liste.listeTypesEnnemis[i].coeffPv >> c;
      fichierListe >> liste.listeTypesEnnemis[i].coeffMana >> c;
      fichierListe >> liste.listeTypesEnnemis[i].coeffAtk >> c;
      fichierListe >> liste.listeTypesEnnemis[i].coeffDef >> c;
      fichierListe >> liste.listeTypesEnnemis[i].coeffXp >> c;
      fichierListe >> liste.listeTypesEnnemis[i].nbCompetencesMax >> c;
      liste.listeTypesEnnemis[i].competences = new unsigned int[liste.listeTypesEnnemis[i].nbCompetencesMax];
      for(unsigned int j=0; j < liste.listeTypesEnnemis[i].nbCompetencesMax; j++) fichierListe >> liste.listeTypesEnnemis[i].competences[j] >> c;
    }
    fichierListe.close();
  }
}

void effacerListeTypesEnnemis(ListeTypesEnnemis & liste) {
  for(unsigned int i = 0; i < liste.nbTypesEnnemis; i++) {
        effacerTypeEnnemi(liste.listeTypesEnnemis[i]);
  }
  delete [] liste.listeTypesEnnemis;
  liste.listeTypesEnnemis = NULL;
}
