#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct{ //campuri pe biti
	unsigned short int minute : 6;
	unsigned short int ore : 2;
} Durata;

typedef struct{ //structura de date
    char nume[20];
    char artist[20];
    char gen[20]; //fara spatii
    int aparitie;
    Durata durata;
    char categorie;
    double nota;
    bool ealbum; //sau single
}Album;
void afisare_static(Album *albume, int n, FILE *f){ //afiseaza in consola sau fisier vectorii statici
    int i;
    for(i = 0; i < n; i++){
    	 fprintf(f, "Categorie: %c\n", albume[i] . categorie);
        fprintf(f, "Nume album: %s\n", albume[i] . nume);
        fprintf(f, "Artist: %s\n", albume[i] . artist);
        fprintf(f, "Aparitie: %d\n", albume[i] . aparitie);
        fprintf(f, "Durata: %d:%d\n", albume[i] . durata.ore, albume[i] . durata.minute);
        fprintf(f, "Gen: %s\n", albume[i] . gen);
        fprintf(f, "Nota: %f\n", albume[i] . nota);
        if(albume[i] . ealbum)
            fprintf(f, "Este album");
        else
            fprintf(f, "Este single");

        fprintf(f, "\n\n****************\n");
    }
}
void afisare(Album **albume, int n, FILE *f){       //                                                  vectorii dinamici
    int i;
    for(i = 0; i < n; i++){

            printf("debug5");
    	 fprintf(f,"Categorie: %c\n", albume[i] -> categorie);
        fprintf(f,"Nume album: %s\n", albume[i] -> nume);
        fprintf(f,"Artist: %s\n", albume[i] -> artist);
        fprintf(f,"Aparitie: %d\n", albume[i] -> aparitie);
        fprintf(f,"Durata: %d:%d\n", albume[i] -> durata.ore, albume[i] -> durata.minute);
        fprintf(f,"Gen: %s\n", albume[i] -> gen);
        fprintf(f,"Nota: %f\n", albume[i] -> nota);
        if(albume[i] -> ealbum)
            fprintf(f,"Este album");
        else
            fprintf(f,"Este single");

        fprintf(f,"\n\n****************\n");
    }
}

Album *adaugare_album(){      //produce un element de tip album cu elemente din consola
    char nume[30], artist[20], gen[20];
    char c, categorie;
    int aparitie, o, m, melodii, pozitie;
    double nota;
    bool ealbum;

    Album * albm;
    albm = (Album*) malloc(sizeof(Album));

    printf("\nNume:");
    fgets(nume, 30, stdin);
    //if(!eof()) return NULL;
    strcpy(albm -> nume, nume);

    printf("\nArtist:");
    fgets(artist, 30, stdin);
    strcpy(albm -> artist, artist);

    printf("\nAnul aparitiei:");
    fscanf(stdin, "%d", &aparitie);
    albm -> aparitie = aparitie;

    printf("\nDurata(ora):");
    scanf("%d", &o);

    printf("\nDurata(minute):");
    scanf("%d", &m);
    albm -> durata.ore = o;
    albm -> durata.minute = m;

    printf("\nGen muzical:");
    fflush(stdin);
    fscanf(stdin,"%s", gen);
    strcpy(albm -> gen, gen);

    printf("\nCategorie:");
    fflush(stdin);
    categorie = getchar();
    albm -> categorie = categorie;
    fflush(stdin);

    printf("\nNota:");
    fscanf(stdin,"%lf", &nota);
    albm -> nota = nota;

    printf("\nEste album sau single?(A sau S)");
    fflush(stdin);
    fscanf(stdin,"%c", &c);
    if(c == 'A')
        albm -> ealbum = 1;
    else
        albm -> ealbum = 0;
    fflush(stdin);

    return albm;
}

