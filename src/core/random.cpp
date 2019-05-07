#include <stdlib.h>
using namespace std;

unsigned int tirageAleatoire(const unsigned int min, const unsigned int max) {
  unsigned int r = (rand() % (max - min + 1)) + min;
  return r;
}

