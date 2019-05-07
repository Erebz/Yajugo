#include <fstream> /*! \headerfile fstream */
#include <string.h> /*! \headerfile string.h */
#include <iostream> /*! \headerfile iostream */
#include <cassert> /*! \headerfile cassert */
#include <stdlib.h>
#include "Etage.h" /*! \headerfile "Etage.h" */
#include "random.h" /*! \headerfile "random.h" */
using namespace std; /*! \namespace std*/
/*!
* \file Etage.cpp
* \brief Fichier cpp de la structure Etage
* \author J. Grosjean, Y. Hamdi, H. Messina
* \version 1.0
* \date 25/03/2019
*/

Etage::Etage() {
  tailleX = 0;
  tailleY = 0;
  nbEnnemis = 0;
  ennemis = NULL;
}

Etage::Etage(unsigned int x, unsigned int y, const ListeCases & lcase) {
  for (unsigned int y = 0; y < TAILLE_Y; ++y) {
    for (unsigned int x = 0; x < TAILLE_X; x++) {
      this->cases[y][x] = lcase.listeCases[0];
    }
  }

  tailleX = x;
  tailleY = y;
  nbEnnemis = 0;
  ennemis = NULL;
}

Etage::Etage(const InfosEtage& infos, const ListeCases & lcase, const ListeCompetences & lcomp, const ListeTypesEnnemis & lenn, const ListeObjets & lobj) {
  for (unsigned int y = 0; y < TAILLE_Y; ++y) {
    for (unsigned int x = 0; x < TAILLE_X; x++) {
      this->cases[y][x] = lcase.listeCases[0];
    }
  }

  this->tailleX = infos.tailleX;
  this->tailleY = infos.tailleY;

  //generation des salles
  this->genererSalles(infos.nbIdSalles, infos.idSalles, infos.nbSalles, lcase);

  //generation des murs
  this->genererMurs(lcase);

  //Generation des ennemis d'après InfosEtage
  this->genererEnnemis(infos.nbEnnemis, infos.nbEnnemisRencontrables, infos.ennemisRencontrables, lcomp, lenn, infos.niveauMin, infos.niveauMax);

  //Generation des objets d'après InfosEtage
  this->genererObjets(infos.nbObjets, infos.nbObjetsTrouvables, infos.objetsTrouvables, lobj);
}

Etage::~Etage(){
  delete [] this->ennemis;
  this->ennemis = NULL;
}

unsigned int Etage::getTailleX() const {
  return this->tailleX;
}

unsigned int Etage::getTailleY() const {
  return this->tailleY;
}

const Case& Etage::getCase(const unsigned int x, const unsigned int y) const { //precondition : x et y valides
  return this->cases[y][x];
}

void Etage::ajouterObjetCase(const unsigned int x, const unsigned int y, Objet * obj){
  this->cases[y][x].objet = obj;
}

void Etage::retirerObjetCase(const unsigned int x, const unsigned int y) {
  this->cases[y][x].objet = NULL;
}

unsigned int Etage::getNbEnnemis() const {
  return this->nbEnnemis;
}

const Ennemi& Etage::getEnnemi(const unsigned int i) const { //precondition : i indice valide
  assert(i < this->nbEnnemis);
  return this->ennemis[i];
}

Ennemi& Etage::getEnnemiOriginal(const unsigned int i) const{
  assert(i < this->nbEnnemis);
  return this->ennemis[i];
}

void Etage::retirerIemeEnnemi(const unsigned int i){
  assert(i < this->nbEnnemis);

  unsigned int n = 0;
  Ennemi * temp = new Ennemi [this->nbEnnemis - 1];
  for (unsigned int k = 0; k < this->nbEnnemis; k++) {
    if (k != i) {
      temp[n] = this->ennemis[k];
      n++;
    }
  }

  delete [] this->ennemis;
  this->ennemis = temp;
  this->nbEnnemis--;

}

bool Etage::caseDisponible(const unsigned int x, const unsigned int y) const {

  bool caseTraversable = this->cases[y][x].traversable;
  bool caseLibre = true;

  if (caseTraversable) {
    for (unsigned int i = 0; i < this->nbEnnemis; ++i) {
      if (this->ennemis[i].getX() == x && this->ennemis[i].getY() == y) caseLibre = false;
    }
  }

  return (caseTraversable && caseLibre);
}

