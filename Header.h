#ifndef HEADER_H
#define HEADER_H

#define MAX_PROIZVODA 10

typedef enum { SLATKO = 1, SLANO } Vrsta;

typedef struct {
	int dan, mjesec, godina; // typedef struct
} Datum;

typedef struct {
	char naziv[50];
	Vrsta vrsta;
	Datum datumProizvodnje;
	int proizvedeno;
	int ostaloZaBacanje;
} Proizvod;

// Funkcije
Proizvod unesiProizvod();
Datum unesiDatum();
int ukupnoZaDatum(Proizvod* niz, int n, Datum datum);
void ispisiProizvode(Proizvod* niz, int n);
int usporediPoDatumu(const void* a, const void* b);
int usporediPoNazivu(const void* a, const void* b);
void spremiUDatoteku(Proizvod* niz, int n, const char* ime);
int ucitajIzDatoteke(Proizvod* niz, const char* ime);

#endif
