#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri May 20 15:36:02 2016

@author: targueriano
"""

from Nodo import Nodo
from RestaUm import RestaUm
from operator import attrgetter
#import numpy

class Busca_largura:
    I = list()
    E = list()


    def buscaLargura(self):
        resta = RestaUm()
        nodo = Nodo(resta.estadoAtual)
        self.E.append(nodo)
        cont = 0
        while(self.E):
            print(cont)
            cont += 1

            nodoAtual = resta.removePrimeiro(self.E)

            if nodoAtual.estado == resta.estadoFinal:
                resta.caminho(nodoAtual)
                return 1
            """
            if numpy.array_equal(nodoAtual.estado,resta.estadoFinal):
                resta.caminho(nodoAtual)
                return 1
            """

            self.I.append(nodoAtual)

            resta.insereNoFinal(nodoAtual, self.I, self.E)
            #verificar metodo collections
            #ordenar E conforme nodo com menor valor (resta.valor())
            self.E.sort(key=attrgetter("valor"))

        return -1




if __name__ == "__main__":
    bl = Busca_largura()
    bl.buscaLargura()



