#! /usr/bin/python
# -*- coding: utf-8 -*-
"""
Created on Fri May 20 21:06:29 2016

@author: targueriano

 * 0 => espaco nao acessivel
 * 1 => espaco ocupado por uma peca
 * 2 => espaco sem peca
 * @author targueriano
"""

from Nodo import Nodo
#import numpy

class RestaUm:

    estadoInicial = [[0, 0, 1, 1, 1, 0, 0], [0, 0, 1, 1, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 2, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1], [0, 0, 1, 1, 1, 0, 0], [0, 0, 1, 1, 1, 0, 0]]

    estadoAtual = [[0, 0, 1, 1, 1, 0, 0], [0, 0, 1, 1, 1, 0, 0],
    [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 2, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1], [0, 0, 1, 1, 1, 0, 0], [0, 0, 1, 1, 1, 0, 0]]

    estadoFinal = [[0, 0, 2, 2, 2, 0, 0], [0, 0, 2, 2, 2, 0, 0],
    [2, 2, 2, 2, 2, 2, 2], [2, 2, 2, 1, 2, 2, 2],
    [2, 2, 2, 2, 2, 2, 2], [0, 0, 2, 2, 2, 0, 0], [0, 0, 2, 2, 2, 0, 0]]



    def valida(self, I, estado):
        for i in range(len(I)):
            if estado == I[i].estado:
                return 0
            """
            if numpy.array_equal(estado, I[i].estado):
                return 0
            """
        return 1


    def insereNoFinal(self, nodo, I, E):
        """
        saltar pedra com lugar vazio
        up, down, left and right
        percorrer matriz para buscar lugar vazio = 2
        imprimir(estado);
        """

        for i in range(7):
            for j in range(7):
                if nodo.estado[i][j] == 2:
                    self.pulaDireita(i, j, nodo, I, E)
                    self.pulaEsquerda(i, j, nodo, I, E)
                    self.pulaDown(i, j, nodo, I, E)
                    self.pulaUp(i, j, nodo, I, E)
        print("######Nova camada#######")


    def pulaDireita(self, origemX, origemY, nodo, I, E):

        if origemY > 1 and origemY <= 6:
            if nodo.estado[origemX][origemY - 1] == 1 and nodo.estado[origemX][origemY - 2] == 1:
                filho = Nodo(nodo.estado, nodo)
                #filho.proximo = nodo
                filho.estado[origemX][origemY] = 1
                filho.estado[origemX][origemY - 1] = 2
                filho.estado[origemX][origemY - 2] = 2
                filho.valor = self.valor(filho.estado)
                if self.valida(I, filho.estado) == 1 :
                    E.append(filho)
                    return 1

        return -1


    def pulaEsquerda(self, origemX, origemY, nodo, I, E):

        if origemY >= 0 and origemY < 5:
            if nodo.estado[origemX][origemY + 1] == 1 and nodo.estado[origemX][origemY + 2] == 1:
                filho = Nodo(nodo.estado, nodo)
                #filho.proximo = nodo
                filho.estado[origemX][origemY] = 1
                filho.estado[origemX][origemY + 1] = 2
                filho.estado[origemX][origemY + 2] = 2
                filho.valor = self.valor(filho.estado)
                if self.valida(I, filho.estado) == 1 :
                    E.append(filho)
                    return 1

        return -1

    def pulaUp(self, origemX, origemY, nodo, I, E):

        if origemX >= 0 and origemX < 5:
            if nodo.estado[origemX + 1][origemY] == 1 and nodo.estado[origemX + 2][origemY] == 1:
                filho = Nodo(nodo.estado, nodo)
                #filho.proximo = nodo
                filho.estado[origemX][origemY] = 1 #posicao vazia fica com peca
                filho.estado[origemX + 1][origemY] = 2 #posicao com peca fica vazia
                filho.estado[origemX + 2][origemY] = 2
                filho.valor = self.valor(filho.estado)

                if self.valida(I, filho.estado) == 1 :
                    E.append(filho)
                    return 1

        return -1


    def pulaDown(self, origemX, origemY, nodo, I, E):

        if origemX > 1 and origemX <= 6:
            if nodo.estado[origemX - 1][origemY] == 1 and nodo.estado[origemX - 2][origemY] == 1:
                filho = Nodo(nodo.estado, nodo)
                #filho.proximo = nodo
                filho.estado[origemX][origemY] = 1 #posicao vazia fica com peca
                filho.estado[origemX - 1][origemY] = 2 #posicao com peca fica vazia
                filho.estado[origemX - 2][origemY] = 2
                filho.valor = self.valor(filho.estado)
                if self.valida(I, filho.estado) == 1 :
                    E.append(filho)
                    return 1

        return -1


    def imprimir(self, estado):
        for i in range(7):
            for j in range(7):
                print estado[i][j],

            print("")

        print("")


    def removePrimeiro(self, E):
        #nodoAtual = E[0]
        #del E[0]
        return E.pop(0)
        #return nodoAtual


    def caminho(self, nodo):
        print("###Meta###")
        cdef int cont = 0
        aux = nodo
        #cont = 0
        while (aux):
            cont += 1
            print(cont)
            self.imprimir(aux.estado)
            aux = aux.proximo

        print cont - 1, ' movimentos'


    #heuristica
    def valor(self, estado):
        # qto maior o valor, mais distante do estado final está.
        #A busca é efetuada pelo nodo com menor valor
        cdef int valor = 0
        cdef int i
        cdef int j
        for i in range(7):
            for j in range(7):
                if estado[i][j] != self.estadoFinal[i][j]:
                    valor += 1


        return valor


