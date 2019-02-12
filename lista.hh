

// Moduuli: lista / tiedosto: lista.hh
// Moduulin lista esittelytiedosto:
// sisältää esittelyn tuotantoketjujen ja repun sisällön käsittelyyn
// tarvittaville metodeille. Moduulin metodeita kutsutaan sekä
// käyttölittymässä että toisissa metodeissa.

#ifndef LISTA_HH
#define LISTA_HH
#include <string>

using namespace std;

class Lista {
public:
    Lista();
    ~Lista();
    bool lisaa_tietorakenteeseen(string esine, string materiaali);

    bool lisaa_reppuun(string esine);
    bool loytyy_repusta(string esine);
    void tulosta_repun_sisalto();
    void tyhjenna_reppu();


    bool askarreltavissa(string esine);
    bool askarreltavissa_bonus(string esine);
    bool etsi_tuotantoketjusta(string esine);
    bool tulosta_materiaalit(string esine);



private:
    bool kay_lapi_tuotantoketju(string esine);
    void kasvata_taulukkoa();
    void aakkosvertailija();
    bool ketjun_ensimmainen(string esine);


    // Reppu sisältää tavaran ja osoiteen seuraavaan tavaraa.
    struct Reppu {
        string tavara_;
        Reppu *seuraavan_osoite_;
    };

    Reppu *repun_ensimmainen_osoite_;
    Reppu *repun_viimeinen_osoite_;

    // Tuotantoketju sisältää esineen, sen askarteluun tarvittavan materiaalin
    // ja osoitteen seuraavaan esine-materiaali-pariin.
    struct Tuotantoketju {
        string esine_;
        string materiaali_;
        Tuotantoketju *seuraavan_osoite_;
    };

    Tuotantoketju *ketjun_ensimmainen_osoite_;
    Tuotantoketju *ketjun_viimeinen_osoite_;

    // Materiaalitaulukkoon lisätään materiaalit-käskyssä kysytyn
    // esineen askarteluun tarvittavat materiaalit aakkosjärjestyksessä
    // printtaamista varten.
    string* materiaalitaulukko_;
    int materiaalitaulukon_koko_;
    int alkioiden_maara_;

};

#endif // LISTA_HH
