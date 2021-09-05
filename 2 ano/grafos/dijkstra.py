from collections import deque
import numpy as np

# Cria a classe do Grafo
class Graph:
  def __init__(self, V, Adj, size, Ciclico):
    self.V = deque()
    self.Adj = deque()
    self.adjMatrix = np.array([], [])
    
# Cria a classe dos Vetores
class Vertex:
  def __init__(self, index, d, pai, cor):
    self.index = index
    self.d = d
    self.pai = pai

def relax(u, v, w):
    if (v.d > u.d + w):
        v.d = u.d + w
        v.pai = u

def extractMin(Q):
    if (len(Q) == 0):
        return None
    dMin = Q[0].d
    i = 0
    pos = 0
    for item in Q:
        if (item.d < dMin):
            pos = i
            dMin = item.d
        i += 1
    return pos
    

def Dijkstra(G):
    Q = []
    S = []
    for v in G.V:
        v.d = float('inf')
        v.pai = None
        Q.append(v)
    Q[0].d = 0;
    while len(Q) != 0:
        u = Q.pop(extractMin(Q))
        S.append(u)
        for v in Q:
            relax(G.V[u.index], G.V[v.index], G.adjMatrix[u.index][v.index])
    
    for v in S:
        print("V:", v.index, "| D:", v.d)
    return S

n = 4
G = Graph([], [], n, None)
G.V = [Vertex(i, float('inf'), None, 'branco') for i in range (n)]
G.adjMatrix = [[float("inf") for i in range(n)] for j in range(n)]
G.Adj = [[1, 2],
         [3],
         [3],
         []]

G.adjMatrix[0][1] = 2
G.adjMatrix[0][2] = 1
G.adjMatrix[1][3] = -5
G.adjMatrix[2][3] = 3

Dijkstra(G)