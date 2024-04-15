import random
import math

# Функция для проверки простоты числа методом Миллера
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

# Процедура генерации чисел по ГОСТ 31.10-94
def gost_31_10_94(q, t):
    N = ((2**(t - 1)) // q) + 1
    if N % 2 != 0:
        N += 1
    u = 0
    while True:
        p = (N + u) * q + 1
        if p > 2 ** t:
            break
        if pow(2, p - 1) % p == 1 and pow(2, N + u) % p != 1:
            return p
        u += 2

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

# Генерация числа по ГОСТ 31.10-94
def generate_gost_numbers(qs, ts):
    results = []
    for q, t in zip(qs, ts):
        p = gost_31_10_94(q, t)
        results.append((q, t, p))
    return results

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

# Для процедуры генерации чисел ГОСТ 31.10-94
gost_qs = [3, 5, 7, 5, 11, 11, 13, 13, 17, 17, 19, 23, 29, 31, 37, 41, 19, 23]  # Примеры значений q для процедуры ГОСТ 31.10-94
gost_ts = [4, 6, 5, 5, 7, 8, 7, 8, 9, 10, 9, 9, 9, 9, 11, 11, 10, 10]     # Примеры значений t для процедуры ГОСТ 31.10-94
gost_results = generate_gost_numbers(gost_qs, gost_ts)
print("\nGOST 31.10-94 Generation Results:")
print("---------------------------------------------------------------------")
print("q\tt\tПростое число p")
print("---------------------------------------------------------------------")
for result in gost_results:
    q, t, p = result
    print(f"{q}\t{t}\t{p}")
print("---------------------------------------------------------------------")

# Построение таблицы простых чисел, меньших 500, с помощью решета Эратосфена
def sieve_of_eratosthenes(limit):
    primes = []
    sieve = [True] * (limit + 1)
    for p in range(2, int(math.sqrt(limit)) + 1):
        if sieve[p]:
            primes.append(p)
            for i in range(p * p, limit + 1, p):
                sieve[i] = False
    for p in range(int(math.sqrt(limit)) + 1, limit + 1):
        if sieve[p]:
            primes.append(p)
    return primes

# Получение простых чисел заданной длины на основе теста Миллера
def generate_primes_miller(length, primes_table):
    primes = []
    while len(primes) < 10:
        candidate = random.choice(primes_table)
        if len(str(candidate)) == length and miller_rabin(candidate):
            primes.append(candidate)
    return primes

# Получение простых чисел заданной длины на основе теста Поклингтона
def generate_primes_pocklington(length, primes_table):
    primes = []
    while len(primes) < 10:
        candidate = random.choice(primes_table)
        if len(str(candidate)) == length:
            R = random.choice([4, 7, 15])
            F = random.choice([3, 4, 8, 20])  # Adding choices for F
            if lehmann_pocklington(candidate, R, F):
                primes.append(candidate)
    return primes
# Получение простых чисел заданной длины ГОСТ Р 34.10-94
def generate_primes_gost(length, primes_table):
    primes = []
    while len(primes) < 10:
        candidate = random.choice(primes_table)
        if len(str(candidate)) == length and gost_31_10_94(candidate, random.choice([4, 7, 15])):
            primes.append(candidate)
    return primes

# Проверка простых чисел на простоту с помощью вероятностного теста
def check_primality(primes, iterations=100):
    results = []
    for p in primes:
        errors = 0
        for _ in range(iterations):
            if not miller_rabin(p):
                errors += 1
        results.append(errors)
    return results

# Построение таблицы результатов
def build_results_table(primes, primality_results):
    table = [["#"] + list(range(1, 11)), ["P"] + primes, ["R"] + ["+" if err < 0.1 else "-" for err in primality_results], ["K"] + primality_results]
    return table

# Построение таблицы простых чисел меньше 500
primes_table = sieve_of_eratosthenes(5000)

# Получение 10 простых чисел длины 3 на основе теста Миллера
primes_miller = generate_primes_miller(4, primes_table)
# Получение 10 простых чисел длины 3 на основе теста Поклингтона
primes_pocklington = generate_primes_pocklington(4, primes_table)
# Получение 10 простых чисел длины 3 на основе ГОСТ Р 34.10-94
primes_gost = generate_primes_gost(4, primes_table)

# Проверка простых чисел на простоту с помощью вероятностного теста
primality_results_miller = check_primality(primes_miller)
primality_results_pocklington = check_primality(primes_pocklington)
primality_results_gost = check_primality(primes_gost)

# Построение таблиц результатов
results_table_miller = build_results_table(primes_miller, primality_results_miller)
results_table_pocklington = build_results_table(primes_pocklington, primality_results_pocklington)
results_table_gost = build_results_table(primes_gost, primality_results_gost)
# Вывод результатов
print("Простые числа длины 3, полученные на основе теста Миллера:")
for row in results_table_miller:
    print("\t".join(map(str, row)))
print("\nПростые числа длины 3, полученные на основе теста Поклингтона:")
for row in results_table_pocklington:
    print("\t".join(map(str, row)))
print("\nПростые числа длины 3, полученные на основе ГОСТ Р 34.10-94:")
for row in results_table_gost:
    print("\t".join(map(str, row)))