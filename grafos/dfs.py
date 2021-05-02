# -*- coding: utf-8 -*-
"""
Created on Wed Mar 17 16:48:33 2021

@author: Guilherme Panobianco
"""

class Graph:
  def __init__(self, V, Adj):
    self.V = V
    self.Adj = Adj

class Vertex:
  def __init__(self, indice, d, f, pai, cor):
    self.indice = indice
    self.d = d
    self.f = f
    self.pai = pai
    self.cor = cor
    
g = Graph([], [])

g.V = [Vertex(i, None, None, None, 'branco') for i in range(8)]
g.Adj = [
      [g.V[1]],
      [g.V[0], g.V[2]],
      [g.V[1], g.V[3]],
      [g.V[2], g.V[4], g.V[5]],
      [g.V[3], g.V[6], g.V[7]],
      [g.V[3], g.V[6]],
      [g.V[5], g.V[4], g.V[7]],
      [g.V[4], g.V[6]]
      ]

tempo = 0

def DFS(G):
    global tempo
    for u in g.V:
        if u.cor == 'branco':
            DFSVisit(G, u)

def DFSVisit(G, u):
    global tempo
    u.cor = 'cinza'
    tempo = tempo + 1
    u.d = tempo
    for v in G.Adj[u.indice]:
        if v.cor == 'branco':
            v.pai = u
            DFSVisit(G, v)
            print(u.indice, "=", v.indice)
    u.cor = 'preto'
    tempo = tempo + 1
    u.f = tempo
            
DFS(g)

for i in range(8):
    print(i, '=', g.V[i].d, '/', g.V[i].f)            
            