#include "TypeEnnemi.h"

void effacerTypeEnnemi(TypeEnnemi &t){
  delete [] t.competences;
  t.competences = NULL;
}
