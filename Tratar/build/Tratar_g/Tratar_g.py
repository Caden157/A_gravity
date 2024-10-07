from math import pi, sqrt

verify = str
while True:
    d = float(input("Digite a variação do comprimento de corda (m): "))
    cycles = int(input("Digite o valor de ciclos: "))
    data_t1 = [5]
    data_t2 = [5]
    T1, T2, g, Dg = (0, 0, 0, 0)
    Dd, Dt = (0.0005, 0.0005)

    print("="*100)
    for t in range(cycles):
        value = float(input(f"Digite o {t+1}º valor para T1: "))
        data_t1.append(value)
        T1 += value

    print("="*100)
    for t in range(cycles):
        value = float(input(f"Digite o {t+1}º valor para T2: "))
        data_t2.append(value)
        T2 += value

    T1 /= cycles
    T2 /= cycles

    print("="*100)
    g = 4 * pi**2 * (d/(T1**2 - T2**2))
    Dg = sqrt((g/d * Dd)**2 + (2 * g * T1/(T1**2 - T2**2) * Dt)**2 + (2 * g * T2/(T1**2 - T2**2) * Dt)**2)

    print(f"O valor da aceleração da gravidade local é: {g} ± {Dg} m/s²")

    while True:
        verify = str(input("Deseja continuar? (S/N): ")).upper()

        if verify != 'S' and verify != 'N':
            print("Resposta inválida!")
        else:
            break

    if verify == "N":
        print("="*100)
        break

    print("="*100)
