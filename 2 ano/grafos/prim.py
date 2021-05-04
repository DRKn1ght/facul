# -*- coding: utf-8 -*-
"""

        
Dados: Será utilizado lista de adjacência para o random Kruskal. MSTKruskal,
por sua vez, retornará uma lista de adjacência. A matriz não é preenchida completamente,
apenas na parte de cima (isso é melhor visualizado no Assert para MSTKruskal),
para otimizar o tempo de execução. O número de vértices deverá ser maior ou igual
a zero.
"""
import time
from collections import deque
import random
import numpy as np

# Cria a classe do Grafo
class Graph:
  def __init__(self, V, Adj, size, Ciclico):
    self.V = deque()
    self.Adj = deque()
    self.adjMatrix = np.array([], [])
    self.Ciclico = Ciclico
# Cria a classe dos Vetores
class Vertex:
  def __init__(self, index, d, pai, cor):
    self.index = index
    self.d = d
    self.pai = pai
    self.cor = cor
    self.rank = 0
    self.chave = float('inf')
    
# Inicializa G
a1 = Graph([], [], 0, None)
b1 = Graph([], [], 1, None)
c1 = Graph([], [], 2, None)
d1 = Graph([], [], 3, None)
e1 = Graph([], [], 4, None)
f1 = Graph([], [], 5, None)
g1 = Graph([], [], 6, None)
h1 = Graph([], [], 7, None)
i1 = Graph([], [], 8, None)
j1 = Graph([], [], 9, None)
k1 = Graph([], [], 10, None)

# Grafos que não são árvores para ser usado no assert de isTree
a2 = Graph([], [], 5,  None)
b2 = Graph([], [], 5, None)
c2 = Graph([], [], 5, None)

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
    v = Q.popleft()
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
    G = Graph([], [], n, None)
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
    return G

# Inicializa o set do vértice x
def makeSet(x):
    x.pai = x
    x.rank = 0
    
# Une os vértices x e y
def union(x, y):
    link(findSet(x), findSet(y))

# Identifica o pai entre os vértices x e y
def link(x, y):
    if x.rank > y.rank:
        y.pai = x
    else:
        x.pai = y
        if x.rank == y.rank:
            y.rank = y.rank + 1
            
# Retorna o pai do conjunto que contém o vértice x
def findSet(x):
    if x != x.pai:
        x.pai = findSet(x.pai)
    return x.pai

# Recebe uma árvore e retorna uma lista de adjacência, utilizando a matriz
# de adjacências da árvore dada.
def MSTKruskal(G):
    V = len(G.V)
    A = [[] for i in range(V)]
    i, e = 0, 0
    for v in G.V:
        makeSet(v)
           
    # A função argsort irá retornar os índices dos valores em ordem não decrescente
    # que estão na matriz G.adjMatrix
    # A função unravel_index irá converter a lista gerada pelo argsort 
    # em uma tupla de arrays.
    # Foi utilizado "mergesort" em kind pois é estável.
    #https://numpy.org/doc/stable/reference/generated/numpy.sort.html
    
    nMatrix = np.nonzero(G.adjMatrix)
    adjFilter = G.adjMatrix[nMatrix]
    sortedMatrix = np.unravel_index(np.argsort(adjFilter, axis=None, kind= "mergesort"), adjFilter.shape)
    while e < V - 1:
        index = sortedMatrix[0][i]
        u = nMatrix[0][index]
        v = nMatrix[1][index]
        i += 1
        if findSet(G.V[u]) != findSet(G.V[v]):
            e += 1
            A[u].append(G.V[v])
            A[v].append(G.V[u])
            union(G.V[u], G.V[v])
    return A

# Gera uma árvore não orientada aleatória com n vértices utilizando o algoritmo
#de Kruskal.
def randomTreeKruskal(n):
    G = Graph([], [], n, None)
    G.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
    # Inicializa a matriz vazia com n colunas e n linhas, do tipo float
    G.adjMatrix = np.full((n,n), 0.)

    # Neste for, a matriz será preenchida apenas na parte diagonal para cima,
    # a parte da diagonal para baixo, que seria G.adjMatrix[v][u], não será
    # modificada, pois não será lida no MSTKruskal.
    for u in range(n):
        for v in range(u+1, n):
            w = random.random()
            G.adjMatrix[u][v] = w

    G.Adj = MSTKruskal(G)
    if (isTree(G) == False):
        return None
    return G

