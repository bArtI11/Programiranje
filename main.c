#include "HEADER.h"

int main() {
    Proizvod *proizvodi = NULL;
    int brojProizvoda = 0;
    int izbor;

    ucitajIzDatoteke(&proizvodi, &brojProizvoda);

    do {
        printf("\n1. Dodaj\n2. Ispisi\n3. Spremi\n4. Obrisi\n5. Azuriraj\n6. Sortiraj po nazivu\n7. Sortiraj po datumu\n0. Izlaz\nIzbor: ");
        scanf("%d", &izbor);
        switch (izbor) {
            case 1: dodajProizvod(&proizvodi, &brojProizvoda); break;
            case 2: ispisiProizvode(proizvodi, brojProizvoda); break;
            case 3: spremiUDatoteku(proizvodi, brojProizvoda); break;
            case 4: obrisiProizvod(proizvodi, &brojProizvoda); break;
            case 5: azurirajProizvod(proizvodi, brojProizvoda); break;
            case 6: sortirajPoNazivu(proizvodi, brojProizvoda); break;
            case 7: sortirajPoDatumu(proizvodi, brojProizvoda); break;
        }
    } while (izbor != 0);

    free(proizvodi);
    return 0;
}
