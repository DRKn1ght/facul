import numpy as np
import random
n = 4
adjMatrix = []
arr = np.full((n,n), 0.)
for i in range(n):
        for j in range(i+1, n):
            w = random.random()
            arr[i][j] = w
print(adjMatrix)
print()
print(arr)
e, i, u = 0, 0, 0
print(arr.size, "gadfgadfgadfg")
minimo2 = np.nonzero(arr)
minimo = np.unravel_index(np.argsort(arr, axis=None, kind= "heapsort"), arr.shape)
u = 0
print(minimo2)
while u < arr.size:
  e+=1
  index1 = minimo[0][u]
  index2 = minimo[1][u]
  print(index1 , "-", index2 , ' u: ', u , ' w: ', arr[index1][index2])
  i+=1
  u+=1
arr2 = np.append(arr, [4])
print("------------")
u = 0
while (u < 6):
  index1 = minimo2[0][u]
  index2 = minimo2[1][u]
  print(index1 , "-", index2 , ' u: ', u , ' w: ', arr[index1][index2])
  u+=1
num = 3
top = arr[minimo2]
top2 = np.unravel_index(np.argsort(top, axis=None, kind= "quicksort"), top.shape)
u = 0
print("-=-=-=-=")
print("minimo: ", minimo)
print("-=-=-=-=")
print("minimo2: ", minimo2)
print("top: ", top)
print("top2: ", top2)
k = 0
i = 0
while (k < 6):
    index = top2[0][i]
    u = minimo2[0][index]
    v = minimo2[1][index]
    print(u, v)
    i+=1
    k+=1


#i = int(((matrixSize - V) / 2) + V)
#5 = 25 elementos
#-5 diagonais
#= 20
#20/2 = 10
#10+5 = 15

#4 = 16 elementos
#-4 diagonais 
#= 12
#12/2 = 6
#6+4 = 10