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
    // int bal;
    struct musica_no *esq, *dir;
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

int alturaArvore(musica_no* t) {
  if (t == NULL)
    return 0;
  int hesq = alturaArvore(t->esq);  
  int hdir = alturaArvore(t->dir);
  return hesq > hdir ? hesq + 1 : hdir + 1;
}

lplaylists_no* criaListaEncadeada(){
    lplaylists_no *cabeca = (lplaylists_no*) malloc(sizeof(lplaylists_no));
    cabeca->prox = NULL;
    return cabeca;
}

musica_no* criaArvore(Musica* m, musica_no* esq, musica_no* dir){
    musica_no *musica = (musica_no*) malloc(sizeof(musica_no));
    musica->musica = m;
    // musica->bal = alturaArvore(dir) - alturaArvore(esq);
    musica->esq = esq;
    musica->dir = dir;
    return musica;
}

playlist_no* criaListaCircular(){
    playlist_no *cabeca = (playlist_no*) malloc(sizeof(playlist_no));
    cabeca->prox = cabeca;
    return cabeca;
}

int qtddMusicasCadastradas(musica_no* ini){
    musica_no* p = ini;
    if (p == NULL)
    {
        return 0;
    } else {
        return qtddMusicasCadastradas(p->esq) + qtddMusicasCadastradas(p->dir) + 1;
    }
}

// void LL(musica_no** r) {
//     musica_no* b = *r;
//     musica_no* a = b->esq;
//     b->esq = a->dir;
//     a->dir = b;
//     a->bal = 0;
//     b->bal = 0;
//     *r = a;
// }

// void RR(musica_no** r) {
//     musica_no* a = *r;
//     musica_no* b = a->dir;
//     a->dir = b->esq;
//     b->esq = a;
//     a->bal = 0;
//     b->bal = 0;
//     *r = b;
// }

// void LR(musica_no** r) {
//     musica_no *c = *r;
//     musica_no *a = c->esq;
//     musica_no *b = a->dir;
//     c->esq = b->dir;
//     a->dir = b->esq;
//     b->esq = a;
//     b->dir = c;
//     switch(b->bal) {
//     case -1:
//         a->bal = 0;
//         c->bal = 1;
//         break;
//     case 0:
//         a->bal = 0;
//         c->bal = 0;
//         break;
//     case +1:
//         a->bal = -1;
//         c->bal = 0;
//         break;
//     }
//     b->bal = 0;
//     *r = b;
// }

// void RL(musica_no** r) {
//     musica_no *a = *r;
//     musica_no *c = a->dir;
//     musica_no *b = c->esq;
//     c->esq = b->dir;
//     a->dir = b->esq;
//     b->esq = a;
//     b->dir = c;
//     switch(b->bal) {
//     case -1:
//         a->bal = 0;
//         c->bal = 1;
//         break;
//     case 0:
//         a->bal = 0;
//         c->bal = 0;
//         break;
//     case +1:
//         a->bal = -1;
//         c->bal = 0;
//         break;
//     }
//     b->bal = 0;
//     *r = b;  
// }

// int auxCadastra(musica_no **ini, musica *s, int *cresceu){
//     if (*ini == NULL){
//         *ini = criaArvore(s, NULL, NULL);
//         *cresceu = 1;
//         return 1;
//     } 

//     if (s == (*ini)->musica)
//     {
//         return 0;
//     }

//     if (s->id < (*ini)->num)
//     {
//         if (auxCadastra(&(*ini)->esq, s, cresceu))
//         {
//             if (*cresceu)
//             {
//                 switch ((*ini)->bal)
//                 {
//                 case -1:
//                     if ((*ini)->esq->bal == -1)
//                     {
//                         LL(ini);
//                     } else {
//                         LR(ini);
//                     }
//                     *cresceu = 0;
//                     break;
                
//                 case 0:
//                     (*ini)->bal = -1;
//                     *cresceu = 1;
//                     break;
//                 case +1:
//                     (*ini)->bal = 0;
//                     *cresceu = 0;
//                     break;
//                 }
//             }
//         }
//     }