def ExtractMin(Q):
    if (Q[0].chave == 0):
        return 0
    chaveMin = Q[0].chave
    #secMin = float('inf')
    i = 0
    j = 0
    for item in Q:
        if (item.chave < chaveMin):
            j = i
            chaveMin = item.chave
        #elif (item.chave < secMin):
        #    secMin = item.chave
        i += 1
        
    #print("min:", chaveMin, "secmin:", secMin)
    return j
    
def MSTPrim(G, s):
    i = 1
    V = len(G.V)
    Q = []
    G.Adj = [[] for i in range(V)]
    for v in G.V:
        v.chave = float('inf')
        v.pai = None
        Q.append(v)
    s.chave = 0
    Q[0].chave = 0;
    #print(G.adjMatrix)
    while len(Q) != 0:
        u = Q.pop(ExtractMin(Q))
        for v in Q:
            #print(u.index, v.index, G.adjMatrix[v.index][u.index])
            if (G.adjMatrix[v.index][u.index] < v.chave):
                v.pai = G.V[u.index]
                v.chave = G.adjMatrix[v.index][u.index]
                #print(v.pai.index, "pai:", G.V[u.index].index, "chave:", v.chave)   
    while i < V:
        vec = G.V[i]
        G.Adj[vec.index].append(vec.pai)
        G.Adj[vec.pai.index].append(vec)
        #print(vec.index, ",", vec.pai.index, "w:", vec.chave)
        #print(vec.pai.index, ",", vec.index, "w:", vec.chave)
        i += 1
        
def randomTreePrim(n):
    G = Graph([], [], n, None)
    G.V = [Vertex(i, float('inf'), None, 'branco') for i in range (n)]
    G.adjMatrix = [[0 for i in range(n)] for j in range(n)]
    
    for u in range(n):
        for v in range(u+1, n):
            w = random.random()
            G.adjMatrix[u][v] = w
            G.adjMatrix[v][u] = w

    s = G.V[0]
    MSTPrim(G, s)
    if (isTree(G) == False):
        print("Não é árvore")
    return G

#randomTreePrim(5)
# Gera um arquivo de texto randomwalk.txt para plotar o gráfico com o arquivo
# plot.py
def randomWalkAssert():
    start_time = time.time()
    print("Gerando arquivo randomwalk.txt")
    fileRandomTreeWalk = open("randomwalk.txt", "w")
    for n in [250, 500, 750, 1000, 1250, 1500, 1750, 2000]:
        start_time2 = time.time()
        soma = 0
        for i in range(500):
            G = RandomTreeRandomWalk(n)
            soma2 = Diameter(G)
            soma += soma2
        media = soma/500
        print("--- Finalizado em %s seconds ---" % (time.time() - start_time2))
        print("{} {}".format(n, media))
        fileRandomTreeWalk.write("{} {}\n".format(n, media))
    fileRandomTreeWalk.close()
    print("--- Tempo total: %s seconds ---" % (time.time() - start_time))
    print("Arquivo gerado")
    
# Gera um arquivo de texto kruskal.txt para plotar o gráfico com o arquivo
# plot.py
def KruskalAssert():
    start_time = time.time()
    print("Gerando arquivo kruskal.txt")
    fileRandomTreeWalk = open("kruskal.txt", "w")
    for n in [250, 500, 750, 1000, 1250, 1500, 1750, 2000]:
        start_time2 = time.time()
        soma = 0
        for i in range(500):
            G = randomTreeKruskal(n)
            soma2 = Diameter(G)
            soma += soma2
        media = soma/500
        print("{} {}".format(n, media))
        print("--- Finalizado em %s seconds ---" % (time.time() - start_time2))
        fileRandomTreeWalk.write("{} {}n".format(n, media))
    fileRandomTreeWalk.close()
    print("--- Tempo total: %s seconds ---" % (time.time() - start_time))
    print("Arquivo gerado")

def PrimAssert():
    start_time = time.time()
    print("Gerando arquivo prim.txt")
    fileRandomTreeWalk = open("kruskal.txt", "w")
    for n in [250, 500, 750, 1000, 1250, 1500, 1750, 2000]:
        start_time2 = time.time()
        soma = 0
        for i in range(10):
            G = randomTreePrim(n)
            soma2 = Diameter(G)
            soma += soma2
        media = soma/500
        print("{} {}".format(n, media))
        print("--- Finalizado em %s seconds ---" % (time.time() - start_time2))
        fileRandomTreeWalk.write("{} {}n".format(n, media))
    fileRandomTreeWalk.close()
    print("--- Tempo total: %s seconds ---" % (time.time() - start_time))
    print("Arquivo gerado")


PrimAssert()