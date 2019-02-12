// Moduuli: tiedoston_luku / tiedosto: main.cpp
// Moduulissa luetaan tiedosto rivi kerrallaan, tarkistetaan se virheiden varalta ja
// tallennetaan tietorakenteeseen.

#include "tiedoston_luku.hh"
#include "apufunktiot.hh"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

// Funktiossa luetaan tiedosto rekursiivisesti.
bool lue_tiedosto(ifstream& virta, Lista& lista){

    // Jos tiedosto on luettu loppuun virheittä palautetaan
    // pääohjelmaan true ja käyttöliittymän suoritus voi alkaa.
    if( virta.eof() ) {
        return true;

    } else {

        string rivi;
        getline(virta, rivi);

        // Jos tiedostossa on tyhjä rivi, se jätetään huomiotta
        // ja siirrytään lukemaan seuraavaa riviä
        if(rivi == ""){
          return lue_tiedosto(virta, lista);
        }

        // Alustetaan luokka, jossa rivin pilkkominen ja taulukkoon
        // tallentaminen tapahtuu.
        int sanoja_rivissa = 2;
        Rivin_kasittely eroteltu_rivi{sanoja_rivissa};

        eroteltu_rivi.aseta_merkkijono(rivi);

        // Jos rivi on kommentti tai se sisältää vain
        // välilyöntejä, se jätetään huomiotta ja siirrytään
        // lukemaan seuraavaa riviä.
        if( eroteltu_rivi.onko_kommentti_tai_valilyonti() ) {

            return lue_tiedosto(virta, lista);
        }

        // Erotellaan rivistä sana ja tarkistetaan se
        // virheiden varalta. Jos rivi on virheellinen
        // palautetaan pääohjelmaan false ja ohjelman suoritus loppuu.
        if ( not eroteltu_rivi.poista_valilyonnit() ) {
            return false;
        }

        string esine;
        string materiaali;

        // Haetaan taulukosta esine ja materiaali
        if ( eroteltu_rivi.hae_alkioiden_maara() == 2) {
            esine = eroteltu_rivi.hae_kentta(0);
            materiaali = eroteltu_rivi.hae_kentta(1);
        }

        // ja lisätään ne tietorakenteeseen. False palautetaan
        // siinä tapauksessa, jos sama esine-materiaali-pari on tiedostossa
        // useammin kuin kerran.
        if(not lista.lisaa_tietorakenteeseen(esine, materiaali)) {
            return false;
        }

        // Koska funktio on rekursiivinen, se palauttaa kutsun itseensä.
        return lue_tiedosto(virta, lista);





    }
}
