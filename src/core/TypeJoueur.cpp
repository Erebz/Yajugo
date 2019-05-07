#include "TypeJoueur.h"
#include <fstream>
using namespace std;

void initialiserTypeJoueur(TypeJoueur & t, const string &nomType) {
  char c;
  string emplacement = "./data/";
  string format = ".txt";
  string nomFichierType = emplacement + nomType + format;
  ifstream fichierType(nomFichierType.c_str());

  if (fichierType.is_open()){
    t.nom = nomType;
    fichierType >> t.coeffPvMin >> c;
    fichierType >> t.coeffManaMin >> c;
    fichierType >> t.coeffAtkMin >> c;
    fichierType >> t.coeffDefMin >> c;
    fichierType >> t.coeffPvMax >> c;
    fichierType >> t.coeffManaMax >> c;
    fichierType >> t.coeffAtkMax >> c;
    fichierType >> t.coeffDefMax >> c;
    fichierType >> t.nbApprentissagesMax >> c;
    t.caps = new unsigned int[t.nbApprentissagesMax];
    t.competences = new unsigned int[t.nbApprentissagesMax];
    for(unsigned int i=0; i < t.nbApprentissagesMax; i++) fichierType >> t.caps[i] >> c;
    for(unsigned int i=0; i < t.nbApprentissagesMax; i++) fichierType >> t.competences[i] >> c;
    fichierType.close();
  }
}

void effacerTypeJoueur(TypeJoueur &t){
  delete [] t.competences;
  delete [] t.caps;
  t.competences = NULL;
  t.caps = NULL;
}

