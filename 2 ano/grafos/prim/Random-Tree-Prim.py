# -*- coding: utf-8 -*-
"""
Alunos: Guilherme Panobianco Ferrari. RA: 112679;
        Stany Helberth de Souza Gomes da Silva. RA: 112683;
        
Dados: A função MSTPrim, receberá apenas uma árvore G, esta função não terá
retorno, ela irá apenas atualizar a lista de adjacência da árvore G, começando
sempre do primeiro vértice (posição 0 da lista de vértices G.V). A função 
randomTreePrim, receberá apenas um inteiro n, que será o número de vértices da
árvore aleatória completa não orientada gerada por ela. O número de vértices 
deverá ser maior ou igual a zero. 
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

# Retorna a posição do menor elemento na lista Q
def ExtractMin(Q):
    if (len(Q) == 0):
        return None
    chaveMin = Q[0].chave
    i = 0
    pos = 0
    for item in Q:
        if (item.chave < chaveMin):
            pos = i
            chaveMin = item.chave
        i += 1
    return pos
    
# Recebe uma árvore G e irá preencher a lista de adjacência desta árvore, utilizando
# Prim, começando do vértice arbitrário 0.
def MSTPrim(G):
    V = len(G.V)
    Q = []
    G.Adj = [[] for i in range(V)]
    if (V == 0):
        return None
    
    for v in G.V:
        v.chave = float('inf')
        v.pai = None
        Q.append(v)
    G.V[0].chave = 0
    Q[0].chave = 0;
    while len(Q) != 0:
        u = Q.pop(ExtractMin(Q))
        for v in Q:
            if (G.adjMatrix[v.index][u.index] < v.chave):
                v.pai = G.V[u.index]
                v.chave = G.adjMatrix[v.index][u.index]
       
    i = 1 # Começaremos do segundo vértice, pois o pai do primeiro é None   
    while i < V:
        vec = G.V[i]
        G.Adj[vec.index].append(vec.pai)
        G.Adj[vec.pai.index].append(vec)
        i += 1

# Gera uma árvore não orientada aleatória com n vértices utilizando o algoritmo
# de Prim.
def randomTreePrim(n):
    G = Graph([], [], n, None)
    G.V = [Vertex(i, float('inf'), None, 'branco') for i in range (n)]
    G.adjMatrix = [[0 for i in range(n)] for j in range(n)]
    
    for u in range(n):
        for v in range(u+1, n):
            w = random.random()
            G.adjMatrix[u][v] = w
            G.adjMatrix[v][u] = w

    MSTPrim(G)
    if (isTree(G) == False):
        return None
    return G

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
    fileKruskal = open("kruskal.txt", "w")
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
        fileKruskal.write("{} {}\n".format(n, media))
    fileKruskal.close()
    print("--- Tempo total: %s seconds ---" % (time.time() - start_time))
    print("Arquivo gerado")

# Gera um arquivo de texto prim.txt para plotar o gráfico com o arquivo
# plot.py
def PrimAssert():
    start_time = time.time()
    print("Gerando arquivo prim.txt")
    filePrim = open("prim.txt", "w")
    for n in [250, 500, 750, 1000, 1250, 1500, 1750, 2000]:
        start_time2 = time.time()
        soma = 0
        for i in range(500):
            G = randomTreePrim(n)
            soma2 = Diameter(G)
            soma += soma2
        media = soma/500
        print("{} {}".format(n, media))
        print("--- Finalizado em %s seconds ---" % (time.time() - start_time2))
        filePrim.write("{} {}\n".format(n, media))
    filePrim.close()
    print("--- Tempo total: %s seconds ---" % (time.time() - start_time))
    print("Arquivo gerado")


'''#-=-=-=-=-=Asserts-=-=-=-=-=-=#'''
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

# Assert da função Diameter:--------------------------------------------------
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
#------------------------------------------------------------------------------

# Assert da função isTree:-----------------------------------------------------
# Assert de um grafo com nenhum vetor
assert(isTree(a1)) == False

# Assert de um grafo com um vetor
assert(isTree(b1)) == True

#Assert de um grafo não conexo cíclico com cinco vetores
assert(isTree(b2)) == False

# Assert de um grafo não conexo com cinco vetores
assert(isTree(a2)) == False

# Assert de um grafo cíclico não conexo com cinco vetores
assert(isTree(c2)) == False

#------------------------------------------------------------------------------
# Assert da função RandomTreeRandomWalk:---------------------------------------
# randomWalkAssert()
# =============================================================================
# Teste realizado:
# Gerando arquivo randomwalk.txt
# --- Finalizado em 1.3042304515838623 seconds ---
# 250 47.052
# --- Finalizado em 2.7159202098846436 seconds ---
# 500 69.104
# --- Finalizado em 4.494464159011841 seconds ---
# 750 85.744
# --- Finalizado em 6.239423751831055 seconds ---
# 1000 101.256
# --- Finalizado em 8.210209608078003 seconds ---
# 1250 111.708
# --- Finalizado em 9.97068738937378 seconds ---
# 1500 125.046
# --- Finalizado em 11.56063723564148 seconds ---
# 1750 134.464
# --- Finalizado em 13.26557445526123 seconds ---
# 2000 142.878
# --- Tempo total: 57.76516008377075 seconds ---
# =============================================================================


# Criando grafo test1 com 3 vértices e criando grafo test2 com 5 vértices
test1 = Graph([], [], 3, None)
test1.V = [Vertex(i, float('inf'), None, 'branco') for i in range(3)]


test2 = Graph([], [], 5, None)
test2.V = [Vertex(i, float('inf'), None, 'branco') for i in range(5)]

# assert de makeSet de test1---------------------------------------------
makeSet(test1.V[0])
makeSet(test1.V[1])
makeSet(test1.V[2])

assert test1.V[0].pai == test1.V[0]
assert test1.V[0].rank == 0
assert test1.V[1].pai == test1.V[1]
assert test1.V[1].rank == 0
assert test1.V[2].pai == test1.V[2]
assert test1.V[2].rank == 0
#------------------------------------------------------------------------

# assert de makeSet de test2---------------------------------------------

makeSet(test2.V[0])
makeSet(test2.V[1])
makeSet(test2.V[2])
makeSet(test2.V[3])
makeSet(test2.V[4])

assert test2.V[0].pai == test2.V[0]
assert test2.V[0].rank == 0
assert test2.V[1].pai == test2.V[1]
assert test2.V[1].rank == 0
assert test2.V[2].pai == test2.V[2]
assert test1.V[2].rank == 0
assert test2.V[3].pai == test2.V[3]
assert test2.V[3].rank == 0
assert test2.V[4].pai == test2.V[4]
assert test2.V[4].rank == 0
#------------------------------------------------------------------------

# assert de union de test1 ----------------------------------------------
union(test1.V[0], test1.V[1])
assert findSet(test1.V[0]) == findSet(test1.V[1]) 
union(test1.V[0], test1.V[2])
assert findSet(test1.V[0]) == findSet(test1.V[2])
union(test1.V[1], test1.V[2])
assert findSet(test1.V[1]) == findSet(test1.V[2])

# assert de union de test2 ----------------------------------------------
union(test2.V[0], test2.V[3])
assert findSet(test2.V[0]) == findSet(test2.V[3]) 
union(test2.V[2], test2.V[4])
assert findSet(test2.V[2]) == findSet(test2.V[4])
union(test2.V[1], test2.V[3])
assert findSet(test2.V[1]) == findSet(test2.V[3])
union(test2.V[0], test2.V[2])
assert findSet(test2.V[0]) == findSet(test2.V[2])
union(test2.V[1], test2.V[2])
assert findSet(test2.V[1]) == findSet(test2.V[2])
#------------------------------------------------------------------------

# assert de link para test1 ---------------------------------------------
makeSet(test1.V[0])
makeSet(test1.V[1])
makeSet(test1.V[2])
link(test1.V[0], test1.V[1])
assert test1.V[0].pai == test1.V[1]
assert test1.V[1].pai == test1.V[1]
assert test1.V[2].pai == test1.V[2]
assert findSet(test1.V[0]) == findSet(test1.V[1])
assert findSet(test1.V[1]) == findSet(test1.V[1])
assert findSet(test1.V[2]) == findSet(test1.V[2])
assert not findSet(test1.V[1]) == findSet(test1.V[2])
assert not findSet(test1.V[0]) == findSet(test1.V[2])
#------------------------------------------------------------------------

# assert de link para test2 ---------------------------------------------
makeSet(test2.V[0])
makeSet(test2.V[1])
makeSet(test2.V[2])
makeSet(test2.V[3])
makeSet(test2.V[4])
link(test2.V[0], test2.V[1])
assert test2.V[0].pai == test2.V[1]
assert test2.V[1].pai == test2.V[1]
assert test2.V[2].pai == test2.V[2]
assert test2.V[3].pai == test2.V[3]
assert test2.V[4].pai == test2.V[4]
assert findSet(test2.V[0]) == findSet(test2.V[1])
assert findSet(test2.V[1]) == findSet(test2.V[1])
assert findSet(test2.V[2]) == findSet(test2.V[2])
assert findSet(test2.V[3]) == findSet(test2.V[3])
assert findSet(test2.V[4]) == findSet(test2.V[4])
assert not findSet(test2.V[1]) == findSet(test2.V[2])
assert not findSet(test2.V[0]) == findSet(test2.V[2])
assert not findSet(test2.V[1]) == findSet(test2.V[4])
assert not findSet(test2.V[2]) == findSet(test2.V[4])
assert not findSet(test2.V[3]) == findSet(test2.V[4])
assert not findSet(test2.V[0]) == findSet(test2.V[2])

# Assert para MSTKruskal-------------------------------------------------------
# Assert para árvore com número de vértices = 5
n = 5

test3 = Graph([], [], n, None)
test3.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]

test3.adjMatrix = np.array(
                [[0., 1., 4., 2., 5.],
                 [0., 0., 3., 6., 3.],
                 [0., 0., 0., 7., 9.],
                 [0., 0., 0., 0., 8.],
                 [0., 0., 0., 0., 0.]])
# Como explicado dentro da função randomTreeKruskal, a matriz de peso só é 
# preenchida na parte de cima, pois, dentro do MSTKruskal, a função np.nonzero()
# irá gerar uma matriz apenas com pesos, evitando assim, executar o sort 
# desnecessariamente

test3.Adj = MSTKruskal(test3)
assert test3.Adj[0][0] == test3.V[1]
assert test3.Adj[0][1] == test3.V[3]
assert test3.Adj[1][0] == test3.V[0]
assert test3.Adj[1][1] == test3.V[2]
assert test3.Adj[1][2] == test3.V[4]
assert test3.Adj[2][0] == test3.V[1]
assert test3.Adj[3][0] == test3.V[0]
assert test3.Adj[4][0] == test3.V[1]

# =============================================================================
#  Árvore gerada e seus respectivos pesos
#            1   3
#         (0)-(1)-(2)
#         2|  3|
#         (3) (4)
# =============================================================================
# Assert para árvore com número de vértices = 0
n = 0
test4 = Graph([], [], n, None)
test4.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
test4.adjMatrix = np.array([])
test4.Adj = MSTKruskal(test4)
assert test4.Adj == []

# Assert para árvore com número de vértices = 1
n = 1
test5 = Graph([], [], n, None)
test5.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
test5.adjMatrix = np.array([])
test5.Adj = MSTKruskal(test5)
assert test5.Adj == [[]]
#------------------------------------------------------------------------------

# Assert do randomTreeKruskal:
# KruskalAssert()
# =============================================================================
# Teste realizado:
# Gerando arquivo kruskal.txt
# 250 37.176
# --- Finalizado em 10.519332647323608 seconds ---
# 500 50.108
# --- Finalizado em 42.102006912231445 seconds ---
# 750 59.114
# --- Finalizado em 91.16993927955627 seconds ---
# 1000 67.386
# --- Finalizado em 161.54000234603882 seconds ---
# 1250 73.93
# --- Finalizado em 254.18537855148315 seconds ---
# 1500 79.474
# --- Finalizado em 358.5312159061432 seconds ---
# 1750 84.816
# --- Finalizado em 486.3889272212982 seconds ---
# 2000 88.86
# --- Finalizado em 656.616391658783 seconds ---
# --- Tempo total: 2061.0531945228577 seconds ---
# Arquivo gerado
# =============================================================================

# Assert da função extractMin e MSTPrim----------------------------------------
# Árvore que será utilizada nos asserts.
n = 5
G = Graph([], [], n, None)
G.V = [Vertex(i, float('inf'), None, 'branco') for i in range (n)]
G.adjMatrix = np.array(
                [[0., 1., 4., 2., 5.],
                 [1., 0., 3., 6., 10.],
                 [4., 3., 0., 7., 9.],
                 [2., 6., 6., 0., 8.],
                 [5., 3., 10., 8., 0.]])

# Assert da função ExtractMin:
G.V[0].chave = 2
G.V[1].chave = 1
G.V[2].chave = 0
G.V[3].chave = 4
G.V[4].chave = 3
Q = G.V.copy()

assert Q.pop(ExtractMin(Q)) == G.V[2]
assert G.V[2].chave == 0

assert Q.pop(ExtractMin(Q)) == G.V[1]
assert G.V[1].chave == 1

assert Q.pop(ExtractMin(Q)) == G.V[0]
assert G.V[0].chave == 2

assert Q.pop(ExtractMin(Q)) == G.V[4]
assert G.V[4].chave == 3

assert Q.pop(ExtractMin(Q)) == G.V[3]
assert G.V[3].chave == 4

assert len(Q) == 0

# Assert da função MSTPrim:
MSTPrim(G)
assert G.Adj[0][0] == G.V[1]
assert G.Adj[0][1] == G.V[3]
assert G.Adj[1][0] == G.V[0]
assert G.Adj[1][1] == G.V[2]
assert G.Adj[1][2] == G.V[4]
assert G.Adj[2][0] == G.V[1]
assert G.Adj[3][0] == G.V[0]
assert G.Adj[4][0] == G.V[1]
# =============================================================================
#  Árvore gerada e seus respectivos pesos
#            1   3
#         (0)-(1)-(2)
#         2|  3|
#         (3) (4)
# =============================================================================

# Assert para árvore com número de vértices = 0
n = 0
test = Graph([], [], n, None)
test.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
test.adjMatrix = np.array([])
MSTPrim(test)
assert test.Adj == []

# Assert para árvore com número de vértices = 1
n = 1
test = Graph([], [], n, None)
test.V = [Vertex(i, float('inf'), None, 'branco') for i in range(n)]
test.adjMatrix = np.array([])
MSTPrim(test)
assert test.Adj == [[]]

# Assert do randomTreePrim:
PrimAssert()
# =============================================================================
# Teste realizado:
# Gerando arquivo prim.txt
# 250 36.486
# --- Finalizado em 12.184503316879272 seconds ---
# 500 50.61
# --- Finalizado em 51.34641790390015 seconds ---
# 750 59.578
# --- Finalizado em 117.56014823913574 seconds ---
# 1000 67.134
# --- Finalizado em 215.8055820465088 seconds ---
# 1250 73.226
# --- Finalizado em 344.4293112754822 seconds ---
# 1500 78.312
# --- Finalizado em 491.4315814971924 seconds ---
# 1750 83.144
# --- Finalizado em 692.9757978916168 seconds ---
# 2000 90.156
# --- Finalizado em 988.3649098873138 seconds ---
# --- Tempo total: 2914.1002531051636 seconds ---
# =============================================================================
