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
primes_table = sieve_of_eratosthenes(500)

# Получение 10 простых чисел длины 3 на основе теста Миллера
primes_miller = generate_primes_miller(3, primes_table)
# Получение 10 простых чисел длины 3 на основе теста Поклингтона
primes_pocklington = generate_primes_pocklington(3, primes_table)
# Получение 10 простых чисел длины 3 на основе ГОСТ Р 34.10-94
primes_gost = generate_primes_gost(3, primes_table)

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