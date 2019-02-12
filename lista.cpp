// Moduuli: lista / tiedosto: lista.cpp
// Sisältää yksityisen rajapinnan tuotantoketjujen ja repun käsittelyyn.

#include "lista.hh"
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

// Alustetaan luokka.
Lista::Lista():
    repun_ensimmainen_osoite_{nullptr},
    repun_viimeinen_osoite_{nullptr},
    ketjun_ensimmainen_osoite_{nullptr},
    ketjun_viimeinen_osoite_{nullptr},
    materiaalitaulukko_{new string[10]},
    materiaalitaulukon_koko_{10},
    alkioiden_maara_{0} {
}


// Purkaja
Lista::~Lista(){
    Tuotantoketju *listan_vapautettavan_osoite;

    while (ketjun_ensimmainen_osoite_ != nullptr) {
        listan_vapautettavan_osoite = ketjun_ensimmainen_osoite_;
        ketjun_ensimmainen_osoite_
                =ketjun_ensimmainen_osoite_->seuraavan_osoite_;

        delete listan_vapautettavan_osoite;
    }

    Reppu *repun_vapautettavan_osoite;

    while( repun_ensimmainen_osoite_ != nullptr ) {
        repun_vapautettavan_osoite = repun_ensimmainen_osoite_;
        repun_ensimmainen_osoite_
                = repun_ensimmainen_osoite_->seuraavan_osoite_;

        delete repun_vapautettavan_osoite;
    }

    delete [] materiaalitaulukko_;
}


// Lisätään esine-materiaali-pari tietorakenteeseen.
bool Lista::lisaa_tietorakenteeseen( string esine, string materiaali ) {

    Tuotantoketju *osoite{ketjun_ensimmainen_osoite_};

    // Jos esine-materiaali-pari on tiedostossa useammin kuin kerran,
    // tiedosto on virheelline ja ohjelman suoritus lopetetaan.
    while( osoite != nullptr ) {
        if ( esine == osoite->esine_ and materiaali == osoite->materiaali_){
            return false;
        }
        osoite = osoite->seuraavan_osoite_;
    }

    Tuotantoketju *uuden_osoite = new Tuotantoketju{esine, materiaali, nullptr};

    // Jos ketjuun lisätään ensimmäistä kertaa, ensimmäinen ja viimeinen osoite
    // asetetaan uuteen osoitteeseen. Seuraavilla kerroilla uusi osoite laitetaan
    // ketjun viimeiseksi.
    if (ketjun_ensimmainen_osoite_ == nullptr ) {
        ketjun_ensimmainen_osoite_ = uuden_osoite;
        ketjun_viimeinen_osoite_ = uuden_osoite;
    } else {

        ketjun_viimeinen_osoite_->seuraavan_osoite_ = uuden_osoite;
        ketjun_viimeinen_osoite_ = uuden_osoite;
    }
    return true;
}


// Lisätään tavara reppuun.
bool Lista::lisaa_reppuun( string esine ) {

    Reppu *uuden_osoite = new Reppu{esine, nullptr};

    // Jos ketjuun lisätään ensimmäistä kertaa, ensimmäinen ja viimeinen osoite
    // asetetaan uuteen osoitteeseen. Seuraavilla kerroilla uusi osoite laitetaan
    // ketjun viimeiseksi.
    if ( repun_ensimmainen_osoite_ == nullptr ) {
        repun_ensimmainen_osoite_ = uuden_osoite;
        repun_viimeinen_osoite_ = uuden_osoite;
    } else {
        repun_viimeinen_osoite_->seuraavan_osoite_ = uuden_osoite;
        repun_viimeinen_osoite_ = uuden_osoite;
    }

    return true;
}


// Etsitään löytyykö haluttu esine repusta.
// Jos löytyy, palautetaan true. Muussa tapauksessa
// palautetaan false.
bool Lista::loytyy_repusta(string esine) {
    Reppu *osoite{ repun_ensimmainen_osoite_ };

    while ( osoite != nullptr ) {
        if ( esine == osoite->tavara_) {
            return true;
        }

        osoite = osoite->seuraavan_osoite_;
    }

    return false;
}


