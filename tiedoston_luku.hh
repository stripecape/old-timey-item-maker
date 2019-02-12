// Moduuli tiedoston_luku / tiedosto: tiedoston_luku.hh
// Moduulin tiedoston_luku esittelytiedosto:
// sisältää esittelyn tiedoston lukuun tarvittavalle funktiolle.

#ifndef TIEDOSTON_LUKU_HH
#define TIEDOSTON_LUKU_HH
#include "lista.hh"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool lue_tiedosto(ifstream& virta, Lista& lista);

#endif // TIEDOSTON_LUKU_HH
