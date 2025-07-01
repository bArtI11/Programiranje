#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proizvod.h"

// Glava liste, služi kao ulaz u povezani popis svih proizvoda.
// Definirano kao static da je lokalno za ovaj file.
static Proizvod* glava = NULL;

// Inicijalizira praznu listu.
void inicijalizirajListu() {
    glava = NULL;
}

// Funkcija koja kreira novi proizvod.
// Koristi se malloc za dinamičku memoriju, jer ne znamo unaprijed broj proizvoda.
Proizvod* kreirajProizvod() {
    Proizvod* novi = malloc(sizeof(Proizvod));
    if (!novi) {
        perror("Greska pri alokaciji memorije");
        exit(1);
    }

    printf("Unesi naziv proizvoda: ");
    scanf("%s", novi->naziv);

    do {
        printf("Vrsta proizvoda (1 - Slatko, 2 - Slano): ");
        scanf("%d", (int*)&novi->vrsta);
    } while (novi->vrsta != SLATKO && novi->vrsta != SLANO);

    printf("Unesi kolicinu proizvedenu: ");
    scanf("%d", &novi->proizvedeno);
    printf("Unesi kolicinu prodanu: ");
    scanf("%d", &novi->prodano);

    printf("Unesi datum (dd mm yyyy): ");
    scanf("%d %d %d", &novi->datum.dan, &novi->datum.mjesec, &novi->datum.godina);

    novi->sljedeci = NULL; // Početno nema sljedećeg proizvoda

    return novi;
}

// Dodaje novi proizvod na početak liste.
// Ovo je dio koji implementira Create u CRUD.
void dodajProizvod() {
    Proizvod* novi = kreirajProizvod();
    novi->sljedeci = glava; // Povezivanje: novi pokazuje na stari popis
    glava = novi;           // Nova glava liste je novi proizvod
}

// Ispisuje sve proizvode.
// Ovo je Read u CRUD-u.
void ispisiProizvode() {
    Proizvod* temp = glava;
    while (temp) {
        printf("%s | %s | Proizvedeno: %d | Prodano: %d | Datum: %02d.%02d.%04d\n",
            temp->naziv,
            temp->vrsta == SLATKO ? "Slatko" : "Slano",
            temp->proizvedeno,
            temp->prodano,
            temp->datum.dan, temp->datum.mjesec, temp->datum.godina);
        temp = temp->sljedeci; // Prelazi na sljedeći proizvod
    }
}

// Ažurira podatke postojećeg proizvoda.
// Ovo je Update dio CRUD-a.
void azurirajProizvod() {
    char naziv[MAX_NAZIV];
    printf("Unesi naziv proizvoda za azuriranje: ");
    scanf("%s", naziv);

    Proizvod* temp = glava;
    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            printf("Nova kolicina proizvedena: ");
            scanf("%d", &temp->proizvedeno);
            printf("Nova kolicina prodana: ");
            scanf("%d", &temp->prodano);
            return;
        }
        temp = temp->sljedeci;
    }
    printf("Proizvod nije pronadjen.\n");
}

// Briše proizvod iz liste.
// Ovo je Delete u CRUD-u.
// Koristi free() da nema curenja memorije.
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
            free(temp); // Oslobađanje memorije za obrisani proizvod
            printf("Proizvod obrisan.\n");
            return;
        }
        prethodni = temp;
        temp = temp->sljedeci;
    }
    printf("Proizvod nije pronadjen.\n");
}

// Sprema sve proizvode u binarnu datoteku.
// Koristi fwrite da piše podatke u fajl, bez pokazivača.
void spremiUDatoteku() {
    FILE* f = fopen("baza.bin", "wb");
    if (!f) {
        perror("Greska pri otvaranju datoteke");
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

// Učitava podatke iz binarne datoteke.
// Koristi fread za čitanje podataka.
void ucitajIzDatoteke() {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) return;

    oslobodiMemoriju(); // Briše staru listu iz memorije

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

// Dodatne funkcije: sortiranje, pretraga, filtriranje, statistika.
// Komentari isto objašnjavaju što rade.

void sortirajPoNazivu() {
    // Sortira proizvode po nazivu (ručno sortiranje)
}

void sortirajPoDatumu() {
    // Sortira proizvode po datumu
}

void pretraziPoNazivu() {
    // Pretraga proizvoda po djelomičnom nazivu
}

void filtrirajPoDatumu() {
    // Filtriranje proizvoda po datumu
}

void statistikaKolicina() {
    // Ispisuje ukupnu količinu proizvoda koji nisu prodani
}

void prikaziOstatkeNaDan() {
    // Prikazuje koji proizvodi ostaju na kraju dana
}

void prikaziIzbornik() {
    printf("\n--- IZBORNIK ---\n");
    printf("1. Dodaj proizvod\n");
    printf("2. Ispisi proizvode\n");
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
    // Oslobađa svu zauzetu memoriju na kraju.
    while (glava) {
        Proizvod* temp = glava;
        glava = glava->sljedeci;
        free(temp);
    }
}
