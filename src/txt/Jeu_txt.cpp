#include <iostream>
#include "../core/Jeu.h"
#include "conio.h"
using namespace std;

unsigned int initJeu(Jeu * & jeu){
  string nomJoueur;
  string nomType;
  unsigned int choix;

  do{
    system("clear");
    cout << "Bienvenue à Yajugo !" << endl << endl << "Selectionnez un fichier de sauvegarde :" << endl;
    for(unsigned int i=1; i <= 3; i++){
      if(!jeu->iemeSauvegardeExistante(i)){
        cout << i <<". Nouvelle Partie" << endl;
      }else{
        cout << i << ". " << jeu->getInfosIemeSauvegarde(i) << endl;
      }
    }
    cin >> choix;
    if(choix == 666) for(unsigned int i=1; i <= 3; i++) jeu->supprimerIemeSauvegarde(i);
  }while(choix > 3 || choix < 1);
  unsigned int choixSauvegarde = choix;

  if(jeu->iemeSauvegardeExistante(choixSauvegarde)){
    do{
      system("clear");
      cout << jeu->getInfosIemeSauvegarde(choixSauvegarde) << " : " << endl;
      cout << "1. Continuer" << endl << "2. Effacer les données" << endl;
      cin >> choix;
    }while(choix > 2 || choix < 1);
    if(choix == 2) jeu->supprimerIemeSauvegarde(choixSauvegarde);
  }

  system("clear");
  if(!jeu->iemeSauvegardeExistante(choixSauvegarde)){ //Nouvelle Partie
    cout << "Veuillez entrer le nom de votre personnage." << endl;
    cin >> nomJoueur;
    do{
      system("clear");
      cout << "Veuillez selectionner un type :" << endl << "1.Guerrier" << endl << "2.Mage" << endl << "3.Voleur" << endl;
      cin >> choix;
    } while (choix > 3 || choix < 1);
    switch (choix) {
      case 1:
      nomType = "Guerrier";
      break;
      case 2:
      nomType = "Mage";
      break;
      case 3:
      nomType = "Voleur";
      break;
    }

    //jeu = new Jeu(nomJoueur, nomType);
    jeu->genererJoueur(nomJoueur, nomType);
    //jeu->sauvegarderDansIemeFichier(choixSauvegarde);
  }else{
    //jeu = new Jeu(choixSauvegarde);
    jeu->genererJoueur(choixSauvegarde);
  }
  return choixSauvegarde;
}

void choixDonjon(Jeu * jeu){
  //Selection du donjon
  unsigned int choix;
  do{
    system("clear");
    cout << "Selectionnez un donjon :" << endl;
    for(unsigned int i=0; i < jeu->getListeDonjons().nbDonjons ; i++){
      cout << i+1 <<". " << jeu->getListeDonjons().donjonsDisponibles[i].nom << " [Niv." << jeu->getListeDonjons().donjonsDisponibles[i].niveauNecessaire << "]" << endl;
    }
    cin >> choix;
  }while(choix > jeu->getListeDonjons().nbDonjons || choix < 1 || jeu->getJoueur().getNiveau() < jeu->getListeDonjons().donjonsDisponibles[choix-1].niveauNecessaire);

  jeu->genererDonjon(choix-1);
}

