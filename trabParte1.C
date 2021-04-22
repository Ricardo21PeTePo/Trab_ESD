#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

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
    printf("3 - Criar playlist;\n");

    printf("Insira uma opcao: ");
}
lplaylists_no* criaListaEncadeada(){
    lplaylists_no *cabeca = (lplaylists_no*) malloc(sizeof(lplaylists_no));
    cabeca->prox = NULL;
    return cabeca;
}

musica_no* criaListaDupla(){
    musica_no *cabeca = (musica_no*) malloc(sizeof(musica_no));
    cabeca->prox = NULL;
    cabeca->ant = NULL;
    return cabeca;
}

playlist_no* criaListaCircular(){
    playlist_no *cabeca = (playlist_no*) malloc(sizeof(playlist_no));
    cabeca->prox = cabeca;
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



void cadastrarMusica(musica_no *ini, musica *s){
    musica_no *novo;
    novo = (musica_no*) malloc(sizeof(musica_no));
    novo->musica = s;
    novo->prox = ini->prox;
    novo->ant = ini;
    ini->prox = novo;
}

void imprimirListaDeMusicas(musica_no* ini){
    musica_no* p;
    p = ini->prox;
    while (p)
    {
        cout << p->musica->titulo << endl;
        cout << p->musica->artista << endl;
        cout << p->musica->album << endl;
        int h, m, s;
        h = (p->musica->duracao/3600); 
	    m = (p->musica->duracao -(3600*h))/60;
	    s = (p->musica->duracao -(3600*h)-(m*60));
        printf("%d:%d:%d\n",h,m,s);
        printf("------------------------\n");

        p = p->prox;
    }
}



void inserirEmPlaylist(musica_no* ini, playlist_no* p, musica* s){
    musica_no* aux;
    aux = ini->prox;
    while (aux)
    {
        /* code */
    }
    
}


int main(){
    int opcao = -1;
    musica_no* listaDeMusicas = criaListaDupla();
    lplaylists_no* listaDePlaylists = criaListaEncadeada();
    do
    {
        printMenu();
        cin >> opcao;
        switch (opcao)
        {
        case 1:{
            musica *p = (musica*) malloc(sizeof(musica));
    
            printf("ID da musica: ");
            cin >> p->id;
            printf("Titulo da musica: ");
            cin >> p->titulo;
            printf("Artista da musica: ");
            cin >> p->artista;
            printf("Album da musica: ");
            cin >> p->album;
            printf("Duracao da musica: ");
            cin >> p->duracao;

            cadastrarMusica(listaDeMusicas, p);
            break;
        }
            
        case 2:
            imprimirListaDeMusicas(listaDeMusicas);
            break;
        case 3: {
            cout << "criar playlist";
        }
        default:
            break;
        }
        
    } while (opcao != 0);


    return 0;
}