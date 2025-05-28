#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAZIV 50

typedef enum { SLATKO = 1, SLANO } Vrsta;

typedef struct {
    int dan, mjesec, godina;
} Datum;

typedef struct {
    char naziv[MAX_NAZIV];
    Vrsta vrsta;
    int kolicina;
    float cijena;
    Datum datumProizvodnje;
} Proizvod;

void dodajProizvod(Proizvod **proizvodi, int *brojProizvoda);
void ispisiProizvode(Proizvod *proizvodi, int brojProizvoda);
void spremiUDatoteku(Proizvod *proizvodi, int brojProizvoda);
void ucitajIzDatoteke(Proizvod **proizvodi, int *brojProizvoda);
void obrisiProizvod(Proizvod *proizvodi, int *brojProizvoda);
void azurirajProizvod(Proizvod *proizvodi, int brojProizvoda);
void sortirajPoNazivu(Proizvod *proizvodi, int brojProizvoda);
void sortirajPoDatumu(Proizvod *proizvodi, int brojProizvoda);

#endif