void txtAff(const Jeu * const jeu) {

  // for (unsigned int i = 0; i < 50; ++i) {
  //   cout << endl;
  // }
  // system("clear");

  int x = 0;
  int y = 0;
  #ifdef _WIN32
  // Deplace le curseur en haut a gauche du terminal
  HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD origine = { (SHORT)x, (SHORT)y };
  SetConsoleCursorPosition(console, origine);
  #else
  char t[16];
  sprintf(t, "\033[%d;%dH", y, x);
  printf("%s",t);
  #endif

  const Etage* etage = &(jeu->getDonjon().getEtageActif());
  Joueur& joueur = jeu->getJoueurOriginal();
  bool presenceEnnemi = false;
  string caractJoueur = "v";
  for(unsigned int y = 0; y < etage->getTailleY(); y++){
    for (unsigned int x = 0; x < etage->getTailleX(); x++) {

      presenceEnnemi = false;
      for (unsigned int i = 0; i < etage->getNbEnnemis(); i++) {
        if (etage->getEnnemi(i).getX() == x && etage->getEnnemi(i).getY() == y) presenceEnnemi = true;
      }

      if (joueur.getX() == x && joueur.getY() == y) {
        // cout << "J"
        switch(joueur.getDirection()){
          case 1:
          caractJoueur = "^";
          break;
          case 2:
          caractJoueur = ">";
          break;
          case 3:
          caractJoueur = "v";
          break;
          case 4:
          caractJoueur = "<";
          break;
          default:
          break;
        }
        printf("%1s", caractJoueur.c_str());
        // printf("%1s", "J");
      } else if (presenceEnnemi) {
        // cout << "e";
        printf("%1s", "e");
      } else if(etage->getCase(x, y).objet != NULL){
        // cout << "O";
        printf("%1s", "O");
      }else{
        // cout << etage->getCase(x, y).caractere;
        const char* c = &etage->getCase(x, y).caractere[0];
        printf("%1s", c);
      }
    }
    // cout << endl;
    printf("\n");
  }
  cout << "Etage " << jeu->getDonjon().getNbEtagesParcourus()+1 << "/" << jeu->getDonjon().getNbEtages() << endl << endl;
  const Stats& s = joueur.getStats();
  cout << joueur.getNom() << ", " << joueur.getType().nom << " de niveau " << joueur.getNiveau() << endl;
  cout << "PV : " << s.pv << "/" << s.pvMax << "  PM : " << s.mana << "/" << s.manaMax << endl;
  cout << "Atk : " << s.atk << "  Def : " << s.def << endl;
  cout << "BuffAtk : " << s.buffAtk << "  BuffDef : " << s.buffDef << endl;
  cout << "XP : " << joueur.getExp() << "/" << joueur.getExpNivSup() << "        " << endl;
  cout << "Consulter les compétences : [C]" << endl << "Consulter l'inventaire : [I]" << endl;
  // cout << endl;
  printf("\n");
}

