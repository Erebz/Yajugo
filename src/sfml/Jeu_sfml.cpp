#include <iostream> /*! \headerfile iostream*/
#include "Jeu_sfml.h" /*! \headerfile "Jeu_sfml"*/

using namespace std; /*! \namespace std*/
using namespace sf; /*! \namespace sf*/
/*!
* \file Jeu_sfml.cpp
* \brief Fichier cpp pour SFML
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 15/04/2019
*/


void Jeu_sfml::initialiserListeTextures(){ // 0, 11 joueur puis ennemis/objets/cases
  ltex.nbTextures = NB_SPRITES;
  ltex.textures = new Texture[ltex.nbTextures];

  string emplacement = "data/Images/";
  string format = ".png";
  string nomFichier;
  unsigned int i=0,k=0;
  unsigned int limite = 12;

  while(i < limite){
    nomFichier = emplacement + "Joueur" + to_string(i+1) + format;
    if (!ltex.textures[i].loadFromFile(nomFichier)){std::cout << "erreur chargement image " <<  nomFichier << std::endl;}
    i++;
  }

  k = limite;
  limite += jeu.getListeTypesEnnemis().nbTypesEnnemis*4;
  while(i < limite){
    nomFichier = emplacement + "Ennemi" + to_string(i-k + 1) + format;
    if (!ltex.textures[i].loadFromFile(nomFichier)){std::cout << "erreur chargement image " <<  nomFichier << std::endl;}
    i++;
  }

  k = limite;
  limite += jeu.getListeObjets().nbObjets ;
  while(i < limite){
    nomFichier = emplacement + "Objet" + to_string(i-k + 1) + format;
    if (!ltex.textures[i].loadFromFile(nomFichier)){std::cout << "erreur chargement image " <<  nomFichier << std::endl;}
    i++;
  }

  k = limite;
  limite += jeu.getListeCases().nbCases ;
  while(i < limite){
    nomFichier = emplacement + "Case" + to_string(i-k+1) + format;
    if (!ltex.textures[i].loadFromFile(nomFichier)){std::cout << "erreur chargement image " <<  nomFichier << std::endl;}
    i++;
  }
}
void Jeu_sfml::effacerListeTextures(){
  delete [] ltex.textures;
  ltex.textures = NULL;
}

Jeu_sfml::Jeu_sfml() : jeu(){
  initialiserListeTextures();
  this->fenetre = new RenderWindow(VideoMode(LARGEUR, HAUTEUR, 32), "YaJuGo");
  fenetre->setKeyRepeatEnabled(false);
  fenetre->setFramerateLimit(60);
  if(!this->musique.openFromFile("./data/Sons/Musique.ogg")) cout << "erreur chargement musique" << endl;
  musique.setVolume(20);
  musique.setLoop(true);

  if (!buffer.loadFromFile("./data/Sons/curseurMove.wav")) cout << "erreur chargement son" << endl;
  this->son.setBuffer(buffer);
  if (!buffer2.loadFromFile("./data/Sons/curseurOk.wav")) cout << "erreur chargement son" << endl;
  this->son2.setBuffer(buffer2);
  if (!buffer3.loadFromFile("./data/Sons/curseurBack.wav")) cout << "erreur chargement son" << endl;
  this->son3.setBuffer(buffer3);

  if (!this->police.loadFromFile("data/DejaVuSansCondensed.ttf")) cout << "Erreur chargement police." << endl;
  else this->texte.setFont(this->police);
  if (!this->image_curseur.loadFromFile("data/Images/curseur.png")) cout << "Erreur chargement image curseur" << endl;
  else curseur.setTexture(image_curseur);
  if (!this->im_console.loadFromFile("data/Images/boiteConsole.png")) cout << "Erreur chargement image console" << endl;
  else console.setTexture(im_console);
  if (!this->im_menu.loadFromFile("data/Images/boiteMenu.png")) cout << "Erreur chargement image menu" << endl;
  else menu.setTexture(im_menu);
  im_fond.loadFromFile("./data/Images/Menu.png");
  fond.setTexture(im_fond);

  this->choixSauvegarde = this->selectionnerJoueur();
  if(this->fenetre->isOpen()) this->choixDonjon = this->selectionnerDonjon();
}

Jeu_sfml::~Jeu_sfml(){
  if(this->fenetre->isOpen()) this->fenetre->close();
  if(this->fenetre != NULL) delete this->fenetre;
  fenetre = NULL;
  musique.stop();
  effacerListeTextures();
}

bool Jeu_sfml::fenetreOuverte(){
    return this->fenetre->isOpen();
}

