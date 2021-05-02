""""
Descrição: Deve-se implementar um simulador para uma arquitetura simples. As
descrições para o hardware são as seguintes:
• Processador:
• A arquitetura deverá ter um pipeline de 5 estágios, sendo eles:
◦ Busca de instrução;
◦ Decodificação de instrução;
◦ Execução;
◦ Acesso a memória;
◦ Escrita do resultado nos registradores;
"""
""""
movi r1,10
movi r2,5
movi r11,3
sw r1,0(r11) -> 
addi r11,r11,1
addi r1,r1,3
addi r1,r1,r2 -> errado
blt r11,r2,3
movi r11,3
lw r4,1(r11)
movi r1,10 -> movi 1 10 0
addi r11,r11,1 -> addi 11 11 1
add r1,r1,r11 -> add 1 1 11



busca -  decodifica - executa - memoria(executas lw e sw) - registrador(executa operaçoes - as de memoria)
"""
#m
class memoria:
  def __init__(self):
    self.mem = [0] * 100

class registrador:
  def __init__(self):
    self.r = [0] * 32


class pipeline:
  def __init__(self):
    self.pipe = {new_list: "NOOP" for new_list in ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']}
    #{'Busca': None, 'Decodifica': None, 'Executa': None, 'Memoria': None, 'Regist': None}

  def fpipe(self, instrucao, registrador, memoria):
    #instrucao.comando, instrucao.pos1, instrucao.pos2, instrucao.pos3 = fetch(instrucao)
    self.pipelist = ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']
    instrucao.pos1, instrucao.pos2, instrucao.pos3 = instrucao.pos1.replace("r",""), instrucao.pos2.replace("r",""), instrucao.pos3.replace("r","")
      

class instrucao:
  def __init__(self, instrucao):
    self.instrucao = instrucao[0:len(instrucao)-1] #tira o \n
    comando, pos1, pos2, pos3 = fetch(instrucao)
    self.comando = comando
    self.pos1 = pos1
    self.pos2 = pos2
    self.pos3 = pos3

  def operar(self, registrador, memoria):
   #add r1,r2
    if self.comando == "movi":      
      registrador.r[int(self.pos1)] = int(self.pos2)

    elif self.comando == "mov":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)]
  
    elif self.comando == "addi":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] + int(self.pos3)

    elif self.comando == "add":      
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] + registrador.r[int(self.pos3)]

    elif self.comando == "subi":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] - int(self.pos3)

    elif self.comando == "sub":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] - registrador.r[int(self.pos3)]

    elif self.comando == "mul":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] * int(self.pos3)
    
    elif self.comando == "div":
      registrador.r[int(self.pos1)] = registrador.r[int(self.pos2)] / int(self.pos3)

  def memoria(self, instrucao, memoria):
    if self.comando == "sw":
      memoria.mem[int(self.pos2)+registrador.r[int(self.pos3)]] = registrador.r[int(self.pos1)] 

    elif self.comando == "lw":
      registrador.r[int(self.pos1)] = memoria.mem[int(self.pos2)+registrador.r[int(self.pos3)]]
    

  #def executa(self, instrucao, memoria)
  
  ##
  # Atenção aqui: Qualquer alteração feita no actPipeLine irá mudar o pipeline
  # original, caso queria fazer alteração, use um pipeline auxiliar:
  # pipeAux = actPipeLine.copy()
  #
  #elif (self.comando in treeOp): não está funcionando direito
  #se pa nem os outros
  def decodifica(self, actPipeLine):
      pipelist = ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']
      depend = []
      i = 0
      oneOp = ['movi']
      twoOp = ['mov', "addi"]
      treeOp = ['add']
      execute = instrucao(actPipeLine["Executa"])
      mem = instrucao(actPipeLine["Memoria"])
      reg = instrucao(actPipeLine["Regist"])
          
      print(self.comando)
      if (self.comando in oneOp):
          print("a")
          if (execute.pos1 == self.pos1):
              depend.append("Executa")
          if (mem.pos1 == self.pos1):
              depend.append("Memoria")
          if (reg.pos1 == self.pos1):
              depend.append("Regist")
          pipeAux = actPipeLine.copy()
          i = 2
          for item in depend:
             actPipeLine[pipelist[i]] = "NOOP"
             for items in actPipeLine.values():
                 if (i == len(actPipeLine) - 1): # Out of range handle
                     break
                 actPipeLine[pipelist[i+1]] = pipeAux[pipelist[i]] # Move todos os valores da pipeline para a direita
                                                    # começando da posição 1 
                 i += 1
                 
      elif (self.comando in twoOp):
          print("b")
          if (execute.pos1 == self.pos1 or execute.pos1 == self.pos2):
              depend.append("Executa")
          if (mem.pos1 == self.pos1 or mem.pos1 == self.pos2):
              depend.append("Memoria")
          if (reg.pos1 == self.pos1 or reg.pos1 == self.pos2):
              depend.append("Regist")
          pipeAux = actPipeLine.copy()
          i = 2
          for item in depend:
             actPipeLine[pipelist[i]] = "NOOP"
             for items in actPipeLine.values():
                 if (i == len(actPipeLine) - 1): # Out of range handle
                     break
                 actPipeLine[pipelist[i+1]] = pipeAux[pipelist[i]] # Move todos os valores da pipeline para a direita
                                                    # começando da posição 1 
                 i += 1
             
      elif (self.comando in treeOp):
          if (execute.pos1 == self.pos1 or execute.pos1 == self.pos2 or execute.pos1 == self.pos3):
              depend.append("Executa")
          if (mem.pos1 == self.pos1 or mem.pos1 == self.pos2 or mem.pos1 == self.pos3):
              depend.append("Memoria")
          if (reg.pos1 == self.pos1 or reg.pos1 == self.pos2 or reg.pos1 == self.pos3):
              depend.append("Regist")
          pipeAux = actPipeLine.copy()
          i = 2
          print(depend)
          print(pipeAux)
          j = 2
          for item in depend:
             actPipeLine[pipelist[j]] = "NOOP"
             for items in actPipeLine.values():
                 if (i == len(actPipeLine) - 1): # Out of range handle
                     break
                 actPipeLine[pipelist[i+1]] = pipeAux[pipelist[i]] # Move todos os valores da pipeline para a direita
                 # começando da posição 1 
                 i += 1
             print(actPipeLine)
             j+=1
            
 
    
