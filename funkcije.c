#include "HEADER.H"

void dodajProizvod(Proizvod **proizvodi, int *brojProizvoda) {
    *proizvodi = realloc(*proizvodi, (*brojProizvoda + 1) * sizeof(Proizvod));
    printf("Naziv: ");
    scanf(" %49[^\n]", (*proizvodi)[*brojProizvoda].naziv);
    
    int tip;
    do {
        printf("Vrsta (1 - Slatko, 2 - Slano): ");
        scanf("%d", &tip);
    } while (tip < 1 || tip > 2);
    (*proizvodi)[*brojProizvoda].vrsta = tip;

    printf("Kolicina: ");
    scanf("%d", &(*proizvodi)[*brojProizvoda].kolicina);
    printf("Cijena: ");
    scanf("%f", &(*proizvodi)[*brojProizvoda].cijena);
    printf("Datum (dd mm yyyy): ");
    scanf("%d %d %d", &(*proizvodi)[*brojProizvoda].datumProizvodnje.dan,
          &(*proizvodi)[*brojProizvoda].datumProizvodnje.mjesec,
          &(*proizvodi)[*brojProizvoda].datumProizvodnje.godina);
    (*brojProizvoda)++;
}

void ispisiProizvode(Proizvod *proizvodi, int brojProizvoda) {
    for (int i = 0; i < brojProizvoda; i++) {
        printf("%s | %s | %d | %.2f | %02d.%02d.%d\n",
               proizvodi[i].naziv,
               proizvodi[i].vrsta == SLATKO ? "Slatko" : "Slano",
               proizvodi[i].kolicina,
               proizvodi[i].cijena,
               proizvodi[i].datumProizvodnje.dan,
               proizvodi[i].datumProizvodnje.mjesec,
               proizvodi[i].datumProizvodnje.godina);
    }
}

void spremiUDatoteku(Proizvod *proizvodi, int brojProizvoda) {
    FILE *fp = fopen("proizvodi.txt", "w");
    for (int i = 0; i < brojProizvoda; i++) {
        fprintf(fp, "%s %d %d %.2f %d %d %d\n",
                proizvodi[i].naziv,
                proizvodi[i].vrsta,
                proizvodi[i].kolicina,
                proizvodi[i].cijena,
                proizvodi[i].datumProizvodnje.dan,
                proizvodi[i].datumProizvodnje.mjesec,
                proizvodi[i].datumProizvodnje.godina);
    }
    fclose(fp);
}

void ucitajIzDatoteke(Proizvod **proizvodi, int *brojProizvoda) {
    FILE *fp = fopen("proizvodi.txt", "r");
    if (!fp) return;
    Proizvod temp;
    while (fscanf(fp, " %49s %d %d %f %d %d %d", temp.naziv, (int*)&temp.vrsta,
                  &temp.kolicina, &temp.cijena,
                  &temp.datumProizvodnje.dan, &temp.datumProizvodnje.mjesec,
                  &temp.datumProizvodnje.godina) == 7) {
        *proizvodi = realloc(*proizvodi, (*brojProizvoda + 1) * sizeof(Proizvod));
        (*proizvodi)[*brojProizvoda] = temp;
        (*brojProizvoda)++;
    }
    fclose(fp);
}

void obrisiProizvod(Proizvod *proizvodi, int *brojProizvoda) {
    char naziv[MAX_NAZIV];
    printf("Unesite naziv za brisanje: ");
    scanf(" %49[^\n]", naziv);
    for (int i = 0; i < *brojProizvoda; i++) {
        if (strcmp(proizvodi[i].naziv, naziv) == 0) {
            for (int j = i; j < *brojProizvoda - 1; j++)
                proizvodi[j] = proizvodi[j + 1];
            (*brojProizvoda)--;
            printf("Obrisano.\n");
            return;
        }
    }
    printf("Nije pronadjen.\n");
}

void azurirajProizvod(Proizvod *proizvodi, int brojProizvoda) {
    char naziv[MAX_NAZIV];
    printf("Unesite naziv za ažuriranje: ");
    scanf(" %49[^\n]", naziv);
    for (int i = 0; i < brojProizvoda; i++) {
        if (strcmp(proizvodi[i].naziv, naziv) == 0) {
            printf("Nova kolicina: ");
            scanf("%d", &proizvodi[i].kolicina);
            printf("Nova cijena: ");
            scanf("%f", &proizvodi[i].cijena);
            return;
        }
    }
    printf("Nije pronadjen.\n");
}

int compareNaziv(const void *a, const void *b) {
    return strcmp(((Proizvod *)a)->naziv, ((Proizvod *)b)->naziv);
}

int compareDatum(const void *a, const void *b) {
    Datum d1 = ((Proizvod *)a)->datumProizvodnje;
    Datum d2 = ((Proizvod *)b)->datumProizvodnje;
    if (d1.godina != d2.godina) return d1.godina - d2.godina;
    if (d1.mjesec != d2.mjesec) return d1.mjesec - d2.mjesec;
    return d1.dan - d2.dan;
}

void sortirajPoNazivu(Proizvod *proizvodi, int brojProizvoda) {
    qsort(proizvodi, brojProizvoda, sizeof(Proizvod), compareNaziv);
}

void sortirajPoDatumu(Proizvod *proizvodi, int brojProizvoda) {
    qsort(proizvodi, brojProizvoda, sizeof(Proizvod), compareDatum);
}