void Etage::genererEnnemis(const unsigned int nbEnnemis, const unsigned int nbTypesEnnemis, const unsigned int * typesEnnemis, const ListeCompetences& lcomp,const ListeTypesEnnemis & lenn, const unsigned int nivMin, const unsigned int nivMax) {
  //precondition : Il n'y a pas plus d'ennemis à generer que de cases disponibles dans l'étage et les typesEnnemis sont valides

  this->nbEnnemis = nbEnnemis;
  this->ennemis = new Ennemi [this->nbEnnemis];

  unsigned int indiceType = 0;
  unsigned int niveau = 0;
  for (unsigned int i = 0; i < this->nbEnnemis; i++) {
    indiceType = typesEnnemis[tirageAleatoire(0, nbTypesEnnemis - 1)];
    niveau = tirageAleatoire(nivMin, nivMax);

    //cout << lenn.listeTypesEnnemis[indiceType].nom << ", niv." << niveau << endl;
    Ennemi e(lenn.listeTypesEnnemis[indiceType], niveau, lcomp);

    //Il faut aussi initialiser la position des ennemis
    unsigned int x = 0, y = 0;
    bool caseOccupee = false;
    do {
      x = tirageAleatoire(0, this->tailleX - 1);
      y = tirageAleatoire(0, this->tailleY - 1);
      caseOccupee = false;
      for (unsigned int k = 0; k < i; ++k) {
        if (this->ennemis[k].getX() == x && this->ennemis[k].getY() == y) caseOccupee = true;
      }
    } while(!this->cases[y][x].traversable || caseOccupee);

    e.setCoordonnees(x, y);
    this->ennemis[i] = e;

  }
}

void Etage::genererObjets(const unsigned int nbObjets, const unsigned int nbTypesObjets, const unsigned int * typeObjets, const ListeObjets &lobj){
  //precondition : Il n'y a pas plus d'objets que de cases disponibles dans l'étage et les typesObjets sont valides
  unsigned int x = 0;
  unsigned int y = 0;
  unsigned int indiceObjet = 0;
  for (unsigned int i = 0; i < nbObjets; i++) {
    do{
      x = tirageAleatoire(0, this->tailleX);
      y = tirageAleatoire(0, this->tailleY);
    }while(!this->cases[y][x].traversable || this->cases[y][x].objet!=NULL || this->cases[y][x].id==10);
    indiceObjet = typeObjets[tirageAleatoire(0, nbTypesObjets-1)];
    this->cases[y][x].objet = &(lobj.listeObjets[indiceObjet]);
  }
}


const Etage& Etage::operator = (const Etage & etage){
  this->tailleX = etage.getTailleX();
  this->tailleY = etage.getTailleY();
  for(unsigned int y = 0; y < etage.getTailleY(); y++){
    for (unsigned int x = 0; x < etage.getTailleX(); x++) {
      this->cases[y][x] = etage.getCase(x, y);
    }
  }
  this->nbEnnemis = etage.getNbEnnemis();
  if (this->ennemis != NULL) delete [] this->ennemis;
  this->ennemis = new Ennemi [this->nbEnnemis];
  for (unsigned int i = 0; i < this->nbEnnemis; i++){
    this->ennemis[i] = etage.getEnnemi(i);
  }
  return *this;
}

