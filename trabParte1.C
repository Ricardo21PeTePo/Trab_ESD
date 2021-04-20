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

typedef struct lplaylists_no {
    int id;
    char nome[200];
    playlist_no *musicas;
    struct lplaylists_no *prox;
} lplaylists_no;

void printMenu(){
    printf("0 - Terminar programa;\n");
    printf("1 - Cadastrar música;\n");
    printf("2 - Cadastrar playlist;\n");
}

void cadastrarMusica(){
    
}

int main(){
    int opcao = -1;
    do
    {
        printMenu();
        scanf("%d", &opcao);
    } while (opcao != 0);
    
}