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
    Proizvod* novi = (Proizvod*)malloc(sizeof(Proizvod));
    if (!novi) {
        perror("Greska pri alokaciji memorije");
        exit(1);
    }

    printf("Unesi naziv proizvoda: ");
    scanf("%s", novi->naziv);

    do {
        printf("Vrsta (1 - Slatko, 2 - Slano): ");
        scanf("%d", (int*)&novi->vrsta);
    } while (novi->vrsta != SLATKO && novi->vrsta != SLANO);

    printf("Unesi kolicinu proizvedenu: ");
    scanf("%d", &novi->proizvedeno);
    printf("Unesi kolicinu prodanu: ");
    scanf("%d", &novi->prodano);
    printf("Unesi datum (dd mm yyyy): ");
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
            temp->proizvedeno,
            temp->prodano,
            temp->datum.dan, temp->datum.mjesec, temp->datum.godina);
        temp = temp->sljedeci;
    }
}

void azurirajProizvod() {
    char naziv[MAX_NAZIV];
    printf("Unesi naziv proizvoda za azuriranje: ");
    scanf("%s", naziv);
    Proizvod* temp = glava;
    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            printf("Unesi novu kolicinu proizvedenu: ");
            scanf("%d", &temp->proizvedeno);
            printf("Unesi novu kolicinu prodanu: ");
            scanf("%d", &temp->prodano);
            return;
        }
        temp = temp->sljedeci;
    }
    printf("Proizvod nije pronadjen.\n");
}

void obrisiProizvod() {
    char naziv[MAX_NAZIV];
    printf("Unesi naziv proizvoda za brisanje: ");
    scanf("%s", naziv);
    Proizvod* temp = glava, * prethodni = NULL;

    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            if (prethodni) {
                prethodni->sljedeci = temp->sljedeci;
            }
            else {
                glava = temp->sljedeci;
            }
            free(temp);
            printf("Proizvod obrisan.\n");
            return;
        }
        prethodni = temp;
        temp = temp->sljedeci;
    }
    printf("Proizvod nije pronadjen.\n");
}

void spremiUDatoteku() {
    FILE* f = fopen("baza.bin", "wb");
    if (!f) {
        perror("Ne mogu otvoriti datoteku");
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
        Proizvod* novi = (Proizvod*)malloc(sizeof(Proizvod));
        *novi = temp;
        novi->sljedeci = glava;
        glava = novi;
    }
    fclose(f);
}

int usporediDatume(Datum d1, Datum d2) {
    if (d1.godina != d2.godina)
        return d1.godina - d2.godina;
    if (d1.mjesec != d2.mjesec)
        return d1.mjesec - d2.mjesec;
    return d1.dan - d2.dan;
}

void sortirajPoNazivu() {
    if (!glava || !glava->sljedeci) return;
    for (Proizvod* i = glava; i; i = i->sljedeci) {
        for (Proizvod* j = i->sljedeci; j; j = j->sljedeci) {
            if (strcmp(i->naziv, j->naziv) > 0) {
                Proizvod temp = *i;
                *i = *j;
                *j = temp;
                Proizvod* swap = i->sljedeci;
                i->sljedeci = j->sljedeci;
                j->sljedeci = swap;
            }
        }
    }
}

void sortirajPoDatumu() {
    if (!glava || !glava->sljedeci) return;
    for (Proizvod* i = glava; i; i = i->sljedeci) {
        for (Proizvod* j = i->sljedeci; j; j = j->sljedeci) {
            if (usporediDatume(i->datum, j->datum) > 0) {
                Proizvod temp = *i;
                *i = *j;
                *j = temp;
                Proizvod* swap = i->sljedeci;
                i->sljedeci = j->sljedeci;
                j->sljedeci = swap;
            }
        }
    }
}

void pretraziPoNazivu() {
    char trazeni[MAX_NAZIV];
    printf("Unesi naziv za pretragu: ");
    scanf("%s", trazeni);
    Proizvod* temp = glava;
    while (temp) {
        if (strstr(temp->naziv, trazeni)) {
            printf("%s | %s | %d/%d | %02d.%02d.%d\n", temp->naziv,
                temp->vrsta == SLATKO ? "Slatko" : "Slano",
                temp->proizvedeno,
                temp->prodano,
                temp->datum.dan,
                temp->datum.mjesec,
                temp->datum.godina);
        }
        temp = temp->sljedeci;
    }
}

void filtrirajPoDatumu() {
    Datum d;
    printf("Unesi datum (dd mm yyyy): ");
    scanf("%d %d %d", &d.dan, &d.mjesec, &d.godina);
    Proizvod* temp = glava;
    while (temp) {
        if (usporediDatume(temp->datum, d) == 0) {
            printf("%s | %s | %d/%d\n", temp->naziv,
                temp->vrsta == SLATKO ? "Slatko" : "Slano",
                temp->proizvedeno, temp->prodano);
        }
        temp = temp->sljedeci;
    }
}

void statistikaKolicina() {
    int ukupno = 0;
    Proizvod* temp = glava;
    while (temp) {
        ukupno += temp->proizvedeno - temp->prodano;
        temp = temp->sljedeci;
    }
    printf("Ukupna preostala kolicina: %d\n", ukupno);
}

void prikaziOstatkeNaDan() {
    Datum d;
    printf("Unesi datum (dd mm yyyy): ");
    scanf("%d %d %d", &d.dan, &d.mjesec, &d.godina);
    Proizvod* temp = glava;
    while (temp) {
        if (usporediDatume(temp->datum, d) == 0 && temp->proizvedeno > temp->prodano) {
            printf("%s | Ostalo: %d\n", temp->naziv, temp->proizvedeno - temp->prodano);
        }
        temp = temp->sljedeci;
    }
}

void prikaziIzbornik() {
    printf("\n--- IZBORNIK ---\n");
    printf("1. Dodaj proizvod\n");
    printf("2. Ispisi sve proizvode\n");
    printf("3. Azuriraj proizvod\n");
    printf("4. Obrisi proizvod\n");
    printf("5. Spremi u datoteku\n");
    printf("6. Ucitaj iz datoteke\n");
    printf("7. Sortiraj po nazivu\n");
    printf("8. Sortiraj po datumu\n");
    printf("9. Pretrazi po nazivu\n");
    printf("10. Filtriraj po datumu\n");
    printf("11. Statistika kolicina\n");
    printf("12. Ostatci na kraju dana\n");
    printf("13. Izlaz\n");
}

void oslobodiMemoriju() {
    while (glava) {
        Proizvod* temp = glava;
        glava = glava->sljedeci;
        free(temp);
    }
}
