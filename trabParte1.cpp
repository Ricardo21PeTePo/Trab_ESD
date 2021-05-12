#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <time.h>

using namespace std;

#define MAX_CHAR 200

typedef struct musica {
    int id;
    char titulo[MAX_CHAR];
    char artista[MAX_CHAR];
    char album[MAX_CHAR];
    int duracao;
} Musica;

typedef struct musica_no {
    Musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} musica_no;

typedef struct playlist_no {
    Musica *musica;
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
    printf("4 - Imprimir playlists;\n");
    printf("5 - Shuffle;\n");
    printf("6 - Imprimir uma playlist;\n");
    printf("7 - Remover musica;\n");

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

    if (ini->prox)
    {
        ini->prox->ant = novo;
    }
    ini->prox = novo;
}

void imprimirListaDeMusicas(musica_no* ini){
    musica_no* p;
    p = ini->prox;
    while (p)
    {
        if (p->musica)
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
        } else {
            break;
        }
    }
}

playlist_no* criaPlaylist(int qtddM, int musicas[], musica_no* listaDeMusicas){
    int i;
    musica_no* ini = listaDeMusicas->prox;
    playlist_no* novaPlaylist = criaListaCircular();
    for (i = qtddM-1; i >= 0; i--)
    {
        while (ini)
        {
            if(ini->musica->id == musicas[i]){
                playlist_no* p = (playlist_no*) malloc(sizeof(playlist_no));
                p->musica = ini->musica;
                if (novaPlaylist->prox == novaPlaylist)
                {
                    novaPlaylist->prox = p;
                    p->prox = novaPlaylist;
                } else {
                    p->prox = novaPlaylist->prox;
                    novaPlaylist->prox = p;
                }
                
            }
            ini = ini->prox;
        }
        ini = listaDeMusicas->prox;
    }
    return novaPlaylist;
}


void inserirPlaylist(lplaylists_no* ini, playlist_no* p, int id, char* nome){
    lplaylists_no* novaPlaylist = (lplaylists_no*) malloc(sizeof(lplaylists_no));
    novaPlaylist->musicas = p;
    novaPlaylist->id = id; 
    strcpy(novaPlaylist->nome, nome);

    novaPlaylist->prox = ini->prox;
    ini->prox = novaPlaylist;
}

void imprimirPlaylists(lplaylists_no* lp){
    lplaylists_no* ini = lp->prox;
    while (ini)
    {
        playlist_no* p = ini->musicas;      
        cout << ini->nome << endl;
        cout << "----------";
        ini = ini->prox;
    }
}

void shuffle(char* np, lplaylists_no* ini){
    int i, cont = 0, j;
    
    lplaylists_no* lp = ini->prox;
    while (lp){
        if (strcmp(lp->nome, np) == 0){
            playlist_no* p = lp->musicas->prox;
            while (p->musica){
                cont++;
                p = p->prox;
            }
            break;
        }
        lp = lp->prox;
    }
    /*
    int arrayRand[cont];
    int check = 0;
    for (i = 0; i < cont; i++){
        int r = rand() % cont;
        for (j = 0; j < cont; j++)
        {
            if (arrayRand[j] == r)
            {
                check = 1;
            } 
            
        }
        if (check == 0)
        {
            arrayRand[i] = r;
        } else {
            i--;
        }
        check = 0;     
    }
    */

    playlist_no* lpm = lp->musicas->prox;
    int counterAux = 0;
    while (lpm && counterAux < cont)
    {
        int r = rand() % cont;
        int counter = 0;
        playlist_no* lpms = lpm;
        while (counter < r)
        {
            lpms = lpms->prox;
            counter++;  
        }
        Musica* m = lpms->musica;
        lpms->musica = lpm->musica;
        lpm->musica = m;
        lpm = lpm->prox;
        counterAux++;
    }
    
}

void imprimirUmaPlaylist(char* nome, lplaylists_no* ini){
    lplaylists_no* lp = ini->prox;
    while (lp)
    {
        if (strcmp(lp->nome, nome) == 0)
        {
            playlist_no* p = lp->musicas->prox;
            while (p->musica)
            {
                cout << p->musica->titulo << endl;
                p = p->prox;
            }
            return;
        }
        lp = lp->prox;
    }
    cout << "playlist nao encontrada" << endl;
    
}

void excluirMusica(char* nome, lplaylists_no* play, musica_no* musi) {
    musica_no* lm = musi->prox;

    while (lm) {
        if (strcmp(lm->musica->titulo, nome) == 0)
        {
            lm->ant->prox = lm->prox;
            delete lm;
            break;
        }
        lm = lm->prox;
    }

    playlist_no* lp = play->prox->musicas->prox;
    while (lp)
    {
        if (strcmp(lp->musica->titulo, nome) == 0){
            lp = lp->prox;
            delete lp;
            break;
        }
    }
    

}

int main(){
    srand(time(NULL));
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
            Musica *p = (Musica*) malloc(sizeof(Musica));
    
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

            int qtddMusicasP, i, idPlaylist, j;
            char nomePlaylist[MAX_CHAR];
            cout << "Quantas musicas deseja inserir? ";
            cin >> qtddMusicasP;
            cout << "Digite os IDs das musicas que deseja inserir: ";
            int novaPlaylist[qtddMusicasP];
            for (i = 0; i < qtddMusicasP; i++)
            {
                cin >> novaPlaylist[i];
            }
            cout << "Insira o nome da playlist: ";
            cin >> nomePlaylist;
            cout << "Insira o ID da playlist: ";
            cin >> idPlaylist;
                        
            inserirPlaylist(listaDePlaylists, criaPlaylist(qtddMusicasP, novaPlaylist, listaDeMusicas), idPlaylist, nomePlaylist);
            break;

        }
        case 4:
            cout << "Nomes das playlists: ";
            imprimirPlaylists(listaDePlaylists);
            break;
        case 5: {
            char nomeShuffle[MAX_CHAR] = "";
            cout << "Insira o nome da playlist desejada: ";
            cin >> nomeShuffle;
            shuffle(nomeShuffle, listaDePlaylists);
            break;
        }
        case 6: {
            char nomeSearch[MAX_CHAR] = "";
            cout << "Insira o nome da playlist que deseja ver: ";
            cin >> nomeSearch;
            imprimirUmaPlaylist(nomeSearch, listaDePlaylists);
            break;
        }
        case 7: {
            char nomeExcluir[MAX_CHAR] = "";
            cout << "insira o nome da musica desejada: ";
            cin >> nomeExcluir;
            excluirMusica(nomeExcluir, listaDePlaylists, listaDeMusicas);
            break;
        }
        default:
            break;
        }
            
        
    } while (opcao != 0);


    return 0;
}