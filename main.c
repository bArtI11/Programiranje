#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main() {
	Proizvod proizvodi[MAX_PROIZVODA];
	int broj = 0;
	int izbor;
	char datoteka[] = "proizvodi.dat";

	do {
		printf("\n=== IZBORNIK ===\n");
		printf("1. Unos proizvoda\n");
		printf("2. Ispis svih proizvoda\n");
		printf("3. Sortiraj po datumu\n");
		printf("4. Sortiraj po nazivu\n");
		printf("5. Ukupno proizvedeno na dan\n");
		printf("6. Spremi u datoteku\n");
		printf("7. Ucitaj iz datoteke\n");
		printf("0. Izlaz\n");
		printf("Vas izbor: ");
		scanf("%d", &izbor);

		switch (izbor) {
		case 1:
			if (broj < MAX_PROIZVODA) {
				proizvodi[broj++] = unesiProizvod();
			}
			else {
				printf("Dosegnut maksimalan broj proizvoda!\n");
			}
			break;
		case 2:
			ispisiProizvode(proizvodi, broj);
			break;
		case 3:
			qsort(proizvodi, broj, sizeof(Proizvod), usporediPoDatumu);
			ispisiProizvode(proizvodi, broj);
			break;
		case 4:
			qsort(proizvodi, broj, sizeof(Proizvod), usporediPoNazivu);
			ispisiProizvode(proizvodi, broj);
			break;
		case 5: {
			Datum d = unesiDatum();
			int ukupno = ukupnoZaDatum(proizvodi, broj, d);
			printf("Ukupno proizvedeno %02d.%02d.%d: %d\n", d.dan, d.mjesec, d.godina, ukupno);
			break;
		}
		case 6:
			spremiUDatoteku(proizvodi, broj, datoteka);
			break;
		case 7:
			broj = ucitajIzDatoteke(proizvodi, datoteka);
			break;
		case 0:
			printf("Izlaz iz programa.\n");
			break;
		default:
			printf("Nepoznata opcija.\n");
		}
	} while (izbor != 0);

	return 0;
}