unsigned int Jeu_sfml::selectionnerJoueur(){
  unsigned int choix=0;
  bool quit = false;
  char c = ' ';

  while (this->fenetre->isOpen() && !quit){
    c = lireTouche();
    switch(c){
      case 'z':
      son.play();
      if(choix == 0) choix = 2;
      else choix--;
      break;

      case's':
      son.play();
      if(choix == 2) choix = 0;
      else choix++;
      break;

      case'J':
      son3.play();
      this->jeu.supprimerIemeSauvegarde(choix);
      break;

      case 'E':
      son2.play();
      quit = true;
      break;

      case 'Q':
      this->fenetre->close();
      quit = true;
      break;
      default: break;
    }

    this->fenetre->clear();
    this->fenetre->draw(fond);

    this->texte.setCharacterSize(35);
    for(unsigned int i=0; i<3; i++){
      this->texte.setStyle(sf::Text::Regular);
      this->texte.setFillColor(sf::Color::White);
      this->texte.setPosition(LARGEUR*0.7, HAUTEUR/2 + i*TAILLE_SPRITE);
      if(!this->jeu.iemeSauvegardeExistante(i+1)) this->texte.setString("Nouvelle Partie");
      else this->texte.setString(this->jeu.getInfosIemeSauvegarde(i+1));
      if(choix == i){
        this->curseur.setPosition(LARGEUR*0.7 - TAILLE_SPRITE, HAUTEUR/2 + i*TAILLE_SPRITE);
        this->texte.setStyle(sf::Text::Bold);
        this->fenetre->draw(this->curseur);
      }
      this->fenetre->draw(this->texte);
    }

    this->fenetre->display();
  }

 if(this->fenetre->isOpen()){
  if(!this->jeu.iemeSauvegardeExistante(choix+1)){
    this->saisirInfosNouvellePartie();
  }else{
    this->jeu.genererJoueur(choix+1);
  }
}

  return choix+1;
}

void Jeu_sfml::saisirInfosNouvellePartie(){
  this->texte.setCharacterSize(30);
  this->texte.setStyle(sf::Text::Regular);
  unsigned int choix = 0;
  bool quit = false;
  im_fond.loadFromFile("./data/Images/Menu2.png");
  fond.setTexture(im_fond);
  string nomJoueur = "";
  string nomType = "Guerrier";

  while (this->fenetre->isOpen() && !quit){
    Event event;
    if (this->fenetre->waitEvent(event)){
      if (event.type == Event::Closed) this->fenetre->close();
      if (event.type == sf::Event::KeyPressed){
        switch(event.key.code){
          case sf::Keyboard::Up:
          son.play();
          if(choix == 0) choix = 2;
          else choix--;
          break;
          case sf::Keyboard::Down:
          son.play();
          if(choix == 2) choix = 0;
          else choix++;
          break;
          case sf::Keyboard::Space: //!!!
          if(choix==0) nomType = "Guerrier";
          if(choix==1) nomType = "Mage";
          if(choix==2) nomType = "Voleur";
          quit = true;
          break;
          case sf::Keyboard::Delete:
          if(nomJoueur != "") nomJoueur = nomJoueur.substr(0, nomJoueur.size()-1);
          break;
          default: break;
        }
      }

      if(event.type == sf::Event::TextEntered && nomJoueur.size() <= 8){
        if((event.text.unicode >= 'A' && event.text.unicode <= 'Z') || (event.text.unicode >= 'a' && event.text.unicode <= 'z')) nomJoueur = nomJoueur + event.text.unicode;
      }

      if (event.type == Event::Closed) this->fenetre->close();
    }

    this->fenetre->clear();
    this->fenetre->draw(this->fond);

    this->texte.setFillColor(sf::Color::White);
    this->texte.setPosition(LARGEUR*0.36, HAUTEUR*0.25);
    this->texte.setString("Entrez un nom :");
    this->fenetre->draw(this->texte);
    this->texte.setPosition(LARGEUR*0.36, HAUTEUR*0.25 + 70);
    this->texte.setString(nomJoueur);
    this->fenetre->draw(this->texte);

    this->texte.setPosition(LARGEUR*0.36, HAUTEUR*0.4);
    this->texte.setString("Selectionnez un type :");
    this->fenetre->draw(this->texte);

    for(unsigned int i=0; i<3; i++){
      this->texte.setFillColor(sf::Color::White);
      this->texte.setPosition(LARGEUR*0.36, HAUTEUR*0.4 + 70 + i*65);
      string type;
      if(i==0) type = "Guerrier";
      if(i==1) type = "Mage";
      if(i==2) type = "Voleur";
      this->texte.setString(type);
      if(choix == i){
        this->curseur.setPosition(LARGEUR*0.36 - 75,  HAUTEUR*0.4 + 65 + i*65);
        this->texte.setFillColor(sf::Color::Yellow);
        this->fenetre->draw(this->curseur);
      }
      this->fenetre->draw(this->texte);
    }

    this->fenetre->display();

  }

  if(nomJoueur == "") nomJoueur = "Xox";
  this->jeu.genererJoueur(nomJoueur, nomType);
}

