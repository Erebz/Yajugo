#include "ListeDonjons.h"
#include <iostream>
#include <fstream>

void initialiserListeDonjons(ListeDonjons & ldonj){
  ifstream fichierListe("./data/listeDonjons.txt");
  if (fichierListe.is_open()){
    char c;
    fichierListe >> ldonj.nbDonjons;
    ldonj.donjonsDisponibles = new InfosDonjon[ldonj.nbDonjons];

    for(unsigned int i=0; i < ldonj.nbDonjons; i++){
      fichierListe >> c;
      getline(fichierListe, ldonj.donjonsDisponibles[i].nom, ';');

      fichierListe >> ldonj.donjonsDisponibles[i].niveauNecessaire >> c;
      fichierListe >> ldonj.donjonsDisponibles[i].nbEtages >> c;
      ldonj.donjonsDisponibles[i].etages = new InfosEtage[ldonj.donjonsDisponibles[i].nbEtages];
      InfosEtage * etage = ldonj.donjonsDisponibles[i].etages;
      for(unsigned int j=0; j < ldonj.donjonsDisponibles[i].nbEtages; j++){
        fichierListe >> etage[j].nbEnnemis >> c;
        fichierListe >> etage[j].nbEnnemisRencontrables >> c;
        etage[j].ennemisRencontrables = new unsigned int[etage[j].nbEnnemisRencontrables];
        for(unsigned int k=0; k < etage[j].nbEnnemisRencontrables; k++){
          fichierListe >> etage[j].ennemisRencontrables[k] >> c;
        }
        fichierListe >> etage[j].niveauMin >> c;
        fichierListe >> etage[j].niveauMax >> c;
        fichierListe >> etage[j].nbObjets >> c;
        fichierListe >> etage[j].nbObjetsTrouvables >> c;
        etage[j].objetsTrouvables = new unsigned int[etage[j].nbObjetsTrouvables];
        for(unsigned int k=0; k < etage[j].nbObjetsTrouvables; k++){
          fichierListe >> etage[j].objetsTrouvables[k] >> c;
        }

        fichierListe >> etage[j].tailleX >> c >> etage[j].tailleY >> c;
        fichierListe >> etage[j].nbSalles >> c;
        fichierListe >> etage[j].nbIdSalles >> c;
        etage[j].idSalles = new unsigned int [etage[j].nbIdSalles];
        for (unsigned int k = 0; k < etage[j].nbIdSalles; k++) {
          fichierListe >> etage[j].idSalles[k] >> c;
        }
      }
    }
    fichierListe.close();
  }
}

void effacerListeDonjons(ListeDonjons & ldonj){
  for(unsigned int i=0; i < ldonj.nbDonjons; i++){
    for(unsigned int j=0; j < ldonj.donjonsDisponibles[i].nbEtages; j++){
      delete [] ldonj.donjonsDisponibles[i].etages[j].ennemisRencontrables;
      delete [] ldonj.donjonsDisponibles[i].etages[j].objetsTrouvables;
      delete [] ldonj.donjonsDisponibles[i].etages[j].idSalles;
      ldonj.donjonsDisponibles[i].etages[j].ennemisRencontrables = NULL;
      ldonj.donjonsDisponibles[i].etages[j].objetsTrouvables = NULL;
      ldonj.donjonsDisponibles[i].etages[j].idSalles = NULL;
    }
    delete [] ldonj.donjonsDisponibles[i].etages;
    ldonj.donjonsDisponibles[i].etages = NULL;

  }
  delete [] ldonj.donjonsDisponibles;
  ldonj.donjonsDisponibles = NULL;
}
