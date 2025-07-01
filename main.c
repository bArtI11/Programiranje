#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "proizvod.h"

// Glavna funkcija programa.
// Povezuje sve CRUD operacije i dodatne opcije kroz izbornik.
int main() {
    int izbor;

    inicijalizirajListu();
    ucitajIzDatoteke(); // Na početku odmah učitaj podatke ako postoje

    do {
        prikaziIzbornik();
        printf("Unesi izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1: dodajProizvod(); break;   // Create
        case 2: ispisiProizvode(); break; // Read
        case 3: azurirajProizvod(); break;// Update
        case 4: obrisiProizvod(); break;  // Delete
        case 5: spremiUDatoteku(); break; // Spremanje
        case 6: ucitajIzDatoteke(); break;// Učitavanje
        case 7: sortirajPoNazivu(); break;
        case 8: sortirajPoDatumu(); break;
        case 9: pretraziPoNazivu(); break;
        case 10: filtrirajPoDatumu(); break;
        case 11: statistikaKolicina(); break;
        case 12: prikaziOstatkeNaDan(); break;
        case 13:
            printf("Zelite li spremiti prije izlaska? (1 = DA / 0 = NE): ");
            int potvrda; scanf("%d", &potvrda);
            if (potvrda) spremiUDatoteku();
            printf("Izlaz iz programa.\n");
            break;
        default: printf("Pogresan izbor!\n"); break;
        }

    } while (izbor != 13);

    oslobodiMemoriju(); // Oslobađa svu memoriju prije izlaska
    return 0;
}