// Tulostetaan repun sisältö järjestyksessä, jossa esineet on sinne
// lisätty. Jos reppu on tyhjä, ei tulosteta mitään.
void Lista::tulosta_repun_sisalto() {
    Reppu *tulostettavan_osoite{ repun_ensimmainen_osoite_ };

    while( tulostettavan_osoite != nullptr ) {
        cout << tulostettavan_osoite->tavara_ << endl;
        tulostettavan_osoite = tulostettavan_osoite->seuraavan_osoite_;
    }
}


// Tyhjennetään reppu.
void Lista::tyhjenna_reppu() {

    Reppu *repun_vapautettavan_osoite;

    // Osoitteiden vapauttaminen alkaa ketjun etupäästä ja
    // vapauttaa osoitteen kerrallaan, kunnes jono on tyhjä.

    while( repun_ensimmainen_osoite_ != nullptr ) {
        repun_vapautettavan_osoite = repun_ensimmainen_osoite_;
        repun_ensimmainen_osoite_
                = repun_ensimmainen_osoite_->seuraavan_osoite_;

        delete repun_vapautettavan_osoite;
    }
}


// Tutkitaan onko esine askarreltavissa repun materiaaleista.
bool Lista::askarreltavissa(string askarreltava) {
    Tuotantoketju *osoite{ ketjun_ensimmainen_osoite_ };

    while ( osoite != nullptr ) {

        // Jos askarreltava esine on jo valmiiksi repussa
        // palautetaan true.
        if ( osoite->esine_ == askarreltava ) {
            if ( loytyy_repusta(askarreltava) ){
                return true;

            // Jos esineen askartelemiseen tarvittava materiaali ei
            // löydy repusta, palautetaan false.
            } else if ( not loytyy_repusta(osoite->materiaali_) ) {
                return false;
            }

        // Siltä varalta, että askarreltava esine on tiedostossa vain materiaalina,
        // täytyy myös materiaalikentät tarkistaa.
        } else if ( osoite->materiaali_ == askarreltava){
            if( loytyy_repusta(askarreltava) ){
                return true;
            }
        }

       osoite = osoite->seuraavan_osoite_;
    }

    return true;
}


// Askarreltavissa_bonus metodi tutkii, onko
// esine valmistettavissa repun materiaaleista,
// vaikkeivat esineen edeltäjät tuotantoketjussa olisikaan
// repussa.
bool Lista::askarreltavissa_bonus(string esine ) {

    if ( askarreltavissa(esine) ) {
        return true;
    }


    if( not kay_lapi_tuotantoketju(esine) ) {
        return false;
    }

    return true;

}

// Metodi käy tuotantoketjua läpi rekursiivisesti.
bool Lista::kay_lapi_tuotantoketju(string esine){
    bool askarreltavissa = true;

    Tuotantoketju *osoite{ketjun_ensimmainen_osoite_};

    // Jos esine löytyy repusta, askarreltava esine on mahdollista
    // askarrella.
    if ( loytyy_repusta(esine) ) {
        askarreltavissa = true;
    }

    // Jos esine ei löydy repusta ja esine on tuotantoketjunsa
    // alkupää, askarreltavaa esinettä ei voi askarrella.
    // Koska askarreltava asetetaan falseksi metodin rekursiivinen
    // rakenne alkaa purkautua jättäen arvokseen falsen.
    if( not loytyy_repusta(esine) and ketjun_ensimmainen(esine) ) {
        askarreltavissa = false;
    }

    // Tuotantoketju käydään läpi ja, jos askarreltava esine
    // ei löydy repusta, mutta se ei myöskään ole tuotantoketjun
    // alkupää, kutsutaan metodia uudestaan parametrinä esinettä tuotantoketjussa
    // edeltävä esine.
    while( osoite != nullptr and askarreltavissa == true ) {

        if (osoite->esine_ == esine) {

            if( not loytyy_repusta(esine) and not ketjun_ensimmainen(esine)) {
                askarreltavissa = kay_lapi_tuotantoketju(osoite->materiaali_);
            }

        }

        osoite = osoite->seuraavan_osoite_;

    }

    return askarreltavissa;

}

// Tutkitaan löytyykö esine tuotantoketjusta.
bool Lista::etsi_tuotantoketjusta(string esine) {
    Tuotantoketju* osoite{ketjun_ensimmainen_osoite_};

    while( osoite != nullptr ) {
        if(osoite->esine_ == esine or osoite->materiaali_ == esine ){
            return true;
        }
        osoite = osoite->seuraavan_osoite_;
    }
    return false;
}


