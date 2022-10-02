import numpy as np
def read_data(): 
  old_elo = []
  new_elo = []
  with open("data.txt", "r") as file:
    for line in file:
      line = line.split()
      old_elo.append(int(line[0]))
      new_elo.append(int(line[1]))
  return old_elo, new_elo

def quantizar(old_elo, new_elo):
  for i in range(len(old_elo)):
    if old_elo[i] > 2800:
      old_elo[i] = [old_elo[i],0]
    elif old_elo[i] > 2750 and old_elo[i] <= 2800:
      old_elo[i] = [old_elo[i],1]  
    elif old_elo[i] > 2700 and old_elo[i] <= 2750:
      old_elo[i] = [old_elo[i],2]  
    elif old_elo[i] > 2650 and old_elo[i] <= 2700:
      old_elo[i] = [old_elo[i],3] 
    elif old_elo[i] > 2600 and old_elo[i] <= 2650:
      old_elo[i] = [old_elo[i],4]       
    elif old_elo[i] > 2550 and old_elo[i] <= 2600:
      old_elo[i] = [old_elo[i],5]   
    elif old_elo[i] > 2500 and old_elo[i] <= 2550:
      old_elo[i] = [old_elo[i],6]      
    elif old_elo[i] > 2450 and old_elo[i] <= 2500:
      old_elo[i] = [old_elo[i],7]      
    elif old_elo[i] < 2450:
      old_elo[i] = [old_elo[i],8]       
      
  for i in range(len(new_elo)):
    if new_elo[i] > 2800:
      new_elo[i] = [new_elo[i],0]
    elif new_elo[i] > 2750 and new_elo[i] <= 2800:
      new_elo[i] = [new_elo[i],1]  
    elif new_elo[i] > 2700 and new_elo[i] <= 2750:
      new_elo[i] = [new_elo[i],2]  
    elif new_elo[i] > 2650 and new_elo[i] <= 2700:
      new_elo[i] = [new_elo[i],3] 
    elif new_elo[i] > 2600 and new_elo[i] <= 2650:
      new_elo[i] = [new_elo[i],4]       
    elif new_elo[i] > 2550 and new_elo[i] <= 2600:
      new_elo[i] = [new_elo[i],5]   
    elif new_elo[i] > 2500 and new_elo[i] <= 2550:
      new_elo[i] = [new_elo[i],6]      
    elif new_elo[i] > 2450 and new_elo[i] <= 2500:
      new_elo[i] = [new_elo[i],7]      
    elif new_elo[i] < 2450:
      new_elo[i] = [new_elo[i],8]           
  return old_elo, new_elo    

def create_matrix(old_elo, new_elo):
  matrix = np.zeros((9, 9))
  prob_t0 = []
  prob_t1 = []     
  for i in range(len(old_elo)):
    matrix[old_elo[i][1]][new_elo[i][1]] += 1
  print(matrix)  
  print("\n-=-=-=-=\n")

  # Probabilidade de começar em t1
  for row in matrix.T:
    s = sum(row)
    prob_t1.append(s/100)    
  for row in matrix:
    s = sum(row)
    # Probabilidade de começar em t2
    prob_t0.append(s/100)
    if s > 0:
      row[:] = [f/s for f in row]   
  return matrix, prob_t0, prob_t1  

  
def main():
  np.set_printoptions(edgeitems=30, linewidth=100000, suppress=True, precision = 5)  
  old_elo, new_elo = read_data()
  old_elo, new_elo = quantizar(old_elo, new_elo)
  matrix, prob_t0, prob_t1 = create_matrix(old_elo, new_elo)
  
  matrix2 = np.linalg.matrix_power(matrix, 2)
  print(matrix)
  print("\n-=-=-=-=\n")
  print(matrix2)
  #Probabilidade sair de H em t1 e ir para C em t2 
  print("\nProbabilidade sair de H em t1 e ir para C em t2 é = ", prob_t1[7] * matrix2[7][5])

if __name__ == "__main__":
  main()