//     if(auxCadastra(&(*ini)->dir, s, cresceu)){
//         if (*cresceu) {
//             switch ((*ini)->bal) {
//             case -1:
//                 (*ini)->bal = 0;
//                 *cresceu = 0;
//                 break;
//             case 0:
//                 (*ini)->bal = +1;
//                 *cresceu = 1;
//                 break;
//             case +1:
//                 if ((*ini)->dir->bal == 1) {
//                     RR(ini);
//                 } else {
//                     RL(ini);
//                 }
//                 *cresceu = 0;
//                 break;
//             }
//         }
//         return 1;
//     } else {
//         return 0;
//     }
// }

void cadastrarMusica(musica_no *ini, musica *s){
    // int cresceu;
    // return auxCadastra(ini, s, &cresceu);

    if (s->id < ini->musica->id)
    {
        if (ini->esq != NULL)
        {
            cadastrarMusica(ini->esq, s);
        } else {
            ini->esq = new musica_no;
            ini->esq->musica = s;
            ini->esq->musica->id = s->id;
            ini->esq->esq = NULL;
            ini->esq->dir = NULL;
        }
        
    } else if (s->id > ini->musica->id)
    {
        if (ini->dir != NULL) {
            cadastrarMusica(ini->dir, s);
        } else
        {
            ini->dir = new musica_no;
            ini->dir->musica = s;
            ini->dir->musica->id = s->id;
            ini->dir->esq = NULL;
            ini->dir->dir = NULL;
        }
        
    }
}

void imprimirListaDeMusicas(musica_no* ini){
    if(ini != NULL) {
        imprimirListaDeMusicas(ini->esq);
        cout << ini->musica->titulo << endl;
        cout << ini->musica->artista << endl;
        cout << ini->musica->album << endl;
        int h, m, s;
        h = (ini->musica->duracao/3600); 
        m = (ini->musica->duracao -(3600*h))/60;
        s = (ini->musica->duracao -(3600*h)-(m*60));
        printf("%d:%d:%d\n",h,m,s);
        printf("------------------------\n");
        imprimirListaDeMusicas(ini->dir);
    }
}

// playlist_no* criaPlaylist(int qtddM, int musicas[], musica_no* listaDeMusicas){
//     int i;
//     musica_no* ini = listaDeMusicas->prox;
//     playlist_no* novaPlaylist = criaListaCircular();
//     for (i = qtddM-1; i >= 0; i--)
//     {
//         while (ini)
//         {
//             if(ini->musica->id == musicas[i]){
//                 playlist_no* p = (playlist_no*) malloc(sizeof(playlist_no));
//                 p->musica = ini->musica;
//                 if (novaPlaylist->prox == novaPlaylist)
//                 {
//                     novaPlaylist->prox = p;
//                     p->prox = novaPlaylist;
//                 } else {
//                     p->prox = novaPlaylist->prox;
//                     novaPlaylist->prox = p;
//                 }
                
