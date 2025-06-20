#define _CRT_SECURE_NO_WARNINGS

#ifndef PROIZVOD_H
#define PROIZVOD_H

#define MAX_NAZIV 100
#define MAX_DATUM 11

// Struktura za pohranu datuma
typedef struct {
    int dan;
    int mjesec;
    int godina;
} Datum;

// Enum za vrstu proizvoda
typedef enum {
    SLATKO = 1,
    SLANO = 2
} VrstaProizvoda;

// Struktura proizvoda
typedef struct Proizvod {
    char naziv[MAX_NAZIV];
    VrstaProizvoda vrsta;
    int proizvedeno;
    int prodano;
    Datum datum;
    struct Proizvod* sljedeci;
} Proizvod;

// Funkcije
void inicijalizirajListu();
void dodajProizvod();
void ispisiProizvode();
void azurirajProizvod();
void obrisiProizvod();
void spremiUDatoteku();
void ucitajIzDatoteke();
void sortirajPoNazivu();
void sortirajPoDatumu();
void pretraziPoNazivu();
void filtrirajPoDatumu();
void statistikaKolicina();
void prikaziIzbornik();
void oslobodiMemoriju();
void prikaziOstatkeNaDan();

#endif
