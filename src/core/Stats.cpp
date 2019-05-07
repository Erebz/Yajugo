#include "Stats.h"
using namespace std;

void initialiserStats(Stats & s, const string &nomType) { //initialiser les stats d'un joueur
    if(nomType == "Guerrier") {
      s.pvMax = 30 + 20;
      s.pv = s.pvMax;
      s.manaMax = 15 + 10;
      s.mana = s.manaMax;
      s.atk = 20;
      s.buffAtk = 0;
      s.def = 30;
      s.buffDef = 0;
    }

    if(nomType == "Voleur") {
      s.pvMax = 20 + 20;
      s.pv = s.pvMax;
      s.manaMax = 20 + 10;
      s.mana = s.manaMax;
      s.atk = 20;
      s.buffAtk = 0;
      s.def = 20;
      s.buffDef = 0;
    }

    if(nomType == "Mage") {
      s.pvMax = 20 + 20;
      s.pv = s.pvMax;
      s.manaMax = 30 + 10;
      s.mana = s.manaMax;
      s.atk = 30;
      s.buffAtk = 0;
      s.def = 15;
      s.buffDef = 0;
    }
}

void initialiserStats(Stats & s, const TypeEnnemi &t, const unsigned int niveau){
  //se servir des coeff et du niveau pour modifier les Stats. Du genre :
  s.pvMax = (t.coeffPv * niveau) + (t.coeffPv * 10) + 20;
  s.pv = s.pvMax;
  s.manaMax = (t.coeffMana * niveau) + (t.coeffMana * 10) + 10;
  s.mana = s.manaMax;
  s.atk = (t.coeffAtk * niveau) + (t.coeffAtk * 10);
  s.def = (t.coeffDef * niveau) + (t.coeffDef * 10);
  s.buffAtk = 0; 
  s.buffDef = 0;
    
}

