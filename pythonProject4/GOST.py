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

# Генерация числа по ГОСТ 31.10-94
def generate_gost_numbers(qs, ts):
    results = []
    for q, t in zip(qs, ts):
        p = gost_31_10_94(q, t)
        results.append((q, t, p))
    return results

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