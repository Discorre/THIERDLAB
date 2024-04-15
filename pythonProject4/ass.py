import random
import math

def miller_rabin(n, k=100):
    if n == 2 or n == 3:
        return True
    if n <= 1 or n % 2 == 0:
        return False

    # Выразить n - 1 как (2^r * d)
    r, d = 0, n - 1
    while d % 2 == 0:
        r += 1
        d //= 2

    # Провести k тестов Миллера
    for _ in range(k):
        a = random.randint(2, n - 2)
        x = pow(a, d) % n
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2) % n
            if x == n - 1:
                break
        else:
            return False
    return True

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

# Генерация таблицы для теста Миллера
def miller_rabin_table(numbers):
    table = []
    for p in numbers:
        errors = 0
        if not miller_rabin(p):
            errors += 1
        factors = prime_factors(p - 1)
        error_probability = 1 / (2 ** len(factors))
        table.append([p, factors, error_probability])
    return table

# Пример использования функций
# Для теста Миллера
miller_numbers = [13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373]  # Пример входных чисел
miller_table = miller_rabin_table(miller_numbers)
print("Miller-Rabin Test Results:")
print("---------------------------------------------------------------------")
print("{:<15} {:<20} {:<25}".format("Простое число p", "Разложение (p - 1)", "Вероятность ошибки"))
print("---------------------------------------------------------------------")
for row in miller_table:
    p, factors, error = row
    factors_str = factors_to_string(factors)
    print("{:<15} {:<20} {:<25}".format(p, factors_str, error))
print("---------------------------------------------------------------------")