//             }
//             ini = ini->prox;
//         }
//         ini = listaDeMusicas->prox;
//     }
//     return novaPlaylist;
// }


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
        cout << "----------" << endl;
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

    playlist_no* lpm = lp->musicas->prox;
    int counterAux = 0;
    while (lpm && counterAux < cont)
    {
        int r = rand() % (cont*2);
        int counter = 0;
        playlist_no* lpms = lpm;
        while (counter < r)
        {
            lpms = lpms->prox;
            counter++;  
        }
        if (lpms->musica == NULL)
        {
            lpms = lpms->prox;
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
    int contadorAux = 0, cont=0;
    while (lp){
        if (strcmp(lp->nome, nome) == 0){
            playlist_no* p = lp->musicas->prox;
            while (p->musica){
                cont++;
                p = p->prox;
            }
            break;
        }
        lp = lp->prox;
    }
    while (lp)
    {
        if (strcmp(lp->nome, nome) == 0)
        {
            playlist_no* p = lp->musicas->prox;
            while (contadorAux < cont){
                if (p->musica == NULL)
                {
                    p = p->prox;
                }
                cout << p->musica->titulo << endl;
                
                p = p->prox;
                contadorAux++;
            }
            return;
        }
        lp = lp->prox;
    }
    cout << "playlist nao encontrada" << endl;
    
}

// void excluirMusica(char* nome, lplaylists_no* play, musica_no* musi) {
//     musica_no* lm = musi->prox;

//     while (lm) {
//         if (strcmp(lm->musica->titulo, nome) == 0)
//         {
//             lm->ant->prox = lm->prox;
//             free(lm);
//             break;
//         }
//         lm = lm->prox;
//     }

//     lplaylists_no* lp = play->prox;
//     playlist_no* p = lp->musicas->prox;
    
//     while (lp)
//     {
//         Musica* m = p->musica;
//         if (strcmp(m->titulo, nome) == 0){
//             free(m);
//             break;
//         } else {
//             p = p->prox;
//         }
//         lp = lp->prox;
//     }
    

// }

int main(){
    srand(time(NULL));
    int opcao = -1;
    musica_no* listaDeMusicas = NULL;
    int counter = 0;
    imprimirListaDeMusicas(listaDeMusicas);

    do
    {
        printMenu();
        cin >> opcao;
        switch (opcao)
        {
        case 1:{
            counter++;
            Musica* p = (Musica*) malloc(sizeof(Musica));
            printf("ID da musica: ");
            cin >> p->id;
            if (cin.fail())
            {
                cout << "digite um número inteiro!" << endl;
                cin.clear();
                cin.ignore();
                break;
            } 
                       
            printf("Titulo da musica: ");
            cin >> p->titulo;
            printf("Artista da musica: ");
            cin >> p->artista;
            printf("Album da musica: ");
            cin >> p->album;

            printf("Duracao da musica: ");
            cin >> p->duracao;
            if (cin.fail())
            {
                cout << "digite um número inteiro!" << endl;
                cin.clear();
                cin.ignore();
                break;
            }
            
            if (counter == 1)
            {
                listaDeMusicas = criaArvore(p, NULL, NULL);
            } else {cadastrarMusica(listaDeMusicas, p);}
            
            break;
        }
            
        case 2:
            imprimirListaDeMusicas(listaDeMusicas);
            break;
        // case 3: {

        //     int qtddMusicasP, i, idPlaylist, check = 0;
        //     char nomePlaylist[MAX_CHAR];
        //     cout << "Quantas musicas deseja inserir? ";
        //     cin >> qtddMusicasP;
        //     if (cin.fail())
        //     {
        //         cout << "digite um número inteiro!" << endl;
        //         cin.clear();
        //         cin.ignore();
        //         break;
        //     }
        //     cout << "Digite os IDs das musicas que deseja inserir: ";
        //     int novaPlaylist[qtddMusicasP];
        //     for (i = 0; i < qtddMusicasP; i++)
        //     {
        //         cin >> novaPlaylist[i];
        //         if (cin.fail())
        //         {
        //             cout << "digite um número inteiro!" << endl;
        //             cin.clear();
        //             cin.ignore();
        //             check = 1;
        //             break;
        //         }
        //     }
        //     if (check == 1)
        //     {
        //         break;
        //     }
            
        //     cout << "Insira o nome da playlist: ";
        //     cin >> nomePlaylist;
        //     cout << "Insira o ID da playlist: ";
        //     cin >> idPlaylist;
        //     if (cin.fail())
        //     {
        //         cout << "digite um número inteiro!" << endl;
        //         cin.clear();
        //         cin.ignore();
        //         break;
        //     }
                        
        //     inserirPlaylist(listaDePlaylists, criaPlaylist(qtddMusicasP, novaPlaylist, listaDeMusicas), idPlaylist, nomePlaylist);
        //     break;

        // }
        // case 4:
        //     cout << "Nomes das playlists: " << endl;
        //     imprimirPlaylists(listaDePlaylists);
        //     break;
        // case 5: {
        //     char nomeShuffle[MAX_CHAR] = "";
        //     cout << "Insira o nome da playlist desejada: ";
        //     cin >> nomeShuffle;
        //     shuffle(nomeShuffle, listaDePlaylists);
        //     break;
        // }
        // case 6: {
        //     char nomeSearch[MAX_CHAR] = "";
        //     cout << "Insira o nome da playlist que deseja ver: ";
        //     cin >> nomeSearch;
        //     imprimirUmaPlaylist(nomeSearch, listaDePlaylists);
        //     break;
        // }
        // case 7: {
        //     char nomeExcluir[MAX_CHAR] = "";
        //     cout << "insira o nome da musica desejada: ";
        //     cin >> nomeExcluir;
        //     excluirMusica(nomeExcluir, listaDePlaylists, listaDeMusicas);
        //     break;
        // }
        default:
            break;
        }
            
        
    } while (opcao != 0);


    return 0;
}