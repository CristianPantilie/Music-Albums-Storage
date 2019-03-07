#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED



#endif // HEADER_H_INCLUDED

typedef struct{
	unsigned short int minute : 6;
	unsigned short int ore : 2;
} Durata;

typedef struct{
    char nume[20];
    char artist[20];
    char gen[20]; //fara spatii
    int aparitie;
    Durata durata;
    char categorie;
    double nota;
    bool ealbum; //sau single
}Album;
