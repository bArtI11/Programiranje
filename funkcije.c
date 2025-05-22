#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

Proizvod unesiProizvod() {
	Proizvod p;

	printf("Unesite naziv proizvoda: ");
	scanf(" %[^\n]", p.naziv);

	do {
		printf("Vrsta (1 - Slatko, 2 - Slano): ");
		scanf("%d", (int*)&p.vrsta);
	} while (p.vrsta != SLATKO && p.vrsta != SLANO);

	printf("Unesite datum proizvodnje (dan mjesec godina): ");
	scanf("%d %d %d", &p.datumProizvodnje.dan, &p.datumProizvodnje.mjesec, &p.datumProizvodnje.godina);

	printf("Kolicina proizvedena: ");
	scanf("%d", &p.proizvedeno);

	printf("Kolicina ostala za bacanje: ");
	scanf("%d", &p.ostaloZaBacanje);

	return p;
}

Datum unesiDatum() {
	Datum d;
	printf("\nUnesite datum za provjeru (dan.mjesec.godina): ");
	scanf("%d %d %d", &d.dan, &d.mjesec, &d.godina);
	return d;
}

int ukupnoZaDatum(Proizvod* niz, int n, Datum datum) {
	int suma = 0;
	for (int i = 0; i < n; i++) {
		if (niz[i].datumProizvodnje.dan == datum.dan &&
			niz[i].datumProizvodnje.mjesec == datum.mjesec &&
			niz[i].datumProizvodnje.godina == datum.godina) {
			suma += niz[i].proizvedeno;
		}
	}
	return suma;
}

void ispisiProizvode(Proizvod* niz, int n) {
	for (int i = 0; i < n; i++) {
		printf("%s | %s | %02d.%02d.%d | Proizvedeno: %d | Ostalo: %d\n",
			niz[i].naziv,
			niz[i].vrsta == SLATKO ? "Slatko" : "Slano",
			niz[i].datumProizvodnje.dan,
			niz[i].datumProizvodnje.mjesec,
			niz[i].datumProizvodnje.godina,
			niz[i].proizvedeno,
			niz[i].ostaloZaBacanje);
	}
}

int usporediPoDatumu(const void* a, const void* b) {
	const Proizvod* p1 = (const Proizvod*)a;
	const Proizvod* p2 = (const Proizvod*)b;

	if (p1->datumProizvodnje.godina != p2->datumProizvodnje.godina)
		return p1->datumProizvodnje.godina - p2->datumProizvodnje.godina;
	if (p1->datumProizvodnje.mjesec != p2->datumProizvodnje.mjesec)
		return p1->datumProizvodnje.mjesec - p2->datumProizvodnje.mjesec;
	return p1->datumProizvodnje.dan - p2->datumProizvodnje.dan;
}

int usporediPoNazivu(const void* a, const void* b) {
	const Proizvod* p1 = (const Proizvod*)a;
	const Proizvod* p2 = (const Proizvod*)b;
	return strcmp(p1->naziv, p2->naziv);
}

void spremiUDatoteku(Proizvod* niz, int n, const char* ime) {
	FILE* f = fopen(ime, "wb");
	if (!f)
	{
		printf("Greska pri otvaranju datotek!\n");
		return;
	}
	fwrite(&n, sizeof(int), 1, f); // spremi broj u elemenata
	fwrite(niz, sizeof(Proizvod), n, f);
	fclose(f);
	printf("Podaci uspjesno spremljeni u '%s'. \n", ime);
}

int ucitajIzDatoteke(Proizvod* niz, const char* ime) {
	FILE* f = fopen(ime, "rb");
	if (!f)
	{
		printf("Datoteka '%s' ne postoji.\n", ime);
		return 0;
	}
	int n;
	fread(&n, sizeof(int), 1, f); //broj proizvoda
	fread(niz, sizeof(Proizvod), n, f);
	fclose(f);
	printf("Ucitano %d proizvoda iz '%s'.\n", n, ime);
	return n;
}
