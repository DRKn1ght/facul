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
  def __init__(self, indice, pai, cor):
    self.indice = indice
    self.pai = pai
    self.cor = cor
    
g = Graph([], [])

g.V = [Vertex(i, None, None) for i in range(5)]
g.Adj = [
        [g.V[1], g.V[2]],
        [g.V[0], g.V[3]],
        [g.V[0], g.V[3]],
        [g.V[2], g.V[1]],
        [g.V[3]]
        ]

def enqueue(Q, v):
    Q.append(v)
    
def dequeue(Q):
    v = Q[0]
    Q.pop(0)
    return v


        
def bfs(G, s):
    s.pai = None
    s.cor = 'vermelho'
    Q = []
    enqueue(Q, s)
    while (len(Q) != 0):
        u = dequeue(Q)
        for v in G.Adj[u.indice]:
            if (v.cor == u.cor):
                return False
            if (v.cor == None):
                v.pai = u
                if (v.pai.cor == 'vermelho'):
                    v.cor = 'azul'
                else:
                    v.cor = 'vermelho'
                enqueue(Q, v)
    return True

print(bfs(g, g.V[0]))


def findP(G, s, v):
    if v == s:
        print(s.indice)
    elif v.pai == None:
        print("Nao ha caminho")
    else:
        findP(G, s, v.pai)
        print(v.indice)
    
'''findP(g, g.V[0], g.V[7])'''