void Etage::genererSalles(const unsigned int nbIdSalles, const unsigned int * idSalles, const unsigned int nbSalles, const ListeCases & lcase) {
  unsigned int idSalle = 0;

  unsigned int positionX = 0, positionY = 0;
  unsigned int dimX = 0, dimY = 0;

  unsigned int debutCheminX = 0, debutCheminY = 0;
  unsigned int finCheminX = 0, finCheminY = 0;

  for (unsigned int i = 0; i < nbSalles; i++) {
    //on choisit une salle parmi la liste donnée
    idSalle = idSalles[tirageAleatoire(0, nbIdSalles - 1)];

    string emplacement = "data/Salles/Salle";
    char id = idSalle + 48;
    string format = ".txt";
    string nomFichier = emplacement + id + format;
    ifstream fichierSalle(nomFichier.c_str());

    //lecture de la salle depuis fichier
    if (fichierSalle.is_open()) {
      char c;

      fichierSalle >> dimX >> c >> dimY >> c;

      //on choisit une salle + on verifie que la place est libre
      do {
        positionX = tirageAleatoire(0, this->tailleX - dimX);
        positionY = tirageAleatoire(0, this->tailleY - dimY);
      } while (!this->sallePosable(positionX, positionY, dimX, dimY));

      //on pose la salle
      unsigned int indiceCase = 0;
      for (unsigned int y = 0; y < dimY; y++) {
        for (unsigned int x = 0; x < dimX; x++) {
          fichierSalle >> indiceCase;
          //On pose les cases seulement sur des blocs pleins
          if (this->cases[y + positionY][x + positionX].id == 0) {
            this->cases[y + positionY][x + positionX] = lcase.listeCases[indiceCase];
          }
        }
      }

      //on selectionne un point pour le chemin
      do {
        finCheminX = tirageAleatoire(positionX, positionX + dimX - 1);
        finCheminY = tirageAleatoire(positionY, positionY + dimY - 1);
      } while (this->cases[finCheminY][finCheminX].id != 5);

      if (i > 0) {
        //on construit le chemin
        int deltaX = finCheminX - debutCheminX;
        int deltaY = finCheminY - debutCheminY;

        unsigned int coupureX = 0;
        if (debutCheminX < finCheminX) {
          coupureX = tirageAleatoire(debutCheminX, finCheminX);
        } else {
          coupureX = tirageAleatoire(finCheminX, debutCheminX);
        }

        unsigned int coupureY = 0;
        if (debutCheminY < finCheminY) {
          coupureY = tirageAleatoire(debutCheminY, finCheminY);
        } else {
          coupureY = tirageAleatoire(finCheminY, debutCheminY);
        }

        // cout << debutCheminX << ", " << debutCheminY << endl;
        // cout << finCheminX << ", " << finCheminY << endl;
        // cout << coupureX << ", " << coupureY << endl;
        // cout << deltaX << ", " << deltaY << endl;

        if (deltaX > 0) {
          for (unsigned int k = debutCheminX; k < finCheminX; k++) {
            if (k < coupureX) {
              this->cases[debutCheminY][k] = lcase.listeCases[5];
            } else {
              this->cases[coupureY][k] = lcase.listeCases[5];
            }
          }
        } else {
          for (unsigned int k = debutCheminX; k > finCheminX; k--) {
            if (k > coupureX) {
              this->cases[debutCheminY][k] = lcase.listeCases[5];
            } else {
              this->cases[coupureY][k] = lcase.listeCases[5];
            }
          }
        }

        if (deltaY > 0) {
          for (unsigned int k = debutCheminY; k < finCheminY; k++) {
            if (k < coupureY) {
              this->cases[k][coupureX] = lcase.listeCases[5];
            } else {
              this->cases[k][finCheminX] = lcase.listeCases[5];
            }
          }
        } else {
          for (unsigned int k = debutCheminY; k > finCheminY; k--) {
            if (k > coupureY) {
              this->cases[k][coupureX] = lcase.listeCases[5];
            } else {
              this->cases[k][finCheminX] = lcase.listeCases[5];
            }
          }
        }

      }

      // this->cases[debutCheminY][debutCheminX].caractere = "c";
      // this->cases[finCheminY][finCheminX].caractere = "c";
      //
      // this->cases[positionY][positionX].caractere = "+";
      // this->cases[positionY + dimY - 1][positionX + dimX - 1].caractere = "+";

      //on memorise le point pour le chemin futur
      debutCheminX = finCheminX;
      debutCheminY = finCheminY;

      fichierSalle.close();
    }
  }

  // on place un escalier dans la derniere salle
  unsigned int escalierX = 0, escalierY = 0;
  do {
    escalierX = tirageAleatoire(positionX, positionX + dimX - 1);
    escalierY = tirageAleatoire(positionY, positionY + dimY - 1);
  } while (this->cases[escalierY][escalierX].id != 5);
  this->cases[escalierY][escalierX] = lcase.listeCases[10];

}

