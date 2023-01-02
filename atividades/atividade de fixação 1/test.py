def pot_3 (numero: int):
    return numero**3

print([pot_3(n) for n in range(0,10) if n % 2 == 0])