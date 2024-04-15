import numpy as np

# Функция для выполнения линейной аппроксимации по методу наименьших квадратов.
def aproks(x, y):
    n = len(x)
    x_sum = np.sum(x)
    y_sum = np.sum(y)
    x2_sum = np.sum(np.square(x))
    xy_sum = np.sum(np.multiply(x, y))

    a = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum)
    b = (y_sum - a * x_sum) / n

    return {'a': a, 'b': b}

# Функция для расчета коэффициента корреляции и t-статистики.
def korrel(x, y):
    if len(x) != len(y) or len(x) == 0:
        raise ValueError("Vectors must be of the same size and not empty.")

    x_mean = np.mean(x)
    y_mean = np.mean(y)
    sum_xy = np.sum((x - x_mean) * (y - y_mean))
    sum_x2 = np.sum(np.square(x - x_mean))
    sum_y2 = np.sum(np.square(y - y_mean))

    r = sum_xy / (np.sqrt(sum_x2) * np.sqrt(sum_y2))
    t = r * np.sqrt(len(x) - 2) / np.sqrt(1 - r * r)

    return {'correlation': r, 't_value': t}

# Функция для моделирования изменения температуры кофе со временем.
def coffee(T, Ts, r, time):
    temperatures = []
    for t in range(time + 1):
        temperature = Ts + (T - Ts) * np.exp(-r * t)
        temperatures.append(temperature)
    return temperatures

# Начальные данные
T = 90  # Начальная температура кофе
Ts = 26  # Температура комнаты
r = 0.01  # Коэффициент остывания
time = 60  # Временной предел в минутах

# Моделирование изменения температуры кофе.
temperatures = coffee(T, Ts, r, time)

# Вектор временных интервалов.
times = np.arange(time + 1)

# Выполнение линейной аппроксимации.
approx_result = aproks(times, temperatures)

# Вычисление коэффициента корреляции и t-статистики.
corr_result = korrel(times, temperatures)

# Вывод результатов аппроксимации и корреляции.
print("Approximation Result:")
print("a:", approx_result['a'], ", b:", approx_result['b'])
print("\nCorrelation Result:")
print("Correlation:", corr_result['correlation'])
print("T-value:", corr_result['t_value'])

# Вывод данных о температуре кофе со временем.
for i in range(len(temperatures)):
    print("Time -", times[i], ":", temperatures[i], "C")