def checkHazard(instrucao, actPipeLine):
    print("checando hazard")
     
    
def fetch(opcode):
  a = []
  if (opcode == "NOOP"):
      a.append("NOOP")
      a.append("None")
      a.append("None")
      a.append("None")
      return a
  b = opcode.find(",")
  space = opcode.find(" ")
  a.append(opcode[0:space]) # instrução
  a.append(opcode[space + 1: b]) # registro
  x = opcode.find('(')
  if (x > 0): # Caso conter '('
      y = opcode.rindex(',', 0, x)
      z = opcode.find(')')
      a.append(opcode[y+1:x]) # valor a ser somado
      a.append(opcode[x+1:z]) # registrador
      return a
  c = opcode.find(",", b + 1)
  if(c == -1):
      a.append(opcode[b+1: len(opcode)]) # valor 1
      a.append("None")
  else:
      a.append(opcode[b+1: c]) # valor 1
      a.append(opcode[c+1: len(opcode)]) # valor 2, se houver
  return a
    
# mov r1,2
def main():
  #a = instrucao
  j = 0 # Será a linha lida do arquivo
  r = registrador()
  m = memoria()
  p = pipeline()
  #a.instrucao = input("digite uma instrução: ")
  f = open("entrada.txt", "r")
  line = f.readlines()
  opTotal = len(line) # Quantidade total de opcodes
  # ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']
  while(not all(value == "NOOP" for value in p.pipe.values()) or j == 0):
    i = 0
    if (j < opTotal):
        a = instrucao(line[j])
    else:
        a.instrucao = "NOOP"
    p.fpipe(a,r,m)
    pAux = p.pipe.copy() # Cria uma cópia da pipeline atual
    p.pipe["Busca"] = a.instrucao # Atualiza Busca
    for items in p.pipe.values(): # Iteração que irá mover os opcodes pelo pipeline
      if (i == len(p.pipelist) - 1): # Out of range handle
          break
      p.pipe[p.pipelist[i+1]] = pAux[p.pipelist[i]] # Move todos os valores da pipeline para a direita
                                                    # começando da posição 1
      i += 1
    decode = instrucao(p.pipe["Decodifica"]) 
    execut = p.pipe["Executa"]
    mem = p.pipe["Memoria"]
    reg = p.pipe["Regist"]
    decode.decodifica(p.pipe)
    pAux = p.pipe.copy() # Atualiza a cópia da pipeline atual
    print("|-----Busca-----||---Decodifica--||----Executa----||----Memoria----||----Regist-----|")
    print(f'|  {p.pipe["Busca"]:13}||  {p.pipe["Decodifica"]:13}||  {p.pipe["Executa"]:13}||  {p.pipe["Memoria"]:13}||  {p.pipe["Regist"]:13}|')
    input()
    j+=1

    """
    #instrucao.operar(a,r,m)
    print("Registrador:")
    print(r.r)
    print("Memoria")
    print(m.mem)
    """
  f.close()  
 
if __name__ == '__main__':
    main()


#print(a)

