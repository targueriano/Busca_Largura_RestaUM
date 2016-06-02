#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Fri May 20 20:47:03 2016

@author: targueriano
"""
from copy import deepcopy

class Nodo:

    def __init__(self, estado, proximo=None, valor=None):
        self.proximo = proximo
        self.estado = deepcopy(estado)
        self.valor = valor







