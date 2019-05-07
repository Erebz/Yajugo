#include "ListeObjets.h"
#include <fstream>
#include <string>
using namespace std;

void initialiserListeObjets(ListeObjets & liste) {
  ifstream fichierListe("./data/listeObjets.txt");
  if (fichierListe.is_open()){
    char c;
    fichierListe >> liste.nbObjets;
    liste.listeObjets = new Objet[liste.nbObjets];

    for(unsigned int i=0; i < liste.nbObjets; i++){
      fichierListe >> c;
      getline(fichierListe, liste.listeObjets[i].nom, ';');
      getline(fichierListe, liste.listeObjets[i].description, ';');
      fichierListe >> liste.listeObjets[i].gainPv >> c;
      fichierListe >> liste.listeObjets[i].gainMana >> c;
      fichierListe >> liste.listeObjets[i].buffAtk >> c;
      fichierListe >> liste.listeObjets[i].buffDef >> c;
    }
    fichierListe.close();
  }
}

void effacerListeObjets(ListeObjets & liste){
  delete[] liste.listeObjets;
  liste.listeObjets = NULL;
}
