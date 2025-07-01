#ifndef PROIZVOD_H
#define PROIZVOD_H

#define MAX_NAZIV 100

typedef struct {
    int dan;
    int mjesec;
    int godina;
} Datum;

typedef enum {
    SLATKO = 1,
    SLANO = 2
} VrstaProizvoda;

typedef struct Proizvod {
    char naziv[MAX_NAZIV];
    VrstaProizvoda vrsta;
    int proizvedeno;
    int prodano;
    Datum datum;
    struct Proizvod* sljedeci;
} Proizvod;

void inicijalizirajListu();
void dodajProizvod();
void ispisiProizvode();
void azurirajProizvod();
void obrisiProizvod();
void spremiUDatoteku();
void ucitajIzDatoteke();
void ucitajNTiProizvod(int n);
void prikaziIzbornik();
void oslobodiMemoriju();

#endif