#ifndef HEADER_H
#define HEADER_H

#define MAX_NAZIV 100
#define MAX_DATUM 11

// Struktura proizvoda
typedef struct Proizvod {
    char naziv[MAX_NAZIV];
    char vrsta[10]; // "slatko" ili "slano"
    char datum[MAX_DATUM]; // "dd.mm.yyyy"
    int proizvedeno;
    int prodano;
    struct Proizvod* sljedeci;
} Proizvod;

// Funkcije
typedef struct {
    Proizvod* pocetak;
} Lista;

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