unsigned int Jeu_sfml::selectionnerDonjon(){
  this->jeu.effacerDonjon();
  this->texte.setCharacterSize(50);
  this->texte.setFillColor(sf::Color::White);
  unsigned int choix = 0;
  unsigned int nbDonjons = this->jeu.getListeDonjons().nbDonjons;
  bool quit = false;

  while (this->fenetre->isOpen() && !quit){
    Event event;
    while (this->fenetre->pollEvent(event)){
      if (event.type == Event::Closed) this->fenetre->close();
      if (event.type == sf::Event::KeyPressed){
        switch(event.key.code){
          case sf::Keyboard::Up:
          son.play();
          if(choix == 0) choix = nbDonjons-1;
          else choix--;
          break;
          case sf::Keyboard::Down:
          son.play();
          if(choix == nbDonjons-1) choix = 0;
          else choix++;
          break;
          case sf::Keyboard::Space:
            if(this->jeu.getJoueur().getNiveau() >= this->jeu.getListeDonjons().donjonsDisponibles[choix].niveauNecessaire) {
            son2.play();
            quit = true;
          }
          break;
          default: break;
        }
      }
    }
    this->fenetre->clear();

    this->texte.setFillColor(sf::Color::White);
    this->texte.setPosition(50, 50);
    this->texte.setString("Selectionnez un donjon :");
    this->fenetre->draw(this->texte);

    for(unsigned int i=0; i < nbDonjons ; i++){
      if(this->jeu.getJoueur().getNiveau() < this->jeu.getListeDonjons().donjonsDisponibles[i].niveauNecessaire) this->texte.setFillColor(sf::Color(120, 120, 120));
      else this->texte.setFillColor(sf::Color::White);
      this->texte.setPosition(TAILLE_SPRITE + 20, TAILLE_SPRITE*2 + i*TAILLE_SPRITE);
      string infos = this->jeu.getListeDonjons().donjonsDisponibles[i].nom + " [Niv." + std::to_string(this->jeu.getListeDonjons().donjonsDisponibles[i].niveauNecessaire) + "]";
      this->texte.setString(infos);
      if(choix == i){
        this->curseur.setPosition(20, TAILLE_SPRITE*2 + i*TAILLE_SPRITE);
        this->fenetre->draw(this->curseur);
      }
      this->fenetre->draw(this->texte);
    }

    this->fenetre->display();
  }

  this->jeu.genererDonjon(choix);
  return choix;
}

