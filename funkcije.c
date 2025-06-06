#include "HEADER.H"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Proizvod lista[MAX];
int brojProizvoda = 0;

void inicijalizirajListu() {
    brojProizvoda = 0;
}

void ucitajIzDatoteke() {
    FILE *fp = fopen("baza.txt", "r");
    if (fp == NULL) return;

    while (fscanf(fp, "%49[^,],%f,%d,%d,%d,%d,%d\n",
                  lista[brojProizvoda].naziv,
                  &lista[brojProizvoda].cijena,
                  &lista[brojProizvoda].kolicina,
                  (int *)&lista[brojProizvoda].vrsta,
                  &lista[brojProizvoda].datumUnosa.dan,
                  &lista[brojProizvoda].datumUnosa.mjesec,
                  &lista[brojProizvoda].datumUnosa.godina) == 7) {
        brojProizvoda++;
    }

    fclose(fp);
}

void spremiUDatoteku() {
    FILE *fp = fopen("baza.txt", "w");
    if (fp == NULL) return;

    for (int i = 0; i < brojProizvoda; i++) {
        fprintf(fp, "%s,%.2f,%d,%d,%d,%d,%d\n",
                lista[i].naziv,
                lista[i].cijena,
                lista[i].kolicina,
                lista[i].vrsta,
                lista[i].datumUnosa.dan,
                lista[i].datumUnosa.mjesec,
                lista[i].datumUnosa.godina);
    }

    fclose(fp);
}

void oslobodiMemoriju() {
    // Nema dinamičke memorije u ovom primjeru
}

void dodajProizvod() {
    if (brojProizvoda >= MAX) {
        printf("Dostignut maksimalan broj proizvoda!\n");
        return;
    }

    printf("Unesi naziv: ");
    scanf(" %[\n^]", lista[brojProizvoda].naziv);
    printf("Unesi cijenu: ");
    scanf("%f", &lista[brojProizvoda].cijena);
    printf("Unesi kolicinu: ");
    scanf("%d", &lista[brojProizvoda].kolicina);

    do {
        printf("Unesi vrstu (1 - slatko, 2 - slano): ");
        scanf("%d", (int *)&lista[brojProizvoda].vrsta);
    } while (lista[brojProizvoda].vrsta != SLATKO && lista[brojProizvoda].vrsta != SLANO);

    printf("Unesi datum (dd mm yyyy): ");
    scanf("%d %d %d", &lista[brojProizvoda].datumUnosa.dan,
          &lista[brojProizvoda].datumUnosa.mjesec,
          &lista[brojProizvoda].datumUnosa.godina);

    brojProizvoda++;
    printf("Proizvod dodan.\n");
}

void ispisiProizvode() {
    for (int i = 0; i < brojProizvoda; i++) {
        printf("%d. %s | %.2f EUR | Kolicina: %d | %s | Datum: %02d.%02d.%04d\n",
               i + 1,
               lista[i].naziv,
               lista[i].cijena,
               lista[i].kolicina,
               lista[i].vrsta == SLATKO ? "Slatko" : "Slano",
               lista[i].datumUnosa.dan,
               lista[i].datumUnosa.mjesec,
               lista[i].datumUnosa.godina);
    }
}

void azurirajProizvod() {
    int index;
    printf("Unesi redni broj proizvoda za azuriranje: ");
    scanf("%d", &index);
    if (index < 1 || index > brojProizvoda) {
        printf("Neispravan broj.\n");
        return;
    }
    index--;

    printf("Novi naziv: ");
    scanf(" %[\n^]", lista[index].naziv);
    printf("Nova cijena: ");
    scanf("%f", &lista[index].cijena);
    printf("Nova kolicina: ");
    scanf("%d", &lista[index].kolicina);
}

void obrisiProizvod() {
    int index;
    printf("Unesi redni broj proizvoda za brisanje: ");
    scanf("%d", &index);
    if (index < 1 || index > brojProizvoda) {
        printf("Neispravan broj.\n");
        return;
    }
    index--;

    for (int i = index; i < brojProizvoda - 1; i++) {
        lista[i] = lista[i + 1];
    }
    brojProizvoda--;
    printf("Proizvod obrisan.\n");
}

void sortirajPoNazivu() {
    for (int i = 0; i < brojProizvoda - 1; i++) {
        for (int j = i + 1; j < brojProizvoda; j++) {
            if (strcmp(lista[i].naziv, lista[j].naziv) > 0) {
                Proizvod temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
    printf("Sortirano po nazivu.\n");
}

void sortirajPoDatumu() {
    for (int i = 0; i < brojProizvoda - 1; i++) {
        for (int j = i + 1; j < brojProizvoda; j++) {
            Datum d1 = lista[i].datumUnosa;
            Datum d2 = lista[j].datumUnosa;
            if (d1.godina > d2.godina ||
                (d1.godina == d2.godina && d1.mjesec > d2.mjesec) ||
                (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan > d2.dan)) {
                Proizvod temp = lista[i];
                lista[i] = lista[j];
                lista[j] = temp;
            }
        }
    }
    printf("Sortirano po datumu.\n");
}

void pretraziPoNazivu() {
    char trazeni[50];
    printf("Unesi naziv za pretragu: ");
    scanf(" %[\n^]", trazeni);

    for (int i = 0; i < brojProizvoda; i++) {
        if (strstr(lista[i].naziv, trazeni)) {
            printf("%s | %.2f EUR | Kolicina: %d\n",
                   lista[i].naziv, lista[i].cijena, lista[i].kolicina);
        }
    }
}

void statistikaKolicina() {
    int ukupno = 0;
    for (int i = 0; i < brojProizvoda; i++) {
        ukupno += lista[i].kolicina;
    }
    printf("Ukupna kolicina proizvoda: %d\n", ukupno);
}

void filtrirajPoDatumu(int dan, int mjesec, int godina) {
    for (int i = 0; i < brojProizvoda; i++) {
        Datum d = lista[i].datumUnosa;
        if (d.dan == dan && d.mjesec == mjesec && d.godina == godina) {
            printf("%s | %.2f EUR | Kolicina: %d\n",
                   lista[i].naziv, lista[i].cijena, lista[i].kolicina);
        }
    }
}

void prikaziOstatkeNaKrajuDana(int dan, int mjesec, int godina) {
    printf("Preostali proizvodi za %02d.%02d.%04d:\n", dan, mjesec, godina);
    for (int i = 0; i < brojProizvoda; i++) {
        Datum d = lista[i].datumUnosa;
        if (d.dan == dan && d.mjesec == mjesec && d.godina == godina && lista[i].kolicina > 0) {
            printf("%s | Kolicina: %d\n", lista[i].naziv, lista[i].kolicina);
        }
    }
}

void prikaziIzbornik() {
    printf("\n--- IZBORNIK ---\n");
    printf("1. Dodaj novi proizvod\n");
    printf("2. Ispisi sve proizvode\n");
    printf("3. Azuriraj proizvod\n");
    printf("4. Obrisi proizvod\n");
    printf("5. Spremi u datoteku\n");
    printf("6. Sortiraj po nazivu\n");
    printf("7. Pretrazi po nazivu\n");
    printf("8. Statistika kolicina\n");
    printf("9. Izlaz\n");
}
