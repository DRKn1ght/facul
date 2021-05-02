# -*- coding: utf-8 -*-
"""
Created on Wed Mar 17 12:16:13 2021

@author: Guilherme Panobianco
"""

class Graph:
  def __init__(self, V, Adj):
    self.V = V
    self.Adj = Adj

class Vertex:
  def __init__(self, indice, d, pai, cor):
    self.indice = indice
    self.d = d
    self.pai = pai
    self.cor = cor
    
g = Graph([], [])

g.V = [Vertex(i, float('inf'), None, 'branco') for i in range(8)]

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
def enqueue(Q, v):
    Q.append(v)
    
def dequeue(Q):
    v = Q[0]
    Q.pop(0)
    return v


        
def bfs(G, s):
    s.d = 0
    s.pai = None
    s.cor = 'cinza'
    Q = []
    enqueue(Q, s)
    while (len(Q) != 0):
        u = dequeue(Q)
        for v in G.Adj[u.indice]:
            if (v.cor == 'branco'):
                v.d = u.d + 1
                v.pai = u
                v.cor = 'cinza'
                enqueue(Q, v)
        u.cor = 'preto'

bfs(g, g.V[0])


def findP(G, s, v):
    if v == s:
        print(s.indice)
    elif v.pai == None:
        print("Nao ha caminho")
    else:
        findP(G, s, v.pai)
        print(v.indice)
    
'''findP(g, g.V[0], g.V[7])'''

for i in range(8):
    print(i, " = ", g.V[i].d)































