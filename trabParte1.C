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
    printf("1 - Cadastrar musica;\n");
    printf("2 - Cadastrar playlist;\n");

    printf("Insira uma opcao: ");
}

musica_no* iniciaLista(){
    musica_no* cabeca;
    cabeca->prox = NULL;
    cabeca->ant = NULL;
    cabeca->musica = NULL;
    return cabeca;
}

int qtddMusicasCadastradas(musica_no* ini){
    int x = 0;
    musica_no* p = ini;
    while (p)
    {
        x++;
        p = p->prox;
    }
    return x;
    
}

void cadastrarMusica(musica_no* ini){
    musica novaMusica;
    novaMusica.id = qtddMusicasCadastradas(ini);
    printf("Insira o titulo da musica: ");
    scanf("%s", &novaMusica.titulo);
    printf("Insira o artista da musica: ");
    scanf("%s", &novaMusica.artista);
    printf("Insira o nome do album da musica: ");
    scanf("%s", &novaMusica.album);
    printf("Insira a duracao da musica [em segundos]: ");
    scanf("%d", &novaMusica.duracao);

    musica_no* p = ini->prox;
    p->ant = ini;
    p->musica = &novaMusica;
    ini->prox = p;
    
}

void imprimirListaDeMusicas(musica_no* ini){
    musica_no* p = ini->prox;
    while (p)
    {
        printf("%s", p->musica->titulo);
        p = p->prox;
    }
    
}

int main(){
    int opcao = -1;
    musica_no* listaDeMusicas = iniciaLista();
    do
    {
        printMenu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            cadastrarMusica(listaDeMusicas);
            break;
        case 2:
            imprimirListaDeMusicas(listaDeMusicas);
            break;
        default:
            break;
        }
        
    } while (opcao != 0);
    
}