// Moduuli kayttoliittyma / tiedosto: kayttoliittyma.hh
// Moduulin kayttoliittyma esittelytiedosto:
// sisältää esittelyn käyttöliittymän funktioista.

#ifndef KAYTTOLIITTYMA_HH
#define KAYTTOLIITTYMA_HH
#include "lista.hh"
#include "apufunktiot.hh"
#include <string>

using namespace std;

bool kayttoliittyma(Lista& lista);
void tyhjenna_reppu(Lista& lista);
void aseta_reppu(Lista& lista, Rivin_kasittely& rivi);
void tulosta_reppu(Lista& lista, Rivin_kasittely& rivi);
void askarreltavissa(Lista& lista, Rivin_kasittely& rivi);
void materiaalit(Lista& lista, Rivin_kasittely& rivi);
void askarreltavissa_bonus(Lista& lista, Rivin_kasittely& rivi);

#endif // KAYTTOLIITTYMA_HH
