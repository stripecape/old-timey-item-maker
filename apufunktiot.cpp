// Moduuli: apufunktiot / tiedosto: apufunktiot.cpp
// Sisältää yksityisen rajapinnan, jossa pilkotaan ohjelman saamat syötteet
// ja tarkistetaan syötteen oikeellisuus. Lopuksi syöte tallennetaan taulukkoon.

#include "apufunktiot.hh"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

// Alustetaan olio.
Rivin_kasittely::Rivin_kasittely(int taulukon_koko):
    merkkijono_{""},
    taulukko_{new string[taulukon_koko]},
    taulukon_koko_{taulukon_koko},
    alkioiden_maara_{0}{
}

// Purkaja
Rivin_kasittely::~Rivin_kasittely(){
    delete [] taulukko_;
}

// Tuodaan merkkijono luokkaan käsiteltäväksi.
void Rivin_kasittely::aseta_merkkijono(const string& merkkijono){
    merkkijono_ = merkkijono;
}

// Metodilla haetaan taulukon alkioita käyttöliittymään.
string Rivin_kasittely::hae_kentta(int indeksi){
    return taulukko_[indeksi];
}

// Haetaan taulukon alkioiden määrä käyttöliittymään.
int Rivin_kasittely::hae_alkioiden_maara(){
    return alkioiden_maara_;
}

// Tuplataan taulukon koko.
void Rivin_kasittely::kasvata_taulukkoa(){

    // Alustetaan uusi taulukko kaksi kertaa suuremmaksi kuin taulukko-olio
    // ja kopioidaan vanhan taulukon alkiot uuteen taulukkoon.
    string *uusi_taulukko = new string[2 * taulukon_koko_];
    for (int i = 0 ; i < alkioiden_maara_ ; ++i){
        uusi_taulukko[i] = taulukko_[i];
    }

    delete [] taulukko_;

    // Asetetaan uusi suurempi taulukko taulukko-olioon.
    taulukko_ = uusi_taulukko;
    taulukon_koko_ = 2 * taulukon_koko_;
}

// Tutkitaan onko rivi kommentti tai sisältääkö se pelkästään
// välilyöntejä.
bool Rivin_kasittely::onko_kommentti_tai_valilyonti() {

    if (merkkijono_.find_first_not_of(" ") == string::npos){
        return true;
    }

    unsigned int kommentin_tarkistus = merkkijono_.find_first_not_of(' ');
    if (merkkijono_.at(kommentin_tarkistus) == '#'){
        return true;
    }

    return false;
}

// Poistetaan välilyönnit reseptitiedostosta.
bool Rivin_kasittely::poista_valilyonnit(){

        // Jos rivi ei sisällä kaksoispistettä, rivi on virheellinen.
        if (merkkijono_.find(":") == string::npos ){
            return false;
        }

       // Etsitään mistä kaksoispiste löytyy ja jaetaan rivi kahtia sen
       // kohdalta.
       string::size_type kaksoispiste = merkkijono_.find(":");

       taulukko_[0] = merkkijono_.substr(0, kaksoispiste);
       taulukko_[1] = merkkijono_.substr(kaksoispiste + 1);

       // Käsitellään kumpikin sana kerrallaan ja poistetaan välilyönnit
       // etsimällä ensimmäinen ja viimeine välilyönti.
       string::size_type aloituskohta;
       string::size_type lopetuskohta;
       for ( int i = 0 ; i < 2 ; ++i ){

           aloituskohta = taulukko_[i].find_first_not_of(" ");
           lopetuskohta = taulukko_[i].find_last_not_of(" ");

           int sanan_pituus = lopetuskohta - aloituskohta + 1;
           taulukko_[i] = taulukko_[i].substr(aloituskohta, sanan_pituus );

           // Jos rivi sisältää vielä välilyöntejä, rivi on virheellinen.
           if ( taulukko_[i].find(" ") != string::npos ){
               return false;
            }
            ++alkioiden_maara_;

       }

       return true;
}


// Paloitellaan käyttäjän syöttämä käsky.
bool Rivin_kasittely::paloittele_kasky() {

    if ( merkkijono_ == ""){
        return false;
    }

    // Jos käyttäjä syötti vain välilyöntejä, palautetaan
    // false, mikä aiheuttaa virheilmoituksen.
    if (merkkijono_.find_first_not_of(' ') == string::npos){
        return false;
    }

    // Lisätään taulukkoon käskyn sanat yksi kerrallaan.
    // >>-operaatio huolehtii, että välilyöntejä ei oteta mukaan.
    istringstream virta(merkkijono_);

    string sana;
    int i = 0;
    while( virta >> sana ) {
        taulukko_[i] = sana;
        ++alkioiden_maara_;
        ++i;

        if ( alkioiden_maara_ == taulukon_koko_ ){
            kasvata_taulukkoa();
        }

    }
    return true;
}