void txtBoucle (Jeu * const jeu) {
  jeu->getJoueurOriginal().reinitialiserStats();
  bool finDuJeu = false;
  bool tourJoueur = true;
  char c;
  int mode = 0;  //mode 0 : attente deplacement, mode 1 : choix attaque, mode 2 : choix objet
  bool deplacementEffectue = false;
  unsigned int choixComp = 0;
  unsigned int choixObj = 0;

  while(!finDuJeu){
    txtAff(jeu);

    //ACTION JOUEUR :
    mode = 0;
    while(tourJoueur){ //switch des modes
      txtAff(jeu);
      deplacementEffectue = false;
      switch (mode) {
        case 0: //attente deplacement
        //lire touche
        c = getch();
        deplacementEffectue = jeu->actionClavierDeplacementJoueur(c);
        if(deplacementEffectue){
          tourJoueur = false;
          unsigned int x = jeu->getJoueur().getX();
          unsigned int y = jeu->getJoueur().getY();
          Case caseJoueur = jeu->getDonjon().getEtageActif().getCase(x, y);
          if (caseJoueur.id == 10){
            if(jeu->getDonjon().getNbEtagesParcourus() < jeu->getDonjon().getNbEtages() - 1){
              txtAff(jeu);
              cout << endl <<"Voulez-vous accéder à l'étage suivant ?" << endl << "Oui [E], Non [A]" << endl;
              do{c=getch();}while(c!='e' && c!='a');
              if(c=='e'){
                jeu->monterEtageSuivant();
                system("clear");
                tourJoueur = true;
                mode = 0;
              }else if(c=='a'){
                system("clear");
              }
            }else{
              if(jeu->getDonjon().getEtageActif().getNbEnnemis() != 0 ){
                txtAff(jeu);
                cout << endl <<"Achevez tous les monstres de l'étage avant de sortir du donjon !" << endl << "OK [E]" << endl;
                do{c=getch();}while(c!='e');
                system("clear");
              }else{
                txtAff(jeu);
                cout << "Félicitations ! Vous avez atteint la sortie !" << endl << "OK [E]" << endl;
                do{c=getch();}while(c!='e');
                //Récompenses de fin de donjon ?
                tourJoueur = false;
                finDuJeu = true;
              }
            }
          }
        }
        if(c == 'c') mode = 1;
        if(c == 'i') mode = 2;
        // if(c == 'r') {
        //   tourJoueur = false;
        //   finDuJeu = true;
        // }
        // if(c == 'a') jeu->getJoueurOriginal().obtenirExp(100);
        // if(c == 'w'){
        //   jeu->getJoueurOriginal().subirDegats(50);
        //   jeu->getJoueurOriginal().soinPvMana(-20, -20);
        // }
        break;

        case 1://choix attaque
        //afficher attaques
        cout << "Appuyez sur [E] pour utiliser une compétence :" << endl;
        for (unsigned int i = 0; i < jeu->getJoueur().getNbCompetencesApprises(); ++i) {
          if(choixComp == i) cout << "-> ";
          cout << jeu->getJoueur().getCompetence(i)->nom << "   " << endl;
        }
        //lire touche
        c = getch();
        if(c == 's'){
          system("clear");
          if(choixComp == jeu->getJoueur().getNbCompetencesApprises() - 1){
            choixComp = 0;
          }else{
            choixComp ++;
          }
        }
        if(c == 'z'){
          system("clear");
          if(choixComp == 0){
            choixComp = jeu->getJoueur().getNbCompetencesApprises() - 1;
          }else{
            choixComp --;
          }
        }

        if(c == 'e'){
          Competence * comp = jeu->getJoueur().getCompetence(choixComp);
          cout << endl << comp->description << endl;
          cout << "Cout en mana : " << comp->coutMana;
          if(comp->gainPv < 0) cout << ", Cout PV : " << -1 * comp->gainPv;
          cout << endl<< "Portée : ";
          if(comp->portee >0)  cout << comp->portee << endl;
          else cout << "Vous-même" << endl;
          cout << "Précision : " << comp->precision << "%" << endl;
          if(comp->transperce) cout << "Peut toucher plusieurs cibles devant vous."<<endl;
          cout << "[E] : Utiliser, [A] : Annuler" << endl;

          do{c = getch();}while(c!='e' && c!='a');
          if(c=='e'){
            if (jeu->getJoueur().peutUtiliserIemeCompetence(choixComp)) {
              //préparations des infos sur le combats
              unsigned int xp = 0;
              unsigned int nbEnnemisTouches = 0;
              string * ennemis = NULL;
              unsigned int * degats = NULL;
              unsigned int niveau = jeu->getJoueur().getNiveau();
              unsigned int nbComp = jeu->getJoueur().getNbCompetencesApprises();
              Stats stats = jeu->getJoueur().getStats();
              bool attaqueReussie = jeu->joueurUtiliseCompetence(comp, nbEnnemisTouches, ennemis, degats, xp);

              if(!attaqueReussie) {
                cout << endl << "Attaque ratée !" << endl << "OK [E]" << endl;
                do {c=getch();}while(c!='e');

              } else {

                //feedbacks si l'attaque à réussi
                cout << endl;
                if (nbEnnemisTouches != 0) {

                  for(unsigned int i=0; i < nbEnnemisTouches; i++) {
                    cout << jeu->getJoueur().getNom() <<" a infligé " << degats[i] << " dégats à " << ennemis[i] << "!" << endl;
                  }
                  if(xp > 0) cout << "KO! +" << xp <<"XP"  << endl;
                  delete[] degats;
                  delete[] ennemis;

                } else if (comp->degats != 0) {
                  cout << "Vous n'avez touché personne" << endl;
                }

                //feedbacks des buffs et soins/reculs
                if (comp->buffAtk != 0) {
                  string ampleur;
                  if (comp->buffAtk < 0) {
                    if (comp->buffAtk < -2) {
                      ampleur = "énormément ";
                    } else if (comp->buffAtk < -1) {
                      ampleur = "";
                    } else {
                      ampleur = "légerement ";
                    }
                    cout << "Votre attaque a " + ampleur + "diminué" << endl;
                  } else {
                    if (comp->buffAtk > 2) {
                      ampleur = "énormément ";
                    } else if (comp->buffAtk > 1) {
                      ampleur = "";
                    } else {
                      ampleur = "légerement ";
                    }
                    cout << "Votre attaque a " + ampleur + "augmenté" << endl;
                  }
                }

                if (comp->buffDef != 0) {
                  string ampleur;
                  if (comp->buffDef < 0) {
                    if (comp->buffDef < -2) {
                      ampleur = "énormément ";
                    } else if (comp->buffDef < -1) {
                      ampleur = "";
                    } else {
                      ampleur = "légerement ";
                    }
                    cout << "Votre défense a " + ampleur + "diminué" << endl;
                  } else {
                    if (comp->buffDef > 2) {
                      ampleur = "énormément ";
                    } else if (comp->buffDef > 1) {
                      ampleur = "";
                    } else {
                      ampleur = "légerement ";
                    }
                    cout << "Votre défense a " + ampleur + "augmenté" << endl;
                  }
                }

                if (comp->gainPv != 0) {
                  cout << "Vous avez ";
                  if (comp->gainPv < 0) {
                    cout << "perdu " << -1*comp->gainPv << " points de vie" << endl;
                  } else {
                    cout << "gagné " << comp->gainPv << " points de vie" << endl;
                  }
                }

                if (comp->gainMana > 0) {
                  cout << "Vous avez gagné : " << comp->gainMana << " points de mana" << endl;
                }

                cout << "OK [E]" << endl;
                do{c=getch();}while(c!='e');

                //feedback montee en niveau
                if(niveau < jeu->getJoueur().getNiveau()){
                  system("clear");
                  txtAff(jeu);
                  Stats stats2 = jeu->getJoueur().getStats();
                  cout << "Montée de niveau ! " << niveau << "->" << jeu->getJoueur().getNiveau() << endl;
                  cout << "Points de vie : " << stats.pvMax << "->" << stats2.pvMax << endl;
                  cout << "Points de mana : " << stats.manaMax << "->" << stats2.manaMax << endl;
                  cout << "Attaque : " << stats.atk << "->" << stats2.atk << endl;
                  cout << "Défense : " << stats.def << "->" << stats2.def << endl;
                  cout << "OK [E]" << endl;
                  do{c=getch();}while(c!='e');
                  if(nbComp < jeu->getJoueur().getNbCompetencesApprises()){
                    system("clear");
                    txtAff(jeu);
                    cout << "Attaque apprise : " << endl;
                    for(unsigned int k = 0; k < jeu->getJoueur().getNbCompetencesApprises() - nbComp; k++){
                      cout << "-" << jeu->getJoueur().getCompetence(nbComp + k)->nom << endl;
                    }
                    cout << "OK [E]" << endl;
                    do{c=getch();}while(c!='e');
                  }
                  stats = jeu->getJoueur().getStats();
                  niveau = jeu->getJoueur().getNiveau();
                }

              }
              tourJoueur = false;

            } else {
              cout << endl << "Pas assez de mana ou de vie pour utiliser la compétence !" << endl << "OK [E]" << endl;
              do{c=getch();}while(c!='e');
              mode = 0;
            }
          }
          system("clear");
        }
        if (c != 'e' && c != 'z' && c != 's') system("clear");
        if(c == 'c'){
          mode = 0;
          system("clear");
        }
        // if(c == 'r') {
        //   tourJoueur = false;
        //   finDuJeu = true;
        // }

        break;

        case 2: //choix objet
        //afficher objets
        cout << "Appuyez sur [E] pour utiliser un objet :" << endl;
        for (unsigned int i = 0; i < jeu->getJoueur().getNbObjets(); ++i) {
          if(choixObj == i) cout << "-> ";
          cout << jeu->getJoueur().getObjet(i)->nom << "   " << endl;
        }
        //lire touche
        c = getch();
        if(c == 's'){
          system("clear");
          if(choixObj == jeu->getJoueur().getNbObjets() - 1){
            choixObj = 0;
          }else{
            choixObj ++;
          }
        }
        if(c == 'z'){
          system("clear");
          if(choixObj == 0){
            choixObj = jeu->getJoueur().getNbObjets() - 1;
          }else{
            choixObj --;
          }
        }
        if (c == 'e') {
          //Il faut verifier si l'inventaire n'est pas vide
          if (jeu->getJoueur().getNbObjets() != 0) {
            cout << endl << jeu->getJoueur().getObjet(choixObj)->description << endl;
            cout << "[E] : Utiliser, [J] : Jeter, [A] : Annuler" << endl;
            do{c = getch();}while(c!='e' && c!='a' && c!='j');
            if (c=='e') {
              jeu->getJoueurOriginal().utiliserIemeObjet(choixObj);
              tourJoueur = false;
              choixObj = 0;
            } else if(c == 'j') {
              int x =  jeu->getJoueur().getX();
              int y = jeu->getJoueur().getY();
              if(jeu->getDonjon().getEtageActif().getCase(x,y).objet == NULL && jeu->getDonjon().getEtageActif().getCase(x,y).id != 10){
                jeu->getDonjonOriginal().getEtageActifOriginal().ajouterObjetCase(x,y,jeu->getJoueur().getObjet(choixObj));
                jeu->getJoueurOriginal().retirerObjet(choixObj);
                tourJoueur = false;
                choixObj = 0;
              }
            }
          }
          system("clear");
        }
        if (c != 'e' && c != 'z' && c != 's') system("clear");
        if(c == 'i'){
          choixObj = 0;
          mode = 0;
          system("clear");
        }
        // if(c == 'r') {
        //   tourJoueur = false;
        //   finDuJeu = true;
        // }

        break;

        default:
        break;
      }
    }

    //actions automatiques c'est a dire tour de chaque ennemi
    //ils essayent d'attaquer d'abord et sinon ils se déplacent (aléatoirement pour l'instant)
    //system("clear");
    txtAff(jeu);

    Ennemi * ennemi = NULL;
    Competence * compChoisie = NULL;
    string nomEnnemi;
    for(unsigned int i=0; i < jeu->getDonjon().getEtageActif().getNbEnnemis(); i++){
      if(jeu->iemeEnnemiPresDeJoueur(i)){
        ennemi = &(jeu->getDonjonOriginal().getEtageActifOriginal().getEnnemiOriginal(i));
        nomEnnemi = ennemi->getType().nom;
        cout << "SALUT TOI !" << endl;
        cout << nomEnnemi << " : ";
        switch(ennemi->getDirection()){
          case 1:
          cout << "Tu es au dessus de moi..." << endl;
          break;
          case 2:
          cout << "Tu es à droite de moi..." << endl;
          break;
          case 3:
          cout << "Tu es en dessous de moi..." << endl;
          break;
          case 4:
          cout << "Tu es à gauche de moi..." << endl;
          break;
        }
        cout << "Je procède à une attaque !" <<endl << "COOL MEC [E]" << endl;

        do{c = getch();}while(c!='e');
        system("clear");
        txtAff(jeu);
        compChoisie = ennemi->choixCompetenceAleatoire();
        if(compChoisie != NULL){
          cout << nomEnnemi << " : J'utilise '" << compChoisie->nom <<"' !!!"<< endl;
          unsigned int degats=0;
          bool attaqueReussie = jeu->iemeEnnemiUtiliseCompetence(i, compChoisie, degats);
          if(attaqueReussie){
            if (compChoisie->degats != 0) {
              cout << nomEnnemi << " vous a infligé " << degats << " dégats." << endl;
            }

            //feedbacks des buffs et soins/reculs
            if (compChoisie->buffAtk != 0) {
              string ampleur;
              if (compChoisie->buffAtk < 0) {
                if (compChoisie->buffAtk < -2) {
                  ampleur = "énormément ";
                } else if (compChoisie->buffAtk < -1) {
                  ampleur = "";
                } else {
                  ampleur = "légerement ";
                }
                cout << nomEnnemi << " : Mon attaque a " + ampleur + "diminué..." << endl;
              } else {
                if (compChoisie->buffAtk > 2) {
                  ampleur = "énormément ";
                } else if (compChoisie->buffAtk > 1) {
                  ampleur = "";
                } else {
                  ampleur = "légerement ";
                }
                cout << nomEnnemi << " : Mon attaque a " + ampleur + "augmenté !" << endl;
              }
            }
            if (compChoisie->buffDef != 0) {
              string ampleur;
              if (compChoisie->buffDef < 0) {
                if (compChoisie->buffDef < -2) {
                  ampleur = "énormément ";
                } else if (compChoisie->buffDef < -1) {
                  ampleur = "";
                } else {
                  ampleur = "légerement ";
                }
                cout << nomEnnemi << " : Ma défense a " + ampleur + "diminué..." << endl;
              } else {
                if (compChoisie->buffDef > 2) {
                  ampleur = "énormément ";
                } else if (compChoisie->buffDef > 1) {
                  ampleur = "";
                } else {
                  ampleur = "légerement ";
                }
                cout << nomEnnemi << " : Ma défense a " + ampleur + "augmenté !" << endl;
              }
            }
            if (compChoisie->gainPv != 0) {
              cout << nomEnnemi << " : J'ai ";
              if (compChoisie->gainPv < 0) {
                cout << "perdu " << -1*compChoisie->gainPv << " points de vie..." << endl;
              } else {
                cout << "gagné " << compChoisie->gainPv << " points de vie !" << endl;
              }
            }
            if (compChoisie->gainMana > 0) {
              cout << nomEnnemi << " : J'ai gagné " << compChoisie->gainMana << " points de mana !" << endl;
            }

          }else{
            cout << "Attaque ratée !" << endl;
          }
          cout << "OK [E]" << endl;
          do{c = getch();}while(c!='e');
          system("clear");
          txtAff(jeu);
          compChoisie = NULL;
        }
        ennemi = NULL;
      }else{
        jeu->deplacerIemeEnnemi(i);
        ennemi = NULL;
      }
      if(jeu->getJoueur().estMort()){
        system("clear");
        txtAff(jeu);
        cout << "Vous êtes mort." << endl;
        cout << "OK [E]" << endl;
        do{c = getch();}while(c!='e');
        finDuJeu = true;
        break;
      }
    }

    if(!finDuJeu) tourJoueur = true;
  }
}
