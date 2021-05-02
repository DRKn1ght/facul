# -*- coding: utf-8 -*-
"""
Created on Wed Mar 17 17:53:09 2021

@author: Guilherme Panobianco
"""

class Graph:
  def __init__(self, V, Adj):
    self.V = V
    self.Adj = Adj

class Vertex:
  def __init__(self, index, d,f, pai, cor):
    self.index = index
    self.d = d
    self.f = f
    self.pai = pai
    self.cor = cor
    
g = Graph([], [])


g.V = [Vertex(i, float('inf'), None, None, 'branco') for i in range(5)]
g.Adj = [
      [g.V[3], g.V[2]],
      [g.V[0]],
      [g.V[1]],
      [g.V[4]],
      [],
      ]
compList = []
tempo = 0
comp = 0
def resetG(G):
    for i in G.V:
        i.d = float('inf')
        i.pai = None
        i.cor = 'branco'
        
        
def DFS(G):
    global tempo
    global comp
    global compList
    resetG(G)
    for u in g.V:
        if u.cor == 'branco':
            comp += 1
            compList.clear()
            compList.append(u.index)
            DFSVisit(G, u)
            print("Componente", comp, compList);

def DFSVisit(G, u):
    global tempo
    global comp
    global compList
    u.cor = 'cinza'
    tempo = tempo + 1
    u.d = tempo
    for v in G.Adj[u.index]:
        compList.append(v.index)
        if v.cor == 'branco':
            v.pai = u
            DFSVisit(G, v)
    u.cor = 'preto'
    tempo = tempo + 1
    u.f = tempo
            
DFS(g)

print("Componentes:", comp)
for i in range(5):
    print(i, '=', g.V[i].d, '/', g.V[i].f)            
                    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    