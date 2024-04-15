import random
import math

# Функция для проверки простоты числа методом Поклингтона
def lehmann_pocklington(p, R, F, t=1):
    for _ in range(t):
        a = random.randint(2, p - 1)
        if pow(a, (p - 1) // 2) % p != pow(R, (p - 1) // 2) % p:
            return False
        if pow(a, p - 1) % p != 1:
            return False
        b = pow(a, (p - 1) // 2) % p
        if b != 1 and b != p - 1:
            return False
        if pow(F, (p - 1) // 2) % p != 1:
            return False
    return True

# Генерация таблицы для теста Поклингтона
def lehmann_pocklington_table(numbers, R_values, F_values, t=100):
    global R
    results = []
    for p in numbers:
        errors = 0
        for i in range(t):
            R = random.choice(R_values)
            F = random.choice(F_values)
            if not lehmann_pocklington(p, R, F):
                errors += 1
        error_probability = errors / t
        results.append([p, prime_factors(p - 1), R, error_probability])
    return results

# Функция для разложения числа на простые множители с подсчетом повторяющихся множителей
def prime_factors(n):
    factors_count = {}
    while n % 2 == 0:
        if 2 in factors_count:
            factors_count[2] += 1
        else:
            factors_count[2] = 1
        n //= 2
    for i in range(3, int(math.sqrt(n)) + 1, 2):
        while n % i == 0:
            if i in factors_count:
                factors_count[i] += 1
            else:
                factors_count[i] = 1
            n //= i
    if n > 2:
        if n in factors_count:
            factors_count[n] += 1
        else:
            factors_count[n] = 1
    return factors_count

# Преобразование словаря множителей в строку
def factors_to_string(factors):
    factors_str = ''
    for factor, count in factors.items():
        if count > 1:
            factors_str += '{}^{} * '.format(factor, count)
        else:
            factors_str += '{} * '.format(factor)
    return factors_str[:-3]

# Для теста Поклингтона
pocklington_numbers = [13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373]  # Пример входных чисел
R_values = [4, 7, 15, 12, 13, 43, 89, 22, 209, 23, 77, 41, 89, 93, 85, 1549, 177]  # Пример значений R
F_values = [3, 4, 4, 8, 8, 4, 2, 16, 2, 20, 8, 20, 8, 20, 12, 64, 72, 4, 36]  # Пример значений F
iterations = 100  # Количество итераций теста
pocklington_table = lehmann_pocklington_table(pocklington_numbers, R_values, F_values, t=iterations)
print("Lehmann-Pocklington Test Results:")
print("---------------------------------------------------------------------")
print("{:<15} {:<20} {:<10} {:<25}".format("Простое число p", "Разложение F", "R", "Вероятность ошибки"))
print("---------------------------------------------------------------------")
for row in pocklington_table:
    p, factors, R, error = row
    factors_str = factors_to_string(factors)
    print("{:<15} {:<20} {:<10} {:<25}".format(p, factors_str, R, error))
print("---------------------------------------------------------------------")