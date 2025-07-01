#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proizvod.h"

static Proizvod* glava = NULL;

void inicijalizirajListu() {
    glava = NULL;
}

Proizvod* kreirajProizvod() {
    Proizvod* novi = malloc(sizeof(Proizvod));
    if (!novi) {
        perror("Greska pri alokaciji");
        exit(1);
    }

    printf("Naziv: ");
    scanf("%s", novi->naziv);

    do {
        printf("Vrsta (1 - Slatko, 2 - Slano): ");
        scanf("%d", (int*)&novi->vrsta);
    } while (novi->vrsta != SLATKO && novi->vrsta != SLANO);

    printf("Proizvedeno: ");
    scanf("%d", &novi->proizvedeno);
    printf("Prodano: ");
    scanf("%d", &novi->prodano);

    printf("Datum (dd mm yyyy): ");
    scanf("%d %d %d", &novi->datum.dan, &novi->datum.mjesec, &novi->datum.godina);

    novi->sljedeci = NULL;
    return novi;
}

void dodajProizvod() {
    Proizvod* novi = kreirajProizvod();
    novi->sljedeci = glava;
    glava = novi;
}

void ispisiProizvode() {
    Proizvod* temp = glava;
    while (temp) {
        printf("%s | %s | Proizvedeno: %d | Prodano: %d | Datum: %02d.%02d.%04d\n",
               temp->naziv,
               temp->vrsta == SLATKO ? "Slatko" : "Slano",
               temp->proizvedeno, temp->prodano,
               temp->datum.dan, temp->datum.mjesec, temp->datum.godina);
        temp = temp->sljedeci;
    }
}

void azurirajProizvod() {
    char naziv[MAX_NAZIV];
    printf("Naziv za azuriranje: ");
    scanf("%s", naziv);

    Proizvod* temp = glava;
    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            printf("Nova proizvedena: ");
            scanf("%d", &temp->proizvedeno);
            printf("Nova prodana: ");
            scanf("%d", &temp->prodano);
            return;
        }
        temp = temp->sljedeci;
    }
    printf("Nema proizvoda s tim nazivom.\n");
}

void obrisiProizvod() {
    char naziv[MAX_NAZIV];
    printf("Naziv za brisanje: ");
    scanf("%s", naziv);

    Proizvod *temp = glava, *prethodni = NULL;

    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            if (prethodni) {
                prethodni->sljedeci = temp->sljedeci;
            } else {
                glava = temp->sljedeci;
            }
            free(temp);
            printf("Proizvod obrisan.\n");
            return;
        }
        prethodni = temp;
        temp = temp->sljedeci;
    }
    printf("Nema proizvoda s tim nazivom.\n");
}

void spremiUDatoteku() {
    FILE* f = fopen("baza.bin", "wb");
    if (!f) {
        perror("Greska pri spremanju");
        return;
    }

    Proizvod* temp = glava;
    while (temp) {
        fwrite(temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f);
        temp = temp->sljedeci;
    }

    fclose(f);
    printf("Podaci spremljeni.\n");
}

void ucitajIzDatoteke() {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) return;

    oslobodiMemoriju();

    Proizvod temp;
    while (fread(&temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f)) {
        Proizvod* novi = malloc(sizeof(Proizvod));
        *novi = temp;
        novi->sljedeci = glava;
        glava = novi;
    }
    fclose(f);
    printf("Podaci ucitani.\n");
}

// Primjer funkcije koja koristi fseek za slučajno čitanje n-tog proizvoda
void ucitajNTiProizvod(int n) {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) {
        perror("Greska pri otvaranju");
        return;
    }

    long pomak = (n - 1) * (sizeof(Proizvod) - sizeof(Proizvod*));
    if (fseek(f, pomak, SEEK_SET) != 0) {
        perror("Greska pri fseek");
        fclose(f);
        return;
    }

    Proizvod temp;
    if (fread(&temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f) == 1) {
        printf("Proizvod %d:\n", n);
        printf("Naziv: %s\n", temp.naziv);
        printf("Vrsta: %s\n", temp.vrsta == SLATKO ? "Slatko" : "Slano");
        printf("Proizvedeno: %d, Prodano: %d\n", temp.proizvedeno, temp.prodano);
        printf("Datum: %02d.%02d.%04d\n",
               temp.datum.dan, temp.datum.mjesec, temp.datum.godina);
    } else {
        printf("Ne postoji zapis s tim rednim brojem.\n");
    }

    fclose(f);
}

void prikaziIzbornik() {
    printf("\n--- IZBORNIK ---\n");
    printf("1. Dodaj proizvod\n");
    printf("2. Ispisi proizvode\n");
    printf("3. Azuriraj proizvod\n");
    printf("4. Obrisi proizvod\n");
    printf("5. Spremi u datoteku\n");
    printf("6. Ucitaj iz datoteke\n");
    printf("7. Ucitaj N-ti proizvod (fseek primjer)\n");
    printf("8. Izlaz\n");
}

void oslobodiMemoriju() {
    while (glava) {
        Proizvod* temp = glava;
        glava = glava->sljedeci;
        free(temp);
    }
}