#Sergio Alvarez RA115735
#Guilherme Ferrari RA112679
class memoria:
  def __init__(self):
    self.mem = [0] * 100

class registrador:
  def __init__(self):
    self.r = [0] * 32
    self.pc = 0
    self.sp = 0
    self.ra = 0


class pipeline:
  def __init__(self):
    self.pipe = {new_list: "NOOP" for new_list in ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']}

  def fpipe(self, instrucao, registrador, memoria):
    self.pipelist = ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']
    instrucao.pos1, instrucao.pos2, instrucao.pos3 = instrucao.pos1.replace("r",""), instrucao.pos2.replace("r",""), instrucao.pos3.replace("r","")
      

class instrucao:
  def __init__(self, instrucao):
    self.instrucao = instrucao.replace('\n', '') #tira o \n
    comando, pos1, pos2, pos3 = fetch(instrucao)
    self.comando = comando
    self.pos1 = pos1
    self.pos2 = pos2
    self.pos3 = pos3

  def operar(self, registrador, memoria):
    self.pos1, self.pos2, self.pos3 = self.pos1.replace("r",""), self.pos2.replace("r",""), self.pos3.replace("r","")

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

    elif self.comando == "lw":
      registrador.r[int(self.pos1)] = memoria.mem[int(self.pos2)+registrador.r[int(self.pos3)]]

  def memoria(self, registrador, memoria):
    self.pos1, self.pos2, self.pos3 = self.pos1.replace("r",""), self.pos2.replace("r",""), self.pos3.replace("r","")
    if self.comando == "sw":
      memoria.mem[int(self.pos2)+registrador.r[int(self.pos3)]] = registrador.r[int(self.pos1)] 


  def desvios(self, registrador, memoria, j, pipe):
    self.pos1, self.pos2, self.pos3 = self.pos1.replace("r",""), self.pos2.replace("r",""), self.pos3.replace("r","")

    if self.comando == "blt":
      if registrador.r[int(self.pos1)] < registrador.r[int(self.pos2)]:
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        return int(self.pos3) - 1, pipe

    if self.comando == "bgt":
      if registrador.r[int(self.pos1)] < registrador.r[int(self.pos2)]:
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        return int(self.pos3) - 1, pipe

    if self.comando == "beq":
      if registrador.r[int(self.pos1)] == registrador.r[int(self.pos2)]:
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        return int(self.pos3) - 1, pipe

    if self.comando == "j":
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        print('1', self.pos1)
        return int(self.pos1) - 1, pipe

    if self.comando == "jr":
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        return registrador.r[int(self.pos1)] - 1, pipe

    if self.comando == "jal":
        pipe['Busca'] = 'NOOP'
        pipe['Decodifica'] = 'NOOP'
        registrador.ra = int(self.pos1)
        return registrador.r[int(self.pos1)] - 1, pipe

    else:
      return j, pipe  

  def decodifica(self, actPipeLine, memoria, registrador, pc):
      pipelist = ['Busca', 'Decodifica', 'Executa', 'Memoria', 'Regist']
      depend = 0
      i = 0
      var = 1
      depend = checkHazard(self, actPipeLine)
      if (depend == 0):
        print("Sem hazard")
        return
      else:
        print("Tratando hazard", depend)
      i = 2
      pipeAux = actPipeLine.copy()
      while (var < depend):
        i = 2
        #executa instrucoes
        mem = instrucao(actPipeLine["Memoria"])
        instrucao.memoria(mem, registrador, memoria)
        reg = instrucao(actPipeLine["Regist"])  
        instrucao.operar(reg, registrador, memoria)
        exe = instrucao(actPipeLine["Executa"])
        var, actPipeLine = instrucao.desvios(exe, registrador, memoria, var, actPipeLine) 
        printPipe(actPipeLine, registrador, memoria)
        actPipeLine[pipelist[2]] = "NOOP"
        for items in actPipeLine.values():
          if (i == len(actPipeLine) - 1): # Out of range handle
            break
          actPipeLine[pipelist[i+1]] = pipeAux[pipelist[i]] # Move todos os valores da pipeline para a direita
                                                            # começando da posição 1 
          i += 1
        var+=1
        input()
        pipeAux = actPipeLine.copy()
            
 
# Retorna o número de identificação do hazard
# Caso retornar 1, terá hazard com o operador que está no regist
# Caso retornar 2, terá hazard com o operador que está na Memoria 
# Caso retornar 3, terá hazard com o operador que está no Executa
# Caso retornar 0, não terá hazard.
def checkHazard(self, actPipeLine):
    depend = 0
    print("checando hazard")
    oneOp = ['sw', 'lw', 'addi', 'subi']
    twoOp = ["add", 'sub', 'mul', 'div', 'mov']
    desvios = ['blt', 'bgt', 'beq', 'j', 'jr', 'jal']
    execute = instrucao(actPipeLine["Executa"])
    mem = instrucao(actPipeLine["Memoria"])
    reg = instrucao(actPipeLine["Regist"])

    if (self.comando in oneOp):
        if (execute.pos1 == self.pos2):
            depend = 3
        elif (mem.pos1 == self.pos2):
            depend = 2
        elif (reg.pos1 == self.pos2):
            depend = 1
    elif (self.comando in twoOp):
        if (execute.pos1 == self.pos2 or execute.pos1 == self.pos3):
            depend = 3
        elif (mem.pos1 == self.pos2 or mem.pos1 == self.pos3):
            depend = 2
        elif (reg.pos1 == self.pos2 or reg.pos1 == self.pos3):
            depend = 1
    elif (self.comando in desvios):
        if (execute.pos1 == self.pos1 or execute.pos1 == self.pos2):
            depend = 3
        elif (mem.pos1 == self.pos1 or mem.pos1 == self.pos2):
            depend = 2
        elif (reg.pos1 == self.pos1 or reg.pos1 == self.pos2):
            depend = 1
    return depend

    
def printPipe(pipeline, r , m):
  print("|-----Busca-----||---Decodifica--||----Executa----||----Memoria----||----Regist-----|")  
  print(f'|  {pipeline["Busca"]:13}||  {pipeline["Decodifica"]:13}||  {pipeline["Executa"]:13}||  {pipeline["Memoria"]:13}||  {pipeline["Regist"]:13}|')
  print("Registrador:")
  print(r.r)
  print("Memoria")
  print(m.mem)
  print("PC : ", r.pc + 1, " SP : ", r.sp, " RA : ", r.ra ) 

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
  if (b == -1): # Caso o operador for J (sem vírgulas na instrução)
      a.append(opcode[space+1:len(opcode)])
      a.append("None")
      a.append("None")
      return a
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

def startR(r, m, j):
  p = pipeline()
  f = open("entrada.txt", "r")
  line = f.readlines()
  opTotal = len(line) # Quantidade total de opcodes
  while(True):
    i = 0
    if (j < opTotal):
        a = instrucao(line[j])
        r.pc = j
    else:
        a.instrucao = "NOOP"
    p.fpipe(a,r,m)
    pAux = p.pipe.copy() # Cria uma cópia da pipeline atual
    p.pipe["Busca"] = a.instrucao # Atualiza Busca
    for items in p.pipe.values(): # Iteração que irá mover os opcodes pelo pipeline
      if (i == len(p.pipelist) - 1): # Out of range handle
          break
      # Move todos os valores da pipeline para a direita começando da posição 2
      p.pipe[p.pipelist[i+1]] = pAux[p.pipelist[i]]                          
      i += 1
    decode = instrucao(p.pipe["Decodifica"])
    decode.decodifica(p.pipe,m,r, r.pc)
    pAux = p.pipe.copy() # Atualiza a cópia da pipeline atual

    #executa instrucoes
    mem = instrucao(p.pipe["Memoria"])
    instrucao.memoria(mem,r,m)
    reg = instrucao(p.pipe["Regist"])  
    instrucao.operar(reg,r,m)
    exe = instrucao(p.pipe["Executa"])
    j, p.pipe = instrucao.desvios(exe, r, m, r.pc, p.pipe)
    printPipe(p.pipe,r,m)
    isAllNoop = all(value == "NOOP" for value in p.pipe.values());
    if (isAllNoop == True):
      break
    input()
    j+=1 

  f.close()

def main():
  r = registrador()
  m = memoria()
  line = 0
  startR(r, m, line)
 
if __name__ == '__main__':
    main()