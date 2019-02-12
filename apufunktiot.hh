// Moduuli apufunktiot / tiedosto: apufunktiot.hh
// Moduulin apufunktiot esittelytiedosto:
// sisältää esittelyn syötteiden käsittelyyn tarvittaville metodeille ja olioille.
// Luokan metodeita kutsutaan tiedoston lukemisen yhteydessä ja käyttöliittymässä.

#ifndef APUFUNKTIOT_HH
#define APUFUNKTIOT_HH
#include <string>



using namespace std;

class Rivin_kasittely {

public:
    Rivin_kasittely(int kenttien_maara);
    ~Rivin_kasittely();

    void aseta_merkkijono(const string& merkkijono);
    bool paloittele_kasky();
    bool poista_valilyonnit();
    bool onko_kommentti_tai_valilyonti();

    string hae_kentta(int indeksi);
    int hae_alkioiden_maara(); 



private:
    void kasvata_taulukkoa();

    // Syöterivi tallennetaan merkkijono-olioon pilkkomista varten.
    string merkkijono_;

    // Pilkotun rivin sanat tallennetaan taulukkoon.
    string* taulukko_;
    int taulukon_koko_;
    int alkioiden_maara_;
};

#endif // APUFUNKTIOT_HH
