#include <stdio.h>
#include "proizvod.h"

int main() {
    int izbor;
    inicijalizirajListu();
    ucitajIzDatoteke();

    do {
        prikaziIzbornik();
        printf("Izbor: "); scanf("%d", &izbor);
        switch (izbor) {
            case 1: dodajProizvod(); break;
            case 2: ispisiProizvode(); break;
            case 3: azurirajProizvod(); break;
            case 4: obrisiProizvod(); break;
            case 5: spremiUDatoteku(); break;
            case 6: ucitajIzDatoteke(); break;
            case 7: backupDatoteke(); break;
            case 8: obrisiDatoteku(); break;
            case 9: {
                int n; printf("Koji zapis? "); scanf("%d", &n);
                ucitajNTiProizvod(n); break;
            }
            case 10: prikaziPoziciju(); break;
            case 11: rewindDatoteke(); break;
            case 12: sortirajPoNazivu(); break;
            case 13:
                printf("Izlaz.\n");
                break;
            default: printf("Pogresan unos.\n"); break;
        }
    } while (izbor != 13);

    oslobodiMemoriju();
    return 0;
}