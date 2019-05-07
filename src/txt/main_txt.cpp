#include <iostream>
#include "Jeu_txt.h"

using namespace std;

int main(int argc, char** argv){
  srand(time(NULL));
  Jeu * jeu = new Jeu();
  bool quitter = false;
  unsigned int choixSauvegarde;

  system("clear");
  choixSauvegarde = initJeu(jeu);

  while(!quitter){
    system("clear");
    choixDonjon(jeu);
    system("clear");
    txtBoucle(jeu);
    unsigned int choix;
    do {
      system("clear");
      cout << "Fin de la partie." << endl;
      cout << "1. Sauvegarder et continuer" << endl << "2. Sauvegarder et quitter" << endl << "3. Quitter" << endl;
      cin >> choix;
    } while(choix > 3 || choix < 1);
    if(choix == 1 || choix == 2) jeu->sauvegarderDansIemeFichier(choixSauvegarde);
    if(choix == 2 || choix == 3) quitter = true;
  }

  delete jeu;
  return 0;
}