bool Etage::sallePosable(unsigned int positionX, unsigned int positionY, unsigned int dimX, unsigned int dimY) {
  bool posable = true;
  for (unsigned int y = 0; y < dimY; y++) {
    for (unsigned int x = 0; x < dimX; x++) {
      if (this->cases[y + positionY][x + positionX].id != 0) {
        posable = false;
      }
    }
  }
  return posable;
}

void Etage::genererMurs(const ListeCases & lcase) {
  for (unsigned int y = 0; y < this->tailleY; y++) {
    for (unsigned int x = 0; x < this->tailleX; x++) {
      //on check que si la case est un bloc plein
      if (this->cases[y][x].id == 0) {
        string voisins = "";
        for (unsigned int i = 0; i < 3; i++) {
          for (unsigned int j = 0; j < 3; j++) {
            if ((x - 1 + j >= 0) && (y - 1 + i >= 0) && (x - 1 + j < this->tailleX) && (y - 1 + i < this->tailleY)) {
              unsigned int id_case = this->cases[y - 1 + i][x - 1 + j].id;
              if (id_case == 5 || id_case == 10) {
                voisins += "1";
              } else {
                voisins += "0";
              }
            } else {
              voisins += "0";
            }
          }
        }

        //coins interieurs
        if (voisins[8] == '1') {
          this->cases[y][x] = lcase.listeCases[1];
        }

        if (voisins[6] == '1') {
          this->cases[y][x] = lcase.listeCases[3];
        }

        if (voisins[2] == '1') {
          this->cases[y][x] = lcase.listeCases[7];
        }

        if (voisins[0] == '1') {
          this->cases[y][x] = lcase.listeCases[9];
        }

        //murs plat
        if (voisins[1] == '1') {
          this->cases[y][x] = lcase.listeCases[8];
        }

        if (voisins[3] == '1') {
          this->cases[y][x] = lcase.listeCases[6];
        }

        if (voisins[5] == '1') {
          this->cases[y][x] = lcase.listeCases[4];
        }

        if (voisins[7] == '1') {
          this->cases[y][x] = lcase.listeCases[2];
        }

        //coins exterieurs
        if (voisins[5] == '1' && voisins[7] == '1' && voisins[8] == '1') {
          this->cases[y][x] = lcase.listeCases[12];
        }

        if (voisins[3] == '1' && voisins[6] == '1' && voisins[7] == '1') {
          this->cases[y][x] = lcase.listeCases[11];
        }

        if (voisins[1] == '1' && voisins[2] == '1' && voisins[5] == '1') {
          this->cases[y][x] = lcase.listeCases[14];
        }

        if (voisins[0] == '1' && voisins[1] == '1' && voisins[3] == '1') {
          this->cases[y][x] = lcase.listeCases[13];
        }

        //cas plus complexes (murs en U)
        if (voisins[3] == '1' && voisins[5] == '1') {
          this->cases[y][x] = lcase.listeCases[16];
        }

        if (voisins[1] == '1' && voisins[7] == '1') {
          this->cases[y][x] = lcase.listeCases[19];
        }

        if (voisins[0] == '1' && voisins[1] == '1' && voisins[2] == '1' && voisins[3] == '1' && voisins[5] == '1') {
          this->cases[y][x] = lcase.listeCases[15];
        }

        if (voisins[1] == '1' && voisins[2] == '1' && voisins[5] == '1' && voisins[8] == '1' && voisins[7] == '1') {
          this->cases[y][x] = lcase.listeCases[20];
        }

        if (voisins[3] == '1' && voisins[6] == '1' && voisins[7] == '1' && voisins[8] == '1' && voisins[5] == '1') {
          this->cases[y][x] = lcase.listeCases[17];
        }

        if (voisins[1] == '1' && voisins[0] == '1' && voisins[3] == '1' && voisins[6] == '1' && voisins[7] == '1') {
          this->cases[y][x] = lcase.listeCases[18];
        }

        if (voisins == "111101111") {
          this->cases[y][x] = lcase.listeCases[21];
        }

      }
    }
  }
}
