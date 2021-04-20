#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 200

typedef struct musica {
    int id;
    char titulo[MAX_CHAR];
    char artista[MAX_CHAR];
    char album[MAX_CHAR];
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
    char nome[MAX_CHAR];
    playlist_no *musicas;
    struct lplaylists_no *prox;
} lplaylists_no;

void printMenu(){
    printf("0 - Terminar programa;\n");
    printf("1 - Cadastrar musica;\n");
    printf("2 - Lista de musicas;\n");

    printf("Insira uma opcao: ");
}

musica_no* criaLista(){
    musica_no* cabeca = (musica_no*) malloc(sizeof(musica_no));
    cabeca->prox = NULL;
    cabeca->ant = NULL;
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

musica definirMusica(){
    musica p;
    
    printf("ID da musica: ");
    scanf("%d", &p.id);
    printf("Titulo da musica: ");
    fflush(stdin);
    fgets(p.titulo, MAX_CHAR, stdin);
    printf("Artista da musica: ");
    fflush(stdin);
    fgets(p.artista, MAX_CHAR, stdin);
    printf("Album da musica: ");
    fflush(stdin);
    fgets(p.album, MAX_CHAR, stdin);
    printf("Duracao da musica: ");
    scanf("%d", &p.duracao);

    return p;
}

void cadastrarMusica(musica_no *ini, musica s){
    musica_no *novo;
    novo = (musica_no*) malloc(sizeof(musica_no));

    novo->musica = &s;
    novo->prox = ini->prox;
    novo->ant = ini;
    if (ini->prox) ini->prox->ant = novo;
    ini->prox = novo;
}

void imprimirListaDeMusicas(musica_no* ini){
    musica_no* p;
    p = ini->prox;
    while (p)
    {
        printf("%s", p->musica->titulo);
        printf("%s", p->musica->artista);
        printf("%s", p->musica->album);
        int h, m, s;
        h = (p->musica->duracao/3600); 
	    m = (p->musica->duracao -(3600*h))/60;
	    s = (p->musica->duracao -(3600*h)-(m*60));
        printf("%d:%d:%d\n",h,m,s);
        printf("------------------------");

        p = p->prox;
    }
}

int main(){
    int opcao = -1;
    musica_no* listaDeMusicas = criaLista();
    do
    {
        printMenu();
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            cadastrarMusica(listaDeMusicas, definirMusica());
            break;
        case 2:
            imprimirListaDeMusicas(listaDeMusicas);
            break;
        default:
            break;
        }
        
    } while (opcao != 0);


    return 0;
}