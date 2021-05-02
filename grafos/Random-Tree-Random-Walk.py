# -*- coding: utf-8 -*-
"""
@author: Guilherme Panobianco
        
Este algoritmo recebe um grafo G, com N vértices, desde que N seja maior
ou igual a zero e calcula o diâmetro.
"""
from collections import deque
import random
# Cria a classe do Grafo
class Graph:
  def __init__(self, V, Adj, Ciclico):
    self.V = deque()
    self.Adj = deque()
    self.Ciclico = Ciclico

# Cria a classe dos Vetores
class Vertex:
  def __init__(self, index, d, pai, cor):
    self.index = index
    self.d = d
    self.pai = pai
    self.cor = cor
# Inicializa G
a1 = Graph([], [], None)
b1 = Graph([], [], None)
c1 = Graph([], [], None)
d1 = Graph([], [], None)
e1 = Graph([], [], None)
f1 = Graph([], [], None)
g1 = Graph([], [], None)
h1 = Graph([], [], None)
i1 = Graph([], [], None)
j1 = Graph([], [], None)
k1 = Graph([], [], None)

# Grafos que não são árvores para ser usado no assert de isTree
a2 = Graph([], [], None)
b2 = Graph([], [], None)
c2 = Graph([], [], None)

# Inicia o Grafo com as listas de adjacências
def iniciaG():
    a1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(0)]
    b1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(1)]
    c1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(2)]
    d1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(3)]
    e1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(4)]
    f1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(5)]
    g1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(6)]
    h1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(7)]
    i1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(8)]
    j1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(9)]
    k1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(10)]
    
    a2.V = [Vertex(i, float('inf'), None, 'branco') for i in range(5)]
    b2.V = [Vertex(i, float('inf'), None, 'branco') for i in range(5)]
    c2.V = [Vertex(i, float('inf'), None, 'branco') for i in range(5)]
    
    a2.Adj = [
        [a2.V[1], a2.V[3]],
        [a2.V[0], a2.V[2]],
        [a2.V[1]],
        [a2.V[0]],
        []
        ]
    
    b2.Adj = [
        [b2.V[1], b2.V[3]],
        [b2.V[0], b2.V[2], b2.V[4]],
        [b2.V[1]],
        [b2.V[0]],
        [b2.V[2]]
        ]
    
    c2.Adj = [
        [c2.V[1], c2.V[2]],
        [c2.V[0], c2.V[2]],
        [c2.V[0], c2.V[1]],
        [c2.V[2]],
        [[]]
        ]

    a1.Adj = [
        []
      ]
    
    b1.Adj = [
        []
        ]
    
    c1.Adj = [
        [c1.V[1]],
        [c1.V[0]]
        ]
    
    d1.Adj = [
        [d1.V[1], d1.V[2]],
        [d1.V[0]],
        [d1.V[0]]
        ]
    
    e1.Adj = [
        [e1.V[1]],
        [e1.V[0], e1.V[3]],
        [e1.V[3]],
        [e1.V[1], e1.V[2]],
        ]
    
    f1.Adj = [
        [f1.V[3], f1.V[2], f1.V[1]],
        [f1.V[0]],
        [f1.V[0]],
        [f1.V[0], f1.V[4]],
        [f1.V[2]]
        ]
    
    g1.Adj = [
        [g1.V[5], g1.V[1]],
        [g1.V[0]],
        [g1.V[5]],
        [g1.V[5]],
        [g1.V[5]],
        [g1.V[0], g1.V[3], g1.V[4], g1.V[2]]
        ]
    
    h1.Adj = [
        [h1.V[3]],
        [h1.V[6]],
        [h1.V[4]],
        [h1.V[0], h1.V[5]],
        [h1.V[5], h1.V[6], h1.V[2]],
        [h1.V[3], h1.V[4]],
        [h1.V[4], h1.V[1]]
        ]
    
    i1.Adj = [
        [i1.V[7], i1.V[1], i1.V[4]],
        [i1.V[0], i1.V[3], i1.V[6], i1.V[5]],
        [i1.V[7]],
        [i1.V[1]],
        [i1.V[0]],
        [i1.V[1]],
        [i1.V[1]],
        [i1.V[0], i1.V[2]]]
    
    j1.Adj = [
        [j1.V[2], j1.V[1]],
        [j1.V[0], j1.V[6], j1.V[3]],
        [j1.V[0], j1.V[4]],
        [j1.V[1]],
        [j1.V[2], j1.V[7]],
        [j1.V[6]],
        [j1.V[1], j1.V[8], j1.V[5]],
        [j1.V[4]],
        [j1.V[6]]
        ]
    
    k1.Adj = [
        [k1.V[1], k1.V[8]],
        [k1.V[0], k1.V[7], k1.V[2]],
        [k1.V[1]],
        [k1.V[5], k1.V[4]],
        [k1.V[3], k1.V[6]],
        [k1.V[7], k1.V[3]],
        [k1.V[4]],
        [k1.V[1], k1.V[5]],
        [k1.V[0], k1.V[9]],
        [k1.V[8]]
        ]

# Reinicializa o grafo G
def resetG(G):
    for i in G.V:
        i.d = float('inf')
        i.pai = None
        i.cor = 'branco'