Album * f_adaugare_album(char *s){  //                                          cu elemente din fisier
    //formatul necesar:
    //nume album,artist,an aparitie,nota acordata,categoria,gen,album(A) sau single(S),durata
    char br[100];
    strcpy(br,s);
    Album * albm;
    albm = (Album*) malloc(sizeof(Album));
    //preia stringul si asociaza fiecare intrare structurii
    char *token;

    token = strtok(br, ",");     //artist
    strcpy(albm -> artist, token);

    token = strtok(NULL, ",");    //nume
    strcpy(albm -> nume, token);

    token = strtok(NULL, ",");     //aparitie
    albm -> aparitie =  atoi(token);

    token = strtok(NULL, ",");  //nota
    albm -> nota = atof(token);

    token = strtok(NULL, ",");  //categorie
    albm -> categorie = token[0];

    token = strtok(NULL, ",");  //gen
    strcpy(albm -> gen, token);

    token = strtok(NULL, ",");  //album sau single
    if(token[0] == 'A')
        albm -> ealbum = 1;
    if(token[0] == 'S')
        albm -> ealbum = 0;

    token = strtok(NULL, ":");      //durata ore
    albm -> durata.ore = atoi(token);

    token = strtok(NULL, ",");      //durata minute
    albm -> durata.minute = atoi(token);

    return albm;
}

void inregistrare_n(){ //consola, n variabile, static
    int n, i = 0;
    char *s;
    printf("n = ");
    scanf("%d", &n);
    fflush(stdin);

    Album albume[40];
    while(i < n){
        albume[i++] = *adaugare_album();
    }
        afisare_static(albume,n, stdout);
}

void inregistrare_eof(){ //consola, pana la eof, static
    Album albume[30];
    Album *albm;
    int i = 0;
    char c;

    printf("\n\n\t\tApasati orice tasta pentru a adauga un album sau Ctrl + Z pentru a va opri\n\n");
    c = getchar();

    while(c != EOF){
        fflush(stdin);
        albume[i++] = *adaugare_album();
        printf("\n\n\t\tApasati orice tasta pentru a adauga un album sau Ctrl + Z pentru a va opri\n\n");
        c = getchar();
    }

    afisare_static(albume, i, stdout);
}

void inregistrare_dinamica_n(){ //consola, pana la n, dinamic
   int n, i = 0;
    printf("n = ");
    scanf("%d", &n);
    fflush(stdin);

    Album **albume;
    albume = (Album **) malloc(n * sizeof(Album*));

    while(i < n){
        albume[i++] = adaugare_album();
    }

    afisare(albume, n, stdout);

}

void inregistrare_dinamica_eof(){   //consola, pana la eof, dinamic
    Album *albm;
    int i = 1;
    int n;
    Album **albume;
    albume = (Album **) calloc(0, sizeof(Album));

    char c;

    printf("\n\n\t\tApasati orice tasta pentru a adauga un album sau Ctrl + Z pentru a va opri\n\n");
    c = getchar();
    fflush(stdin);

    while(c != EOF){
        fflush(stdin);
        albume = (Album **) realloc(albume, ( sizeof(Album*)*i));
        albm = adaugare_album();
        albume[i - 1] = albm;
        n = i;
        i++;
        printf("\n\n\t\tApasati orice tasta pentru a adauga un album sau Ctrl + Z pentru a va opri\n\n");
        c = getchar();
    }

    afisare(albume, n, stdout);
}

void f_inregistrare_n(FILE *f, FILE *g){  //fisier, pana la n, static
    char s[100];
    int n, i = 0;
    Album albume[20];
    printf("n = ");
    scanf("%d", &n);

    while(i < n){
        fgets(s, 100, f);
        albume[i++] = *f_adaugare_album(s);
    }
    afisare_static(albume, n, g);
}

void f_inregistrare_eof(FILE *f, FILE *g){  //fisier, pana la eof, static
    char s[100];
    int i = 0;
    Album albume[20];

    while(!feof(f)){
        fgets(s, 100, f);
        albume[i++] = *f_adaugare_album(s);
    }

    afisare_static(albume, i, g);
}

void f_inregistrare_dinamica_n(FILE *f, FILE *g){   //fisier, pana la n, dinamic
    char s[100];
    int n, i = 0;

    printf("n = ");
    scanf("%d", &n);

    Album **albume;
    albume = (Album **) malloc(n * sizeof(Album));

    while(i < n){
        fgets(s, 100, f);
        albume[i++] = f_adaugare_album(s);
    }

    afisare(albume, n, g);
}

