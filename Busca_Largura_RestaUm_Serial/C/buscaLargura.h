/*
 * buscaLargura.h
 *
 *  Created on: May 30, 2016
 *      Author: targueriano
 */

#ifndef BUSCALARGURA_H_
#define BUSCALARGURA_H_

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   buscaLargura.h
 * Author: targueriano
 *
 * Created on May 28, 2016, 2:11 AM
 */

#ifndef BUSCALARGURA_H
#define BUSCALARGURA_H


#ifdef __cplusplus
extern "C" {
#endif

/* Tipo exportado */
/*
* tipo nodo composto por int[][] estado, Nodo* nodo e int valor
*/
typedef struct nodo Nodo;

/* funcoes exportadas */

/*
* funcao criar
* cria um nodo no estado inicial
* instancia ou cria um nodo filho
* o filho aponta para o pai, ou seja, ele eh inserido no inicio da lista
* clonar o estado do pai no estado do filho
*/
Nodo* inicializa_nodo (void);

Nodo* criar_nodo (int estado[7][7], Nodo *nodo, int valor);

/*
interface lista que representa um vetor
dinamico que armazena tipo Nodo
*** logica de uma fila
@targueriano
GCC Debian Stretch GNU/linux
*/


/*interface para resta_um, que eh um tipo de dado especifico
* Autor: targueriano
*/


/*funcoes exportadas
* valida
* imprimir
* insereNoFinal
* pulaDireita
* pulaEsquerda
* pulaUp
* pulaDown
* caminho
* valor
* insere_ordenado
* insere
*/

/*
* valida
* serve para validar se o nodo filho gerado ja foi analisado
* se foi analisado, nao deve ser inserido na lista
*/
int valida (Nodo* I[], int (*estado)[7]);


/*
* imprimir
* apenas imprime num formato de matriz
*/
void imprimir(int (*estado)[7]);

/*
 * Insere sem ordenar
 *
 */
void insere (Nodo* nodo, Nodo* lista[]);

/*
 * insere no final do vetor e
 * ordena com a função qsort()
 */
void insere_ordenado (Nodo* nodo, Nodo* lista[]);

/*
* insereNoFinal
* funcao principal do metodo de busca
* percorrer os lugares vazios para efetuar os saltos qdo possivel
*/
void insereNoFinal (Nodo* nodo, Nodo* I[], Nodo* E[]);

/*
* pulaX
* verifica se o nodo->estado avaliado pode pular para direita
* se pode, entra gera um novo filho, faz o movimento, procura se o estado derivado ja existe
* e por ultimo insere na Lista E
*/

/* pulaDireita*/
int pulaDireita (int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]);
/* pulaEsquerda*/
int pulaEsquerda (int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]);
/* pulaUp*/
int pulaUp (int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]);
/* pulaDown*/
int pulaDown (int origemX, int origemY, Nodo* nodo, Nodo* I[], Nodo* E[]);

/*
* caminho
* percorre a lista encadeada (nodo) qdo a busca encontra o estado final
*
*/
void caminho (Nodo* nodo);

/*
 * remove o primeiro elemento do vetor estatico
 */

Nodo* removePrimeiro (Nodo* lista[]);
/*
* valor
* metodo heuristico que define a distancia entre o estado atual e o estado final
* Quanto maior o valor, mais distante
* o valor = 0 significa <=> estado final
*/
int valor (int (*estado)[7]);

/*
 * verifica se as matrizes sao iguais
 */
int arrEquals(int (*estado1)[7], int (*estado2)[7] );

/*
 * funcao q define o modo de comparacao do qsort
 */
int cmp (Nodo * a,Nodo * b);



#ifdef __cplusplus
}
#endif

#endif /* BUSCALARGURA_H */



#endif /* BUSCALARGURA_H_ */
