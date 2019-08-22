x = input("Digite um numero X qualquer: ")
i = 0
resultado = 0
def Somar(x):
    global i
    global resultado
    while i < 3:
        resultado += int(x)
        i += 1
    return resultado


PE = Somar(x)
print("X+Y = " + str(PE))