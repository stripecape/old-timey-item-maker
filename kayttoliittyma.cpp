

// Moduuli: kayttoliittyma / tiedosto: kayttoliittyma.cpp
// Sisältää käyttöliittymän askartelupeliin. Käyttöliittymä
// huolehtii käskyjen pituuden tarkistamisesta, käskyjen vaatimien
// metodien kutsumisesta ja virheilmoitusten tulostuksesta.

#include "kayttoliittyma.hh"
#include "apufunktiot.hh"
#include <iostream>
#include <string>

using namespace std;

bool kayttoliittyma(Lista& lista){

    string kasky;
    cout << "testikayttoliittyma> ";

    // Luetaan käsky ja viedään se luokkaan Rivien_kasittely pilkottavaksi.
    // Jos käyttäjä on syöttänyt tyhjän rivi, pelkkiä välilyöntejä
    // tai ohjelmalle tuntemattoman käskyn, nostetaan virheilmoitus.
    while (getline(cin, kasky)) {

        Rivin_kasittely rivi{10};

        rivi.aseta_merkkijono(kasky);
        if( not rivi.paloittele_kasky() ){
            cout << "Virhe: tuntematon kasky." << endl;

        } else {

            kasky = rivi.hae_kentta(0);
            int kaskyssa_sanoja = rivi.hae_alkioiden_maara();

            // Kun käyttäjä syöttää "loppu", false palautetaan pääohjelmaan
            // ja ohjelman suoritus lopetetaan.
            if ( kasky == "loppu"  and kaskyssa_sanoja == 1) {
                return false;

            } else if ( kasky == "reppu" and kaskyssa_sanoja == 1 ) {
                tyhjenna_reppu(lista);

            } else if ( kasky == "reppu" and kaskyssa_sanoja > 1 ) {
                aseta_reppu(lista, rivi);

            } else if ( kasky == "tulostareppu" ) {
                tulosta_reppu(lista, rivi);

            } else if ( kasky == "materiaalit" ) {
                materiaalit(lista, rivi);

            } else if ( kasky == "askarreltavissa" ) {
                askarreltavissa(lista, rivi);

            } else if ( kasky == "askarreltavissa_bonus" ) {
                askarreltavissa_bonus(lista, rivi);

            } else {
                cout << "Virhe: tuntematon kasky." << endl;
            }
        }

        cout << "testikayttoliittyma> ";
    }

   return true;
}


// Lisätään reppuun tavaraa.
void aseta_reppu(Lista& lista, Rivin_kasittely& rivi){
    lista.tyhjenna_reppu();

    // Haetaan tavarat yksi kerralaan taulukosta.
    for ( int i = 1 ; i < rivi.hae_alkioiden_maara() ; ++i ){
        string tavara = rivi.hae_kentta(i);

        // Jos käyttäjä on syöttänyt tavaran, jota ei löydy
        // tuotantoketjusta, nostetaan virheilmoitus ja palataan
        // käskyn kyselyyn.
        if( not lista.etsi_tuotantoketjusta(tavara) ){
            cout << "Virhe: tuntematon tavara." << endl;
            return;

        // Jos käyttäjä on yrittänyt syöttää saman tavaran
        // useammin kuin kerran, nostetaan virheilmoitus ja
        // tyhjennetään reppu.
        } else if( lista.loytyy_repusta(tavara) ) {
            cout << "Virhe: useampi sama tavara." << endl;
           lista.tyhjenna_reppu();
           return;

        } else {

            lista.lisaa_reppuun(tavara);
        }
    }
    cout << "Repun sisalto asetettu." << endl;
}


// Tyhjennetään reppu.
void tyhjenna_reppu(Lista& lista){
    lista.tyhjenna_reppu();
    cout << "Reppu tyhjennetty." << endl;
}


// Tulostetaan repun sisältö.
void tulosta_reppu(Lista& lista, Rivin_kasittely& rivi){
    if ( rivi.hae_alkioiden_maara() > 1) {
        cout << "Virhe: vaara maara sanoja syoterivilla." << endl;
                return;
    }

    lista.tulosta_repun_sisalto();
}


// Tutkitaan, onko tavara askarreltavissa repun materiaaleista.
void askarreltavissa(Lista& lista, Rivin_kasittely& rivi){
    if ( rivi.hae_alkioiden_maara() != 2 ) {
        cout << "Virhe: vaara maara sanoja syoterivilla." << endl;
        return;
    }

    string askarreltava = rivi.hae_kentta(1);

    // Jos tavara ei löydy tuotantoketjusta, nostetaan virheilmoitus
    if( not lista.etsi_tuotantoketjusta(askarreltava) ) {
        cout << "Virhe: tuntematon esine." << endl;
        return;
    }

    if( lista.askarreltavissa(askarreltava) ) {
        cout << "On askarreltavissa." << endl;

    } else {
        cout << "Ei ole askarreltavissa." << endl;
    }
}

// Tulostetaan käyttäjän syöttämän esineen askartelemiseen
// tarvittavat materiaalit aakkosjärjestyksessä.
void materiaalit(Lista& lista, Rivin_kasittely& rivi){
    if ( rivi.hae_alkioiden_maara() != 2 ) {
        cout << "Virhe: vaara maara sanoja syoterivilla." << endl;
        return;
    }
    string esine = rivi.hae_kentta(1);

    if( not lista.tulosta_materiaalit(esine) ) {
        cout << "Virhe: tuntematon esine." << endl;
    }


}

// Tutkitaan, onko tavara askarreltavissa repun materiaaleista.
void askarreltavissa_bonus(Lista& lista, Rivin_kasittely& rivi){
    if( rivi.hae_alkioiden_maara() != 2 ) {
        cout << "Virhe: vaara maara sanoja syoterivilla." << endl;
        return;
    }

    string askarreltava = rivi.hae_kentta(1);

    // Jos tavara ei löydy tuotantoketjusta, nostetaan virheilmoitus.
    if ( not lista.etsi_tuotantoketjusta(askarreltava) ) {
        cout << "Virhe: tuntematon esine." << endl;
        return;
    }

    if( lista.askarreltavissa_bonus(askarreltava) ) {
        cout << "On askarreltavissa." << endl;
    } else {
        cout << "Ei ole askarreltavissa." << endl;
    }
}