Album **f_inregistrare_dinamica_eof(FILE *f, int *n){  //fisier, pana la eof, dinamic + cerinte speciale
    char s[100];
    int i = 1, c;

    Album **albume;
    albume = (Album **) calloc(0, sizeof(Album));
    //fgets(s, 40, f);

    while(!feof(f)){
        albume = (Album **) realloc(albume, ( sizeof(Album*)*i));
        fgets(s, 100, f);
        albume[i-1] = f_adaugare_album(s);
        c = i - 1;
        i++;
    }
    *n = c;
    return albume;
}

  int comp(const void *elem1, const void *elem2){ //comparare pentru qsort in functie de ani
    Album **a = (Album **) elem1;
    Album **b = (Album **) elem2;

    int  l = (*a) -> aparitie;
    int r = (*b) -> aparitie;

    if(l > r)   return 1;    //le aranjeaza crescator
    if(l < r)   return -1;	//1 aici pentru descrescator
    return 0;
}

int compalf(const void *elem1, const void *elem2){ //comparare pentru qsort in functie de ordine alfabetica si ani
                                                                    //aranjeaza alfabetic si fiecare album al aceleaiasi trupe
    Album **a = (Album **) elem1;				//crescator dupa aparitie
    Album **b = (Album **) elem2;

    int  l = (*a) -> aparitie;
    int r = (*b) -> aparitie;

    char x[30];
    char y[30];
    strcpy(x, (*a) -> artist);
    strcpy(y, (*b) -> artist);

    int d = strcmp(x, y);

    if(d > 0)   {
            return 1;
    }
    if(d < 0){
            return -1;
    }

    if(d == 0){
        if(l > r)   return 1;
        if(l < r)   return -1;
    }

    return 0;
}

void modificare_the(Album **albume, int n){  //elimina "the"-ul din fata unei trupe si il baga la sfarsit
    char *b;
    int i;
    for(i = 0; i < n; i++){
    	if(b = (strstr(albume[i] -> artist,"The "))){
    		memmove(b, b + 4, strlen(b) - 3 + 1);
    		strcat(albume[i] -> artist, ",The");
    	}
    }
}

void schimbare_cat(Album **albume, int n){  //schimbare categorie
    char cmod1, cmod2;
    int i;
   printf("Mutare albume dintr-o categorie in alta\n\nIntroduceti categoria initiala:");
   cmod1 = getchar();
   printf("Introduceti categoria noua");
   fflush(stdin);
   cmod2 = getchar();
   fflush(stdin);

    for(i = 0; i < n; i++){
            if(albume[i] -> categorie == cmod1)
                albume[i] -> categorie = cmod2;
    }
}

void modificare_aparitie(Album **albume, int n){ //modificare aparitie
    int i;
    printf("Modificare an");
    printf("Scrieti numele albumului al carui an de aparitie doriti sa il modificati");
    char nume[40];
    gets(nume);
    fflush(stdin);
    int an;
	for(i = 0; i < 12; i++){
        if(strcmp(albume[i] -> nume, nume) == 0){
            printf("Introduceti noul an");
            scanf("%d", &an);
            albume[i] -> aparitie = an;
            break;
        }
   }
}

void functie(FILE *intrare, FILE *iesire){ //functia pentru cerinte special; merge numai cu fisier, pana la eof, dinamic

    int nr, optiune, i = 0;
    int *n = &nr;
    Album **albume;
    albume = f_inregistrare_dinamica_eof(intrare, n);
    nr = *n;

	printf("\n\t1.Afisare albume dintr-o categorie");
	printf("\n\t2.Sortare in functie de anul aparitiei");
	printf("\n\t3.Sortare in functie de numele trupei si anul aparitiei");
	printf("\n\t4.Modificare nume trupe care au the in fata");
	printf("\n\t5.Schimbare categorie album");
	printf("\n\t6.Modificare an aparitie album");
	printf("\n\t0.Iesire");

	fflush(stdin);
	while(optiune != 0){
        int optiune = getchar() - '0';
        fflush(stdin);
        switch(optiune){
            case 1:
                printf("\nCare categorie?");
                char cat = getchar();
                for(i = 0; i  < nr; i++){
                    if(albume[i] -> categorie == cat){
                    fprintf(iesire, "Categorie: %c\n", albume[i] -> categorie);
                    fprintf(iesire, "Nume album: %s\n", albume[i] -> nume);
                    fprintf(iesire, "Artist: %s\n", albume[i] -> artist);
                    fprintf(iesire, "Aparitie: %d\n", albume[i] -> aparitie);
                    fprintf(iesire, "Gen: %s\n", albume[i] -> gen);
                    fprintf(iesire, "Durata: %d:%d\n", albume[i] -> durata.ore, albume[i] -> durata.minute);
                    fprintf(iesire, "Nota: %f\n", albume[i] -> nota);
                    if(albume[i] -> ealbum)
                        fprintf(iesire, "Este album");
                    else
                        fprintf(iesire, "Este single");

                        fprintf(iesire, "\n\n****************\n");
                    }
                }
                break;
            case 2:
                qsort(albume, nr, sizeof(Album*), comp);
                break;
            case 3:
                qsort(albume, nr, sizeof(Album*), compalf);
                break;
            case 4:
                modificare_the(albume, nr);
                break;
            case 5:
                schimbare_cat(albume, nr);
                break;
            case 6:
                modificare_aparitie(albume, nr);
                break;
            case 0:
                return;
                break;
            default:
                printf("Introduceti o optiune");
	}
	}
}

