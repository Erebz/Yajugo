#include <fstream>
#include "ListeCases.h"
#include <fstream>
#include <string>
using namespace std;

void initialiserListeCases(ListeCases & liste) {
  ifstream fichierListe("./data/listeCases.txt");
  if (fichierListe.is_open()){
    char c;
    string s;
    fichierListe >> liste.nbCases;
    liste.listeCases = new Case[liste.nbCases];

    for(unsigned int i=0; i < liste.nbCases; i++){
      getline(fichierListe, s, ';');
      fichierListe >> c;
      fichierListe >> liste.listeCases[i].id >> c;
      fichierListe >> liste.listeCases[i].traversable >> c;
      // fichierListe >> liste.listeCases[i].caractere >> c;
      getline(fichierListe, liste.listeCases[i].caractere, ']');
    }
    fichierListe.close();
  }
}

void effacerListeCases(ListeCases & liste){
  delete [] liste.listeCases;
  liste.listeCases = NULL;
}
