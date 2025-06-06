#include "HEADER.h"

#include <stdio.h>


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
            case 6: sortirajPoNazivu(); break;
            case 7: pretraziPoNazivu(); break;
            case 8: statistikaKolicina(); break;
            case 9: printf("Izlaz iz programa.\n"); break;
            default: printf("Pogresan izbor!\n"); break;
        }

    } while (izbor != 9);

    oslobodiMemoriju();
    return 0;
}