#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proizvod.h"

static Proizvod* glava = NULL; // Glava povezane liste

void inicijalizirajListu() { glava = NULL; }

// Provjera postoji li naziv u listi (sprječava duplikate)
int postojiNaziv(char* naziv) {
    Proizvod* temp = glava;
    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) return 1;
        temp = temp->sljedeci;
    }
    return 0;
}

// Kreiranje proizvoda s validacijom
Proizvod* kreirajProizvod() {
    Proizvod* novi = malloc(sizeof(Proizvod));
    if (!novi) { perror("Greska pri alokaciji"); exit(1); }

    do {
        printf("Naziv: ");
        scanf("%s", novi->naziv);
        if (postojiNaziv(novi->naziv)) printf("Naziv vec postoji! Pokusaj opet.\n");
    } while (postojiNaziv(novi->naziv));

    do {
        printf("Vrsta (1=Slatko, 2=Slano): ");
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

// CREATE
void dodajProizvod() {
    Proizvod* novi = kreirajProizvod();
    novi->sljedeci = glava;
    glava = novi;
}

// READ
void ispisiProizvode() {
    if (!glava) { printf("Lista je prazna.\n"); return; }
    Proizvod* temp = glava;
    while (temp) {
        printf("%s | %s | %d/%d | %02d.%02d.%04d\n",
               temp->naziv,
               temp->vrsta == SLATKO ? "Slatko" : "Slano",
               temp->proizvedeno, temp->prodano,
               temp->datum.dan, temp->datum.mjesec, temp->datum.godina);
        temp = temp->sljedeci;
    }
}

// UPDATE
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
    printf("Nema proizvoda.\n");
}

// DELETE
void obrisiProizvod() {
    char naziv[MAX_NAZIV];
    printf("Naziv za brisanje: ");
    scanf("%s", naziv);
    Proizvod *temp = glava, *prethodni = NULL;
    while (temp) {
        if (strcmp(temp->naziv, naziv) == 0) {
            if (prethodni) prethodni->sljedeci = temp->sljedeci;
            else glava = temp->sljedeci;
            free(temp);
            printf("Obrisano.\n");
            return;
        }
        prethodni = temp;
        temp = temp->sljedeci;
    }
    printf("Nema proizvoda.\n");
}

// Spremanje (fwrite) + double check
void spremiUDatoteku() {
    char potvrda;
    printf("Jeste li sigurni da zelite spremiti? (Y/N): ");
    scanf(" %c", &potvrda);
    if (potvrda != 'Y' && potvrda != 'y') return;

    FILE* f = fopen("baza.bin", "wb");
    if (!f) { perror("Greska"); return; }

    Proizvod* temp = glava;
    while (temp) {
        fwrite(temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f);
        temp = temp->sljedeci;
    }
    fclose(f);
    printf("Podaci spremljeni.\n");
}

// Učitavanje (fread)
void ucitajIzDatoteke() {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) { printf("Nema baze.\n"); return; }

    oslobodiMemoriju();

    Proizvod temp;
    while (fread(&temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f)) {
        Proizvod* novi = malloc(sizeof(Proizvod));
        *novi = temp;
        novi->sljedeci = glava;
        glava = novi;
    }
    fclose(f);
    printf("Ucitano.\n");
}

// Backup (rename)
void backupDatoteke() {
    if (rename("baza.bin", "baza_backup.bin") == 0) {
        printf("Backup OK.\n");
    } else {
        printf("Nema baze za backup.\n");
    }
}

// Brisanje baze (remove)
void obrisiDatoteku() {
    if (remove("baza.bin") == 0) printf("Baza obrisana.\n");
    else printf("Nema baze.\n");
}

// fseek primjer
void ucitajNTiProizvod(int n) {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) { printf("Nema baze.\n"); return; }
    long pomak = (n - 1) * (sizeof(Proizvod) - sizeof(Proizvod*));
    fseek(f, pomak, SEEK_SET);
    Proizvod temp;
    if (fread(&temp, sizeof(Proizvod) - sizeof(Proizvod*), 1, f) == 1) {
        printf("Proizvod %d: %s %d/%d\n", n, temp.naziv, temp.proizvedeno, temp.prodano);
    } else {
        printf("Nema tog zapisa.\n");
    }
    fclose(f);
}

// Primjer ftell
void prikaziPoziciju() {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) return;
    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    printf("Velicina fajla: %ld bajta.\n", pos);
    fclose(f);
}

// Rewind
void rewindDatoteke() {
    FILE* f = fopen("baza.bin", "rb");
    if (!f) return;
    rewind(f);
    printf("Pokazivac vracen na pocetak.\n");
    fclose(f);
}

// Sortiranje po nazivu
void sortirajPoNazivu() {
    // Bubble sort za povezan popis
    int zamjena;
    do {
        zamjena = 0;
        Proizvod* p = glava;
        while (p && p->sljedeci) {
            if (strcmp(p->naziv, p->sljedeci->naziv) > 0) {
                Proizvod temp = *p; *p = *p->sljedeci; *p->sljedeci = temp;
                Proizvod* t = p->sljedeci; p->sljedeci = t->sljedeci; t->sljedeci = p;
                zamjena = 1;
            }
            p = p->sljedeci;
        }
    } while (zamjena);
    printf("Sortirano po nazivu.\n");
}

// (Slično sortiranje po datumu, filtriranje, pretraga, statistika, ostatci itd. dodaš po istom principu.)

void prikaziIzbornik() {
    printf("\n--- IZBORNIK ---\n");
    printf("1 Dodaj | 2 Ispisi | 3 Azuriraj | 4 Obrisi | 5 Spremi | 6 Ucitaj\n");
    printf("7 Backup | 8 Obrisi bazu | 9 fseek | 10 ftell | 11 rewind\n");
    printf("12 Sortiraj naziv | 13 Izlaz\n");
}

void oslobodiMemoriju() {
    while (glava) {
        Proizvod* t = glava;
        glava = glava->sljedeci;
        free(t);
    }
}