/*
 * busca_largura_p.c
 *
 *  Created on: Jun 16, 2016
 *      Author: targueriano
 */
/*
 ============================================================================
 Name        : CRestOne.c
 Author      : targueriano
 Version     : 1.0.16
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//#include "buscaLargura.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define TAM 4500

int inicial[7][7] = {
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 2, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {0, 0, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 0, 0}
};

int alvo[7][7] = {
    {0, 0, 2, 2, 2, 0, 0},
    {0, 0, 2, 2, 2, 0, 0},
    {2, 2, 2, 2, 2, 2, 2},
    {2, 2, 2, 1, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2},
    {0, 0, 2, 2, 2, 0, 0},
    {0, 0, 2, 2, 2, 0, 0}
};


/*
 * DEFINIÇÃO DO NODO
 * Nodo é uma estrutura composta pelo estado (matriz)
 * um valor de distancia com relacao ao estado alvo e
 * um ponteiro para o nodo pai.
 * Lista encadeada
 * Cada novo nodo é inserido no inicio
 */
struct nodo {
    int valor;
    int estado[7][7];
    struct nodo *proximo;

};
typedef struct nodo Nodo;

Nodo* inicializa_nodo(void){
    return NULL;
}

Nodo* criar_nodo(int estado[7][7], Nodo* n, int valor){
    Nodo* filho = (Nodo*) malloc(sizeof(Nodo));
    int i,j;
    for(i = 0; i < 7; i++)
        for(j = 0; j < 7; j++)
            filho->estado[i][j] = estado[i][j];


    filho->valor = valor;
    filho->proximo = n;

    return filho;

}
/*
 DEFINIÇÃO DA LISTA
 * Lista é uma fila construída por meio de uma lista encadeada
 * finalidade: armazenar os nodos
 * O metodo de ordenacao é o selection sort
 */

//typedef int (*comp) (const void*, const void*);
int cmp (Nodo * a,Nodo * b)
{
    /*converte os ponteiros de tipos genericos para os desejados*/
	int* ia = (int*) a->valor;
	int* ib = (int*) b->valor;
	/*Dados os ponteiros de int, faz a comparacao*/
    if (*ia < *ib)
        return -1;
    else if (*ia > *ib)
        return 1;
    else
        return 0;

}

void insere (Nodo* nodo, Nodo* lista[]){
	int i = 0;
	while (lista[i] != NULL) {
		i++;
	}

	lista[i] = nodo;


}

void insere_ordenado(Nodo* nodo, Nodo* lista[] ){
    int i = 0;
    while(lista[i] != NULL ){
        i++;
    }

    lista[i] = nodo;

    qsort(lista, (i+1), sizeof(Nodo*),cmp);

    /*
    int x, y;
    Nodo* aux;
    for (x = 0; x < (i+1); x++) {
        for (y = x + 1; y < (i+1); y++) // sempre 1 elemento à frente
        {
            // se o (x > (x+1)) então o x passa pra frente (ordem crescente)
            //printf("%d\n",lista[x]->valor);
            //printf("%d\n",lista[y]->valor);
            if (lista[x]->valor > lista[y]->valor) {
                aux = lista[x];
                lista[x] = lista[y];
                lista[y] = aux;
            }
        }
    } // fim da ordenação
	*/

}

/*DEFINIÇÃO DE RESTA_UM
 *
 */

int valida (Nodo* lista[], int (*estado)[7] ) {

	int k;
    for (k = 0; lista[k] != NULL; k++) {
        //imprimir(lista[k]->estado);
    	if (arrEquals(estado,lista[k]->estado)){
    		return 0;
    	}

    }
    return 1;
}

void insereNoFinal(Nodo* nodo, Nodo* I[], Nodo* E[]) {
    int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
			#pragma omp parallel num_threads(4)
        	{
				#pragma omp sections
        		{
					if (nodo->estado[i][j] == 2) {
						#pragma omp section
						{
							pulaDireita(i, j, nodo, I, E);
						}
						#pragma omp section
						{
							pulaEsquerda(i, j, nodo, I, E);
						}
						#pragma omp section
						{
							pulaDown(i, j, nodo, I, E);
						}
						#pragma omp section
						{
							pulaUp(i, j, nodo, I, E);
						}
					}
        		}
        	}
        }
    }
    //estadoInicial = (int[][]) E.get(0);
    printf("######Nova camada#######\n");
}

int pulaDireita(int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]) {


    if (origemY > 1 && origemY <= 6) {
        if (nodo->estado[origemX][origemY - 1] == 1 && nodo->estado[origemX][origemY - 2] == 1) {
            Nodo* filho;

        	//regiao critica
		#pragma omp critical
        	{
            		filho = criar_nodo(nodo->estado, nodo, valor(nodo->estado));
        	}

            filho->estado[origemX][origemY] = 1;
            filho->estado[origemX][origemY - 1] = 2;
            filho->estado[origemX][origemY - 2] = 2;
            //imprimir(filho->proximo->estado);

            filho->valor = valor(filho->estado);
            //imprimir(filho->estado);
            if (valida(I, filho->estado) == 1) {
                insere_ordenado(filho,E);
                //printf("%d\n",E->nodo->valor);
                return 1;
            }
        }
    }
    return -1;
}

