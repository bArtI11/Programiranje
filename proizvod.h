#ifndef PROIZVOD_H
#define PROIZVOD_H

#define MAX_NAZIV 100

// Struktura za datum
typedef struct {
    int dan, mjesec, godina;
} Datum;

// Enum za vrstu proizvoda
typedef enum {
    SLATKO = 1,
    SLANO = 2
} VrstaProizvoda;

// Glavna struktura proizvoda (povezana lista)
typedef struct Proizvod {
    char naziv[MAX_NAZIV];
    VrstaProizvoda vrsta;
    int proizvedeno;
    int prodano;
    Datum datum;
    struct Proizvod* sljedeci;
} Proizvod;

// CRUD funkcije
void inicijalizirajListu();
void dodajProizvod();
void ispisiProizvode();
void azurirajProizvod();
void obrisiProizvod();

// Rad s datotekom
void spremiUDatoteku();
void ucitajIzDatoteke();
void backupDatoteke();
void obrisiDatoteku();

// Napredne funkcije
void sortirajPoNazivu();
void sortirajPoDatumu();
void pretraziPoNazivu();
void filtrirajPoDatumu();
void statistikaProizvoda();
void prikaziOstatke();
void ucitajNTiProizvod(int n);
void prikaziPoziciju();
void rewindDatoteke();

// Ostalo
void prikaziIzbornik();
void oslobodiMemoriju();

#endif