void meniu(){
    enum afisare{FISIER = 1, CONSOLA = 2};
    enum memorare{VECTORN = 1, VECTOREOF = 2, DINAMICN = 3, DINAMICEOF = 4};
    int afisare, memorare, alegere;                 //declarari
    char f_afisare[40];
    char f_citire[40];
    FILE *fin = NULL;
    FILE *fout = NULL;

	system("COLOR 3F");

    printf("\n\n\n\t\t\t    Albume de muzica\n\n\n\n");
    printf("\t\t\tApasati orice tasta pentru a continua");              //afisare initiala
    getchar();
    system("cls");
    fflush(stdin);
    printf("\n\n\t\tAlegeti modul de citire/afisare:");
    printf("\n\t\t\t1. Fisiere");
    printf("\n\t\t\t2. Consola\n\n");

    afisare = getchar() - '0';

    switch(afisare){
    case FISIER:
        printf("Ati ales sa lucrati cu fisiere");
                system("cls");
            printf("\nNumele fisierului de citire a datelor:");     //declara fisierul de citire, il deschide, ii citeste numele
            fflush(stdin);
            gets(f_citire);
            fin = fopen(f_citire, "r");

            system("cls");
            printf("\nNumele fisierului de afisare a datelor:");    //fisierul de scriere
            fflush(stdin);
            gets(f_afisare);
            fout = fopen(f_afisare, "w");
        break;
    case CONSOLA:
        printf("Ati ales sa lucrati cu consola"); break;
    default:
        printf("Introduceti o optiune valida"); break;
    }

    system("cls");
    printf("\n\n\t\tAlegeti modul de memorare:");
    printf("\n\t\t\t1. Vector cu n elemente de tip structura");
    printf("\n\t\t\t2. Vector cu numar necunoscut de elemente");
    printf("\n\t\t\t3. Alocare dinamica pentru n elemente");
    printf("\n\t\t\t4. Alocare dinamica pentru un numar necunoscut de elemente\n\n");

    fflush(stdin);
    memorare = getchar() - '0';

    switch(memorare){
        case VECTORN:
            printf("Ati ales memorarea printr-un vector de n elemente");
            if(afisare == CONSOLA)
                inregistrare_n();
            if(afisare == FISIER)
                f_inregistrare_n(fin, fout);
                fclose(fin);
                fclose(fout);
            return;
        case VECTOREOF:
            printf("Ati ales memorarea printr-un vector cu numar necunoscut de elemente");
            if(afisare == CONSOLA)
                inregistrare_eof();
            if(afisare == FISIER)
                f_inregistrare_eof(fin, fout);
                fclose(fin);
                fclose(fout);
            return;
        case DINAMICN:
            printf("Ati ales memorarea dinamica de n elemente");
            if(afisare == FISIER)
                f_inregistrare_dinamica_n(fin, fout);
                fclose(fin);
                fclose(fout);
            if(afisare == CONSOLA)
                inregistrare_dinamica_n();
            return;
        case DINAMICEOF:
            printf("Ati ales memorarea dinamica a unui numar necunoscut de elemente");
            if(afisare == FISIER)
                functie(fin, fout);
                fclose(fin);
                fclose(fout);
            if(afisare == CONSOLA)
                inregistrare_dinamica_eof();
            return;
        default:
            printf("Introduceti o optiune valida"); break;
    }

    printf("\n\n\t\t\tApasati orice tasta pentru a continua");
    fflush(stdin);
    getchar();
    system("cls");
    fflush(stdin);

}

int main()
{
    meniu();

    return 0;
}
