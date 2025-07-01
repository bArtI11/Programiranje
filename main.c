#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "proizvod.h"

int main() {
    int izbor;

    inicijalizirajListu();
    ucitajIzDatoteke();

    do {
        prikaziIzbornik();
        printf("Unesi izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
            case 1: dodajProizvod(); break;
            case 2: ispisiProizvode(); break;
            case 3: azurirajProizvod(); break;
            case 4: obrisiProizvod(); break;
            case 5: spremiUDatoteku(); break;
            case 6: ucitajIzDatoteke(); break;
            case 7:
                printf("Redni broj proizvoda: ");
                int n; scanf("%d", &n);
                ucitajNTiProizvod(n);
                break;
            case 8:
                printf("Spremiti prije izlaza? (1=DA/0=NE): ");
                int p; scanf("%d", &p);
                if (p) spremiUDatoteku();
                printf("Izlaz.\n");
                break;
            default: printf("Nepostojeca opcija!\n"); break;
        }

    } while (izbor != 8);

    oslobodiMemoriju();
    return 0;
}