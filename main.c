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
        case 7: sortirajPoNazivu(); break;
        case 8: sortirajPoDatumu(); break;
        case 9: pretraziPoNazivu(); break;
        case 10: filtrirajPoDatumu(); break;
        case 11: statistikaKolicina(); break;
        case 12: prikaziOstatkeNaDan(); break;
        case 13:
            printf("Zelite li spremiti podatke prije izlaska? (1 = DA / 0 = NE): ");
            int potvrda;
            scanf("%d", &potvrda);
            if (potvrda == 1) {
                spremiUDatoteku();
                printf("Podaci su spremljeni.\n");
            }
            printf("Izlaz iz programa.\n");
            break;
        default: printf("Pogresan izbor!\n"); break;
        }
    } while (izbor != 13);

    oslobodiMemoriju();
    return 0;
}