# Coloca vetor na fila para fazer a busca em largura
def enqueue(Q, v):
    Q.append(v)
    
# Tira da fila o vetor que já foi explorado
def dequeue(Q):
    v = Q.pop()
    return v

# Faz a busca em largura no grafo G iniciando do vértice s e retorna o vértice
# com o maior atributo d obtido.
def BFS(G, s):
    resetG(G)
    s.d = 0
    s.cor = 'cinza'
    maiorD = s
    Q = deque()
    enqueue(Q, s)
    while (len(Q) != 0):
        u = dequeue(Q)
        for v in G.Adj[u.index]:
            if (v.cor == 'branco'):
                v.d = u.d + 1
                if (v.d > maiorD.d):
                    maiorD = v
                v.pai = u
                v.cor = 'cinza'
                enqueue(Q, v)
            else:
                if (u.pai != v):
                    G.Ciclico = True
                elif G.Ciclico == None:
                    G.Ciclico = False
    return maiorD
        
# Calcula e retorna o diâmetro do grafo G. Retorna -1 caso o número de vetores
# for 0.
def Diameter(G):
    if (len(G.V) == 0):
        return -1
    s = G.V[0]
    a = BFS(G, s)
    b = BFS(G, a)
    return b.d

# Adiciona o vértice u ligado em v na lista de adjacência do grafo G
def unit(G, u, v):
    G.Adj[u.index].append(v)
    G.Adj[v.index].append(u)
    
# Devolve True se o grafo G for uma árvore, e False caso contrário
def isTree(G):
    if (len(G.V) == 0):
        return False
    if (G.Ciclico == None):
        BFS(G, G.V[0])
    if (G.Ciclico == True):
        return False
    for v in G.V:
        if(v.cor == 'branco'):
            return False
    return True

# Gera uma árvore não orientada aleatória com n vértices
def RandomTreeRandomWalk(n):
    G = Graph([], [], None)
    G.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
    for i in range(n):
        G.Adj.append([]);
    u = G.V[0]
    u.cor = 'cinza'
    Adj = 0
    while (Adj < n-1):
        randomNum = random.randrange(n)
        v = G.V[randomNum]
        if (v.cor == 'branco'):
            unit(G, u, v)
            v.cor = 'cinza'
            Adj += 1
        u = v
    if (isTree(G) == False):
        return None
    return G

# Gera um arquivo de texto randomwalk.txt para plotar o gráfico com o arquivo
# plot.py
def randomWalkAssert():
    print("Gerando arquivo randomwalk.txt")
    fileRandomTreeWalk = open("randomwalk.txt", "w")
    for n in [250, 500, 750, 1000, 1250, 1500, 1750, 2000]:
        soma = 0
        for i in range(500):
            G = RandomTreeRandomWalk(n)
            soma += Diameter(G)
        media = soma/500
        print("{} {}".format(n, media))
        fileRandomTreeWalk.write("{} {}\n".format(n, media))
    fileRandomTreeWalk.close()
    print("Arquivo gerado")
    
# Inicia todos os grafos
iniciaG()

# Assert da função BFS:
BFS(h1, h1.V[0])
assert(h1.V[0].d) == 0
assert(h1.V[1].d) == 5
assert(h1.V[2].d) == 4
assert(h1.V[3].d) == 1
assert(h1.V[4].d) == 3
assert(h1.V[5].d) == 2
assert(h1.V[6].d) == 4

BFS(j1, j1.V[5])
assert(j1.V[0].d) == 3
assert(j1.V[1].d) == 2
assert(j1.V[2].d) == 4
assert(j1.V[3].d) == 3
assert(j1.V[4].d) == 5
assert(j1.V[5].d) == 0
assert(j1.V[6].d) == 1
assert(j1.V[7].d) == 6

# Assert da função Diameter:
# Assert de grafo com nenhum vetor
assert(Diameter(a1)) == -1

# Assert de grafo com um vetor
assert(Diameter(b1)) == 0

# Assert de grafo com dois vetores
assert(Diameter(c1)) == 1

# Assert de grafo com três vetores
assert(Diameter(d1)) == 2

# Assert de grafo com quatro vetores
assert(Diameter(e1)) == 3

# Assert de grafo com cinco vetores
assert(Diameter(f1)) == 3

# Assert de grafo com seis vetores
assert(Diameter(g1)) == 3

# Assert de grafo com sete vetores
assert(Diameter(h1)) == 5

# Assert de grafo com oito vetores
assert(Diameter(i1)) == 4

# Assert de grafo com nove vetores
assert(Diameter(j1)) == 6

# Assert de grafo com dez vetores
assert(Diameter(k1)) == 8

# Assert da função isTree:
# Assert de um grafo com nenhum vetor
assert(isTree(a1)) == False

# Assert de um grafo com um vetor
assert(isTree(b1)) == True

# Assert de um grafo não conexo com cinco vetores
assert(isTree(a2)) == False

# Assert de um grafo cíclico com cinco vetores
assert(isTree(b2)) == False

# Assert de um grafo cíclico não conexo com cinco vetores
assert(isTree(c2)) == False

randomWalkAssert()