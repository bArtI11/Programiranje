#ifndef PROIZVOD_H
#define PROIZVOD_H

#define MAX_NAZIV 100 // Konstanta za maksimalnu duljinu naziva proizvoda

// Struktura koja čuva datum (dan, mjesec, godina)
typedef struct {
    int dan;
    int mjesec;
    int godina;
} Datum;

// Enum za vrstu proizvoda (npr. slatko ili slano)
typedef enum {
    SLATKO = 1,
    SLANO = 2
} VrstaProizvoda;

// Glavna struktura proizvoda.
// Svaki proizvod je jedan zapis u povezanoj listi.
// Polje 'sljedeci' povezuje sve proizvode u lanac.
typedef struct Proizvod {
    char naziv[MAX_NAZIV];
    VrstaProizvoda vrsta;
    int proizvedeno;
    int prodano;
    Datum datum;
    struct Proizvod* sljedeci; // Pokazivač na sljedeći proizvod
} Proizvod;

// Deklaracije svih funkcija iz funkcije.c
void inicijalizirajListu();
void dodajProizvod();       // Dodavanje novog proizvoda (Create)
void ispisiProizvode();     // Ispis proizvoda (Read)
void azurirajProizvod();    // Ažuriranje proizvoda (Update)
void obrisiProizvod();      // Brisanje proizvoda (Delete)
void spremiUDatoteku();     // Spremanje podataka u binarnu datoteku
void ucitajIzDatoteke();    // Učitavanje podataka iz datoteke
void sortirajPoNazivu();    // Sortiranje po nazivu
void sortirajPoDatumu();    // Sortiranje po datumu
void pretraziPoNazivu();    // Pretraga po djelomičnom nazivu
void filtrirajPoDatumu();   // Filtriranje po datumu
void statistikaKolicina();  // Statistika količine proizvoda
void prikaziOstatkeNaDan(); // Ostatci proizvoda na kraju dana
void prikaziIzbornik();     // Prikaz izbornika
void oslobodiMemoriju();    // Oslobađanje zauzete memorije

#endif
