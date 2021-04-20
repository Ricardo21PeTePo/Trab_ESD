#include <stdlib.h>
#include <stdio.h>

typedef struct musica {
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; //em segundos
} musica;

typedef struct musica_no {
    musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} musica_no;

typedef struct playlist_no {
    musica *musica;
    struct playlist_no *prox;
} playlist_no;

int main(){

}