// Moduuli: main / tiedosto: main.cpp
// Sisältää pääohjelman askartelupelille.

#include "tiedoston_luku.hh"
#include "apufunktiot.hh"
#include "kayttoliittyma.hh"
#include "lista.hh"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    Lista lista;


    string tiedoston_nimi;
    cout << "Syotetiedosto: ";
    getline(cin, tiedoston_nimi);

    ifstream virta(tiedoston_nimi);
    if( not virta ){
        cout << "Virhe: syötetiedostoa " + tiedoston_nimi + " ei voida lukea." << endl;
        return 1;
    }

    if ( not lue_tiedosto(virta, lista) ) {
        cout << "Virhe: syötetiedosto " + tiedoston_nimi + " virheellinen." << endl;
        return 1;
    }
    cout << "Tuotantoketjut luettu onnistuneesti." << endl;

    virta.close();

    if( not kayttoliittyma(lista) ){
        return 1;
    }
}