int pulaEsquerda(int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]) {

    if (origemY >= 0 && origemY < 5) {
        if (nodo->estado[origemX][origemY + 1] == 1 && nodo->estado[origemX][origemY + 2] == 1) {
            Nodo* filho;

        	//regiao critica
			#pragma omp critical
        	{
            	filho = criar_nodo(nodo->estado, nodo, valor(nodo->estado));
        	}

            filho->estado[origemX][origemY] = 1;
            filho->estado[origemX][origemY + 1] = 2;
            filho->estado[origemX][origemY + 2] = 2;
            //imprimir(estado);
            filho->valor = valor(filho->estado);

            //imprimir(filho->estado);
            if (valida(I, filho->estado) == 1) {
                insere_ordenado(filho,E);
                return 1;
            }
        }
    }
    return -1;
}

int pulaUp(int origemX, int origemY, Nodo* nodo, Nodo *I[], Nodo *E[]) {

    if (origemX >= 0 && origemX < 5) {
        if (nodo->estado[origemX + 1][origemY] == 1 && nodo->estado[origemX + 2][origemY] == 1) {
            Nodo* filho;

        	//regiao critica
			#pragma omp critical
        	{
            	filho = criar_nodo(nodo->estado, nodo, valor(nodo->estado));
        	}
            filho->estado[origemX][origemY] = 1;
            filho->estado[origemX + 1][origemY] = 2;
            filho->estado[origemX + 2][origemY] = 2;
            //imprimir(estado);
            filho->valor = valor(filho->estado);

            //imprimir(filho->estado);
            if (valida(I, filho->estado) == 1 ) {
                insere_ordenado(filho,E);
                return 1;
            }
        }
    }
    return -1;
}

int pulaDown(int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]) {

    if (origemX > 1 && origemX <= 6) {
        if (nodo->estado[origemX - 1][origemY] == 1 && nodo->estado[origemX - 2][origemY] == 1) {
            Nodo* filho;

        	//regiao critica
			#pragma omp critical
        	{
            	filho = criar_nodo(nodo->estado, nodo, valor(nodo->estado));
        	}

            filho->estado[origemX][origemY] = 1;
            filho->estado[origemX - 1][origemY] = 2;
            filho->estado[origemX - 2][origemY] = 2;
            //imprimir(estado);
            filho->valor = valor(filho->estado);

            //imprimir(filho->estado);
            if (valida(I, filho->estado) == 1 ) {
                insere_ordenado(filho,E);
                return 1;
            }
        }
    }
    return -1;
}

void imprimir(int (*estado)[7]) {
    int i,j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            printf("%d ",estado[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
Nodo* removePrimeiro(Nodo* lista[]) {
    Nodo* aux = lista[0];
    int i = 0, j = 1;
    while(lista[i] != NULL){
        lista[i] = lista[j];
        i++;
        j++;
    }

    return aux;

}

int vazio(Nodo* lista[]){
    if(lista[0] == NULL)
        return 1;
    else
        return 0;
}

void caminho(Nodo* nodo) {
    printf("###Meta###\n\n");
    Nodo* aux = nodo;
    int cont = 0;
    while (aux != NULL) {
        printf("%d\n",cont++);
        imprimir(aux->estado);
        aux = aux->proximo;
    }
    printf("%d movimentos\n",cont-1);
}

    //heuristica distancia euclidiana
int valor(int (*estado)[7]) { //qto maior o valor, mais distante do estado final está.
    //A busca é efetuada pelo nodo com menor valor
    int valor = 0;
    int i,j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (estado[i][j] != alvo[i][j])
                valor++;
        }
    }
    return valor;
}

int arrEquals (int (*estado1)[7], int (*estado2)[7]){
	int i, j;
	for (i = 0; i < 7; ++i) {
		for (j = 0; j < 7; ++j) {
			if (estado1[i][j] != estado2[i][j])
				return 0;
		}
	}
	return 1;
}
int main(void){


    Nodo* E[TAM];
    Nodo* I[TAM];
    Nodo* nodoAtual;

    int i;
    for (i = 0; i < TAM; i++) {
        E[i]= NULL;
        I[i]= NULL;
    }

    nodoAtual = inicializa_nodo();
    nodoAtual = criar_nodo(inicial, nodoAtual, 33);

    insere_ordenado(nodoAtual,E);
    int cont;
    cont = 0;
    while(!vazio(E)){

        printf("%d\n",cont++);

        nodoAtual = removePrimeiro(E);

        if (arrEquals(nodoAtual->estado, alvo)){
        	caminho(nodoAtual);
        	exit(0);
        }

        insere(nodoAtual,I);
        insereNoFinal(nodoAtual, I, E);
    }

    return 0;

}