// Tulostetaan käyttäjän syöttämän esineen valmistamiseen tarvittavat
// materiaalit aakkosjärjestyksessä.
bool Lista::tulosta_materiaalit(string esine) {
    Tuotantoketju *osoite{ ketjun_ensimmainen_osoite_ };

    // Jos haluttua esinettä ei löydy tuotantoketjusta,
    // palautetaan false ja käyttöliittymässä nostetaan
    // virheilmoitus.
    if ( not etsi_tuotantoketjusta(esine) ) {
        return false;
    }
    // Jos esine on ketjun ensimmäinen, sitä ei voida valmistaa
    // toisista materiaaleista. Käyttöliittymään palautetaan true
    // ja jatketaan ohjelman suorittamista.
    if ( ketjun_ensimmainen(esine) ) {
        return true;
    }

    // Lisätään kaikki halutun esineen askarteluun tarvittavat materiaalit
    // taulukkoon aakkosjärjestämistä varten.
    while ( osoite != nullptr ) {
        if (osoite->esine_ == esine){

            materiaalitaulukko_[alkioiden_maara_] = osoite->materiaali_;
            ++alkioiden_maara_;

            if ( alkioiden_maara_ == materiaalitaulukon_koko_ ){
                kasvata_taulukkoa();
            }
        }

        osoite = osoite->seuraavan_osoite_;
    }

        // Funktio palauttaa taulukon aakkosjärjestykseen
        // järjestettynä.
        aakkosvertailija();

        // Tulostetaan taulukko.
        int i;
        for ( i = alkioiden_maara_ -1 ;  i >= 0 ; --i){
            cout << materiaalitaulukko_[i] << endl;
        }

        alkioiden_maara_ = 0;

    return true;
}


// Tutkitaan, onko esine tuotantoketjunsa ensimmäinen esine.
bool Lista::ketjun_ensimmainen(string esine){
    Tuotantoketju *osoite{ketjun_ensimmainen_osoite_};

    // Jos esineen pystyy tuottamaan materiaalista,
    // se ei ole ketjunsa ensimmäinen ja palautetaan false.
    while( osoite != nullptr ){
        if ( osoite->esine_ == esine) {
            return false;
        }
        osoite = osoite->seuraavan_osoite_;
    }
    return true;
}


// Jos taulukko on täynnä, sen koko tuplataan.
// Ensin luodaan uusi taulukko, jonka koko on kaksinkertainen
// entiseen verrattuna. Sitten taulukon alkiot kopioidaan uuteen
// taulukkoon ja uusi taulukko kopioidaan vanhaan taulukkoon.
void Lista::kasvata_taulukkoa() {
    string *uusi_taulukko = new string[2 * materiaalitaulukon_koko_];
    for (int i = 0 ; i < materiaalitaulukon_koko_ ; ++i){
        uusi_taulukko[i] = materiaalitaulukko_[i];
    }

    delete [] materiaalitaulukko_;

    materiaalitaulukko_ = uusi_taulukko;
    materiaalitaulukon_koko_ = 2 * materiaalitaulukon_koko_;
}


// Järjestetään taulukon alkiot aakkosjärjestykseen.
void Lista::aakkosvertailija() {


    int i;
    int j;
    int ensimmainen;
    string valiaikainen;

    // Luupissa etsitään aina pienin alkio ja laitetaan se taulukon alkuun.
     for ( i = alkioiden_maara_ -1 ; i > 0 ; i-- ) {
          ensimmainen = 0;

          // Jos tutkittava alkio on pienempi vaihdetaan se ensimmäiseksi alkioksi.
          // Näin jatketaan kunnes taulukko on käyty läpi.
          for ( j = 1 ; j <= i ; ++j) {   // locate smallest between positions 1 and i.
                if (materiaalitaulukko_[j] < materiaalitaulukko_[ensimmainen]) {
                    ensimmainen = j;
                }
         }

        // Jotta alkiot eivät katoaisi taulukosta, täytyy pienimmän alkion ja taulukon
        // ja vaihtaa paikkaa taulukon i:nnen alkion kanssa.
        valiaikainen = materiaalitaulukko_[ensimmainen];
        materiaalitaulukko_[ensimmainen] = materiaalitaulukko_[i];
        materiaalitaulukko_[i] = valiaikainen;
    }
    return;

}