void Jeu_sfml::boucleSFML(){
  this->jeu.getJoueurOriginal().reinitialiserStats();
  bool finDuJeu = false;
  bool tourJoueur = true;
  char c = ' ';
  int mode = 0;  //mode 0 : attente deplacement, mode 1 : choix attaque, mode 2 : choix objet
  bool deplacementEffectue = false;
  unsigned int choixComp = 0;
  unsigned int choixObj = 0;

  musique.play();
  this->fenetre->clear();
  this->texte.setFillColor(sf::Color::White);
  this->afficherMessageConsole("Ce donjon possede " + to_string(this->jeu.getDonjon().getNbEtages()) + " etages.\nBonne chance!");
  while(!finDuJeu && this->fenetre->isOpen()){
    this->afficherSFML();
    deplacementEffectue = false;
    while(tourJoueur &&this->fenetre->isOpen()){
      this->afficherSFML();

      switch(mode){
        case 0: //mode dplacement
        c = this->lireTouche();
        if(c=='z' || c=='d' || c=='s' || c=='q') deplacementEffectue = this->jeu.actionClavierDeplacementJoueur(c);
        if(deplacementEffectue){
          this->afficherSFML();
          tourJoueur = false;
          unsigned int jX = this->jeu.getJoueur().getX();
          unsigned int jY = this->jeu.getJoueur().getY();
          if(this->jeu.getDonjon().getEtageActif().getCase(jX,jY).id == 10){
            this->afficherSFML();
            if(this->jeu.getDonjon().getNbEtagesParcourus() < this->jeu.getDonjon().getNbEtages()-1){
              if(this->questionConsole("Voulez vous acceder  l'etage suivant ?")){
                this->jeu.monterEtageSuivant();
                tourJoueur = true;
              }
            }else{
              if(this->jeu.getDonjon().getEtageActif().getNbEnnemis()>0){
                this->afficherMessageConsole("Achevez tous les ennemis avant de sortir du donjon !");
              }else{
                afficherMessageConsole("Vous tes sorti sain et sauf du donjon !");
                unsigned int xp = (this->choixDonjon+1)*100;
                this->jeu.getJoueurOriginal().obtenirExp(xp);
                if(xp!=0) afficherMessageConsole("+ " + to_string(xp) + "XP !");
                finDuJeu = true;
              }
            }
          }
        }
        if(c == 'c') mode = 1;
        if(c == 'i') mode = 2;
        if(c=='Q'){
            bool quitter = this->questionConsole("Voulez-vous quitter le jeu ?");
            afficherSFML();
          if(quitter){
            this->afficherMessageConsole("Fichier de sauvegarde choisi : " + to_string(this->choixSauvegarde));
            if(this->questionConsole("Sauvegarder votre progression ?")){

              this->jeu.sauvegarderDansIemeFichier(this->choixSauvegarde);
              this->afficherMessageConsole("Jeu sauvegarde !");
            }
            this->afficherMessageConsole("A la prochaine !");
            finDuJeu = false;
            this->fenetre->close();
          }
        }
        break;
        case 1://mode attaque
        this->afficherCompetences(choixComp);
        do{c = this->lireTouche();}while(c!='z' && c!='s' && c!='E' && c!='c' && c!='i' && c!='Q');
        switch(c){
          case 'z':
          son.play();
          if(choixComp == 0){
            choixComp = this->jeu.getJoueur().getNbCompetencesApprises() - 1;
          }else{
            choixComp --;
          }
          break;
          case 's':
          son.play();
          if(choixComp == this->jeu.getJoueur().getNbCompetencesApprises() - 1){
            choixComp = 0;
          }else{
            choixComp ++;
          }
          break;
          case 'E':
          if(this->jeu.getJoueur().peutUtiliserIemeCompetence(choixComp)){
            unsigned int nbEnnemisTouches=0, xp=0, niveau = this->jeu.getJoueur().getNiveau(), nbComp=this->jeu.getJoueur().getNbCompetencesApprises();
            unsigned int * degats = NULL;
            string * ennemis = NULL;
            Competence * comp = this->jeu.getJoueur().getCompetence(choixComp);
            Stats stats = this->jeu.getJoueur().getStats();
            bool attaqueReussie = this->jeu.joueurUtiliseCompetence(comp, nbEnnemisTouches, ennemis, degats, xp);
            afficherMessageConsole("Vous utilisez " + comp->nom + " !");
            if(!attaqueReussie){
              this->afficherMessageConsole("Attaque ratee !");
            } else {
              if(nbEnnemisTouches > 0){
                this->afficherSFML();
                for(unsigned int j=0; j< nbEnnemisTouches; j++){
                  this->afficherMessageConsole(this->jeu.getJoueur().getNom() + " a inflige " + to_string(degats[j]) + " degats  a " + ennemis[j]);
                }
                if(xp>0) afficherMessageConsole("KO ! +" + to_string(xp) + "XP");
              }else if(comp->degats != 0) {
                afficherMessageConsole("Vous n'avez touche personne.");
              }

              //feedback comp�tences
              if (comp->buffAtk != 0) {
                string ampleur;
                if (comp->buffAtk < 0) {
                  if (comp->buffAtk < -2) {
                    ampleur = "enormement ";
                  } else if (comp->buffAtk < -1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole("Votre attaque a " + ampleur + "diminue...");
                } else {
                  if (comp->buffAtk > 2) {
                    ampleur = "enormement ";
                  } else if (comp->buffAtk > 1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole("Votre attaque a " + ampleur + "augmente !");
                }
              }
              if (comp->buffDef != 0) {
                string ampleur;
                if (comp->buffDef < 0) {
                  if (comp->buffDef < -2) {
                    ampleur = "enormement ";
                  } else if (comp->buffDef < -1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole("Votre defense a " + ampleur + "diminue...");
                } else {
                  if (comp->buffDef > 2) {
                    ampleur = "enormement ";
                  } else if (comp->buffDef > 1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole("Votre defense a " + ampleur + "augmente !");
                }
              }
              if (comp->gainPv != 0) {
                if (comp->gainPv < 0) {
                  this->afficherMessageConsole("Vous avez perdu " + std::to_string(-1*comp->gainPv) + " points de vie...");
                } else {
                  this->afficherMessageConsole("Vous avez gagne " + std::to_string(comp->gainPv) + " points de vie !");
                }
              }
              if (comp->gainMana > 0) {
                this->afficherMessageConsole("Vous avez gagne " + std::to_string(comp->gainMana) + " points de mana !");
              }

            }

            if(niveau < this->jeu.getJoueur().getNiveau()){
                this->afficherSFML();
                  Stats stats2 = this->jeu.getJoueur().getStats();
                  afficherMessageConsole("Montee de niveau ! " + to_string(niveau) + "->" + to_string(this->jeu.getJoueur().getNiveau()));
                  string message = "Points de vie : " + to_string(stats.pvMax) + "->" + to_string(stats2.pvMax) + "\n";
                  message += "Points de mana : " + to_string(stats.manaMax) + "->" + to_string(stats2.manaMax);
                  afficherMessageConsole(message);
                  message = "Attaque : " + to_string(stats.atk) + "->" + to_string(stats2.atk) + "\n";
                  message += "Defense : " + to_string(stats.def) + "->" + to_string(stats2.def);
                  afficherMessageConsole(message);

                  if(nbComp < this->jeu.getJoueur().getNbCompetencesApprises()){
                    this->fenetre->clear();
                    this->afficherSFML();
                    for(unsigned int k = 0; k < this->jeu.getJoueur().getNbCompetencesApprises() - nbComp; k++){
                      afficherMessageConsole("Attaque apprise : " + this->jeu.getJoueur().getCompetence(nbComp + k)->nom);
                    }
                  }
                  stats = this->jeu.getJoueur().getStats();
                  niveau = this->jeu.getJoueur().getNiveau();
                }
            if(degats != NULL) delete[] degats;
            if(ennemis != NULL) delete[] ennemis;
            mode = 0;
            tourJoueur = false;
          }
          break;
          case 'c':
          son3.play();
          mode = 0;
          break;
          case 'i':
          mode = 2;
          break;
          case 'Q':
          son3.play();
          mode = 0;
          break;

        }
        break;
        case 2://mode inventaire
        this->afficherInventaire(choixObj);
        do{c = this->lireTouche();}while(c!='z' && c!='s' && c!='E' && c!='J' && c!='c' && c!='i' && c!='Q');
        switch(c){
          case 'z':
          son.play();
          if(choixObj == 0){
            choixObj = this->jeu.getJoueur().getNbObjets() - 1;
          }else{
            choixObj --;
          }
          break;
          case 's':
          son.play();
          if(choixObj == this->jeu.getJoueur().getNbObjets() - 1){
            choixObj = 0;
          }else{
            choixObj ++;
          }
          break;
          case 'E':
          if(this->jeu.getJoueur().getNbObjets()>0){
            this->jeu.getJoueurOriginal().utiliserIemeObjet(choixObj);
            choixObj = 0;
            mode = 0;
          }
          break;
          case 'J':
          if(this->jeu.getJoueur().getNbObjets()>0){
                unsigned int x = this->jeu.getJoueur().getX();
                unsigned int y = this->jeu.getJoueur().getY();
                if(this->jeu.getDonjon().getEtageActif().getCase(x,y).objet == NULL && this->jeu.getDonjon().getEtageActif().getCase(x,y).id != 10){
                this->jeu.getDonjonOriginal().getEtageActifOriginal().ajouterObjetCase(x,y,this->jeu.getJoueur().getObjet(choixObj));
                this->jeu.getJoueurOriginal().retirerObjet(choixObj);
                tourJoueur = false;
                mode = 0;
                choixObj = 0;
            }
          }
          break;
          case 'c':
          mode = 1;
          choixObj = 0;
          break;
          case 'i':
          son3.play();
          mode = 0;
          choixObj = 0;
          break;
          case 'Q':
          son3.play();
          mode = 0;
          choixObj = 0;
          break;
          default:break;
        }

        break;
        default:break;
      }
    }
    //tour Ennemis

    if(!finDuJeu){

      Ennemi * ennemi = NULL;
      Competence * compChoisie = NULL;
      string nomEnnemi;
      for(unsigned int i=0; i < this->jeu.getDonjon().getEtageActif().getNbEnnemis(); i++){
        if(this->jeu.iemeEnnemiPresDeJoueur(i)){
          ennemi = &(this->jeu.getDonjonOriginal().getEtageActifOriginal().getEnnemiOriginal(i));
          nomEnnemi = ennemi->getType().nom;
          compChoisie = ennemi->choixCompetenceAleatoire();
          if(compChoisie != NULL){
            this->afficherSFML();
            this->afficherMessageConsole(nomEnnemi + " : J'utilise '" + compChoisie->nom + " !!");
            unsigned int degatsEnnemis=0;
            bool attaqueReussie = jeu.iemeEnnemiUtiliseCompetence(i, compChoisie, degatsEnnemis);
            if(attaqueReussie){
              if (compChoisie->degats != 0) {
                this->afficherMessageConsole(nomEnnemi + " vous a inflige " + std::to_string(degatsEnnemis) + " degats.");
              }

              if (compChoisie->buffAtk != 0) {
                string ampleur;
                if (compChoisie->buffAtk < 0) {
                  if (compChoisie->buffAtk < -2) {
                    ampleur = "enormement ";
                  } else if (compChoisie->buffAtk < -1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole(nomEnnemi + " : Mon attaque a " + ampleur + "diminue...");
                } else {
                  if (compChoisie->buffAtk > 2) {
                    ampleur = "enormement ";
                  } else if (compChoisie->buffAtk > 1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole(nomEnnemi + " : Mon attaque a " + ampleur + "augmente !");
                }
              }
              if (compChoisie->buffDef != 0) {
                string ampleur;
                if (compChoisie->buffDef < 0) {
                  if (compChoisie->buffDef < -2) {
                    ampleur = "enormement ";
                  } else if (compChoisie->buffDef < -1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole(nomEnnemi + " : Ma defense a  " + ampleur + "diminue...");
                } else {
                  if (compChoisie->buffDef > 2) {
                    ampleur = "enormement ";
                  } else if (compChoisie->buffDef > 1) {
                    ampleur = "";
                  } else {
                    ampleur = "legerement ";
                  }
                  this->afficherMessageConsole(nomEnnemi + " : Ma defense a  " + ampleur + "augmente !");
                }
              }
              if (compChoisie->gainPv != 0) {
                if (compChoisie->gainPv < 0) {
                  this->afficherMessageConsole(nomEnnemi + " : J'ai perdu " + std::to_string(-1*compChoisie->gainPv) + "points de vie...");
                } else {
                  this->afficherMessageConsole(nomEnnemi + " : J'ai gagne " + std::to_string(compChoisie->gainPv) + "points de vie !");
                }
              }
              if (compChoisie->gainMana > 0) {
                this->afficherMessageConsole(nomEnnemi + " : J'ai gagne " + std::to_string(compChoisie->gainMana) + " points de mana !");
              }

            }else{
              this->afficherMessageConsole(nomEnnemi + " : J'ai rate mon attaque...");
            }
          }

          if(this->jeu.getJoueur().estMort()) finDuJeu = true;

        }else{
          this->jeu.deplacerIemeEnnemi(i);
          ennemi = NULL;
        }

      }
    }

    tourJoueur = true;
  }

  if(this->jeu.getJoueur().estMort()) afficherMessageConsole("Vous etes mort !");
}

char Jeu_sfml::lireTouche(){
  char c = ' ';
  Event event;
  if (this->fenetre->waitEvent(event)){
    if (event.type == Event::Closed) c = 'Q';
    if (event.type == sf::Event::KeyPressed){
      switch(event.key.code){
        case sf::Keyboard::Up :
        c = 'z';
        break;
        case sf::Keyboard::Right :
        c = 'd';
        break;
        case sf::Keyboard::Down :
        c = 's';
        break;
        case sf::Keyboard::Left :
        c = 'q';
        break;
        case sf::Keyboard::Z :
        c = 'z';
        break;
        case sf::Keyboard::D :
        c = 'd';
        break;
        case sf::Keyboard::S :
        c = 's';
        break;
        case sf::Keyboard::Q :
        c = 'q';
        break;
       /* case sf::Keyboard::Enter : //bug sur linux
        c = 'e';
        break;*/
        case sf::Keyboard::C :
        c = 'c';
        break;
        case sf::Keyboard::I :
        c = 'i';
        break;
        case sf::Keyboard::J :
        c = 'J';
        break;
        case sf::Keyboard::Space :
        c = 'E';
        break;
        case sf::Keyboard::Escape :
        c = 'Q';
        break;
        default:break;
      }
    }
    /* Cette partie fait interpréter "deux fois" l'input du E...
    if(event.type == sf::Event::TextEntered){
      if(event.text.unicode >= 'a' && event.text.unicode <= 'z'){
        c = event.text.unicode;
      }
    }*/
  }
  return c;
}

void Jeu_sfml::ecrireConsole(string message){
  this->console.setScale(1.21, 1.f);
  this->console.setPosition(20, HAUTEUR*2/3 + 40);
  this->fenetre->draw(console);

  this->texte.setFillColor(Color::White);
  this->texte.setPosition(60, HAUTEUR*2/3 + 60);
  /*if(message.size() >= 64){
  string temp = "\n";
  for(unsigned int i=63; i<message.size(); i++) temp = temp + message.at(i);
  message = message.substr(0, 63);
  message = message + temp;
}*/
this->texte.setString(message);
this->fenetre->draw(this->texte);
//this->fenetre->display();
}

void Jeu_sfml::afficherMessageConsole(string message, char ok){
  ecrireConsole(message);
  this->curseur.setPosition(LARGEUR*0.9, HAUTEUR*0.9 - 20);
  this->fenetre->draw(this->curseur);
  this->fenetre->display();
  char c;
  do{
    c=this->lireTouche();
  }while(c!=ok);
}

bool Jeu_sfml::questionConsole(string message, string option1, string option2){
  bool reponse = true;
  char c;
  do{
    ecrireConsole(message);
    this->texte.setPosition(LARGEUR*0.3, HAUTEUR*0.9-20);
    this->texte.setString(option1);
    this->fenetre->draw(this->texte);
    this->texte.setPosition(LARGEUR*0.7, HAUTEUR*0.9-20);
    this->texte.setString(option2);
    this->fenetre->draw(this->texte);
    if(reponse) this->curseur.setPosition(LARGEUR*0.3-TAILLE_SPRITE, HAUTEUR*0.9-20);
    else this->curseur.setPosition(LARGEUR*0.7-TAILLE_SPRITE, HAUTEUR*0.9-20);
    this->fenetre->draw(this->curseur);
    this->fenetre->display();
    c=lireTouche();
    if(c=='d' || c=='q') {
      son.play();
      reponse = !reponse;
    }
  }while(c!='E');
  if(reponse) son2.play();
  else son3.play();
  return reponse;
}

void Jeu_sfml::afficherSFML(){
  this->fenetre->clear();
  Sprite caseActuelle, joueur, ennemi, objet;
  unsigned int idTextureJoueur;

  unsigned int idCaseVide = 12 + 4*jeu.getListeTypesEnnemis().nbTypesEnnemis + jeu.getListeObjets().nbObjets;
  caseActuelle.setTexture(this->ltex.textures[idCaseVide]);
  for(unsigned int y=0; y<HAUTEUR/TAILLE_SPRITE; y++){
    for(unsigned int x=0; x<LARGEUR/TAILLE_SPRITE; x++){
      caseActuelle.setPosition(x*TAILLE_SPRITE, y*TAILLE_SPRITE);
      this->fenetre->draw(caseActuelle);
    }
  }

  unsigned int dimx = this->jeu.getDonjon().getEtageActif().getTailleX();
  unsigned int dimy = this->jeu.getDonjon().getEtageActif().getTailleY();
  unsigned int jX = this->jeu.getJoueur().getX();
  unsigned int jY = this->jeu.getJoueur().getY();


  for(unsigned int y=0; y < dimy; y++){
    for(unsigned int x=0; x < dimx; x++){
      Case caseXY = this->jeu.getDonjon().getEtageActif().getCase(x,y);
      unsigned int idCase = 12 + 4*jeu.getListeTypesEnnemis().nbTypesEnnemis + jeu.getListeObjets().nbObjets + caseXY.id;
      caseActuelle.setPosition(LARGEUR/2-(jX-x)*TAILLE_SPRITE, HAUTEUR/2-(jY-y)*TAILLE_SPRITE);
      caseActuelle.setTexture(this->ltex.textures[idCase]);
      this->fenetre->draw(caseActuelle);
      if(caseXY.objet != NULL){
        unsigned int idTextureObjet = 12 + 4*jeu.getListeTypesEnnemis().nbTypesEnnemis + jeu.idObjet(caseXY.objet);
        objet.setTexture(this->ltex.textures[idTextureObjet]);
        objet.setPosition(LARGEUR/2-(jX-x)*TAILLE_SPRITE, HAUTEUR/2-(jY-y)*TAILLE_SPRITE);
        this->fenetre->draw(objet);
      }
      bool presenceEnnemi = false, presenceJoueur = false;
      unsigned int idEnn=0;

      if(jeu.getJoueur().getX() == x && jeu.getJoueur().getY() == y) presenceJoueur = true;

      for(unsigned int i=0; i < this->jeu.getDonjon().getEtageActif().getNbEnnemis(); i++){
        const Ennemi * enn = &(this->jeu.getDonjon().getEtageActif().getEnnemi(i));
        if(enn->getX() == x && enn->getY() == y) {
          presenceEnnemi = true;
          idEnn = i;
        }
      }

      if(presenceJoueur){
        joueur.setPosition(LARGEUR/2, HAUTEUR/2 - TAILLE_SPRITE);
        string type = this->jeu.getJoueur().getType().nom;
        if(type=="Guerrier") idTextureJoueur = 0;
        if(type=="Mage") idTextureJoueur = 4;
        if(type=="Voleur") idTextureJoueur = 8;

        switch(this->jeu.getJoueur().getDirection()){
          case 1:
          idTextureJoueur +=1;
          break;
          case 2:
          idTextureJoueur +=2;
          break;
          case 4:
          idTextureJoueur +=3;
          break;
          default:break;
        }
        joueur.setTexture(this->ltex.textures[idTextureJoueur]);
        this->fenetre->draw(joueur);
      }else if(presenceEnnemi){
        const Ennemi * enn = &(this->jeu.getDonjon().getEtageActif().getEnnemi(idEnn));
        unsigned int idTextureEnnemi = 12 + 4*jeu.idEnnemi(enn);
        switch(enn->getDirection()){
          case 1:
          idTextureEnnemi +=1;
          break;
          case 2:
          idTextureEnnemi +=2;
          break;
          case 4:
          idTextureEnnemi +=3;
          break;
        }
        ennemi.setTexture(this->ltex.textures[idTextureEnnemi]);
        ennemi.setPosition(LARGEUR/2-(jX-enn->getX())*TAILLE_SPRITE, HAUTEUR/2-(jY-enn->getY())*TAILLE_SPRITE - TAILLE_SPRITE);
        this->fenetre->draw(ennemi);
      }

    }
  }

  this->console.setScale(0.5f, 0.5f);
  this->console.setPosition(20, 20);
  this->fenetre->draw(this->console);
  this->console.setScale(0.5f, 0.5f);
  this->console.setPosition(LARGEUR*0.59, 20);
  this->fenetre->draw(this->console);

  this->texte.setStyle(sf::Text::Regular);
  this->texte.setFillColor(sf::Color::White);
  this->texte.setPosition(38,28);
  this->texte.setString(this->jeu.getJoueur().getNom()+", "+this->jeu.getJoueur().getType().nom+" de niv."+ std::to_string(this->jeu.getJoueur().getNiveau()));
  this->fenetre->draw(this->texte);
  this->texte.setPosition(38,88);
  Stats s = this->jeu.getJoueur().getStats();
  this->texte.setString("PV : " + to_string(s.pv) + "/" + to_string(s.pvMax) + "  MP : " + to_string(s.mana) + "/" + to_string(s.manaMax));
  this->fenetre->draw(this->texte);
  this->texte.setPosition(LARGEUR*0.65, 60);
  this->texte.setString(this->jeu.getDonjon().getNom() + ", " +to_string(this->jeu.getDonjon().getNbEtagesParcourus()+1)+"F");
  this->fenetre->draw(this->texte);

  this->fenetre->display();
}

void Jeu_sfml::afficherCompetences(unsigned int choix){
  //this->fenetre->clear();
  //this->menu.setColor(sf::Color(255, 255, 255, 128));
  this->afficherSFML();
  this->menu.setScale(1.f, 0.7);
  this->menu.setPosition(LARGEUR/2 + TAILLE_SPRITE*3.5, TAILLE_SPRITE*2);
  this->fenetre->draw(menu);
  unsigned int limiteAffichage = 5;

  for (unsigned int i = 0; i < this->jeu.getJoueur().getNbCompetencesApprises(); ++i) {
    this->texte.setFillColor(sf::Color::White);
    this->texte.setStyle(sf::Text::Regular);
    if(choix == i){
      string description = this->jeu.getJoueur().getCompetence(i)->description;
      string coutMana = "Cout Mana : " + to_string(this->jeu.getJoueur().getCompetence(i)->coutMana), coutPv = "";
      string portee = "Portee : ";
      unsigned int k = this->jeu.getJoueur().getCompetence(i)->portee;
      if(this->jeu.getJoueur().getCompetence(i)->gainPv < 0) coutPv = "Cout PV : " + to_string(-1*this->jeu.getJoueur().getCompetence(i)->gainPv) + ", ";
      if(k>0) portee = portee + to_string(k);
      else portee = portee + "Vous-meme";
      this->ecrireConsole(description + "\n\n" + coutMana + ", " + coutPv + portee);
      this->curseur.setPosition(LARGEUR/2 + TAILLE_SPRITE*2.9, TAILLE_SPRITE*2.3 + (i%limiteAffichage)*TAILLE_SPRITE);
      this->texte.setStyle(sf::Text::Bold);
    }
    if(!this->jeu.getJoueur().peutUtiliserIemeCompetence(i)) this->texte.setFillColor(sf::Color(150,150,150));
    this->texte.setString(this->jeu.getJoueur().getCompetence(i)->nom);
    this->texte.setPosition(LARGEUR/2 + TAILLE_SPRITE*3.9 , TAILLE_SPRITE*2.3 + (i%limiteAffichage)*TAILLE_SPRITE);
    if((i >= ((int)(choix/limiteAffichage) + 1) * limiteAffichage - limiteAffichage) && (i<= ((int)(choix/limiteAffichage) + 1) * limiteAffichage - 1)) this->fenetre->draw(this->texte);
  }
  this->fenetre->draw(this->curseur);
  this->fenetre->display();
}

void Jeu_sfml::afficherInventaire(unsigned int choix){
  this->afficherSFML();
  this->menu.setScale(1.f, 0.7);
  this->menu.setPosition(LARGEUR/2 + TAILLE_SPRITE*3.5, TAILLE_SPRITE*2);
  this->fenetre->draw(menu);
  unsigned int limiteAffichage = 5;

  for (unsigned int i = 0; i < this->jeu.getJoueur().getNbObjets(); ++i) {
    this->texte.setFillColor(sf::Color::White);
    this->texte.setStyle(sf::Text::Regular);
    if(choix == i){
      string description = this->jeu.getJoueur().getObjet(i)->description;
      this->ecrireConsole(description);
      this->curseur.setPosition(LARGEUR/2 + TAILLE_SPRITE*2.9, TAILLE_SPRITE*2.3 + (i%limiteAffichage)*TAILLE_SPRITE);
      this->texte.setStyle(sf::Text::Bold);
    }
    this->texte.setString(this->jeu.getJoueur().getObjet(i)->nom);
    this->texte.setPosition(LARGEUR/2 + TAILLE_SPRITE*3.9 , TAILLE_SPRITE*2.3 + (i%limiteAffichage)*TAILLE_SPRITE);
    if((i >= ((int)(choix/limiteAffichage) + 1) * limiteAffichage - limiteAffichage) && (i<= ((int)(choix/limiteAffichage) + 1) * limiteAffichage - 1)) this->fenetre->draw(this->texte);
  }
  if(this->jeu.getJoueur().getNbObjets()>0) this->fenetre->draw(this->curseur);
  this->fenetre->display();
}

bool Jeu_sfml::demanderContinuer(){
    bool continuer = false;

    if(this->fenetre->isOpen()){
      this->fenetre->clear();
      if(questionConsole("Voulez vous sauvegarder ?")) this->jeu.sauvegarderDansIemeFichier(choixSauvegarde);
      continuer = this->questionConsole("Retourner a l'ecran de selection de donjon ?");

      if(continuer) this->selectionnerDonjon();
      else this->fenetre->close();
    }

    return continuer;
}
