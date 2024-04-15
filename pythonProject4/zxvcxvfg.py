import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress

# Функция для моделирования процесса остывания кофе
def coffee_cooling(initial_temp, room_temp, time_constant, time_points):
    temps = []
    for t in time_points:
        temp = room_temp + (initial_temp - room_temp) * np.exp(-t / time_constant)
        temps.append(temp)
    return temps

# Генерация случайных данных измерений температуры
def generate_measurements(true_temps, noise_level):
    return [temp + np.random.normal(0, noise_level) for temp in true_temps]

# Задаем параметры
initial_temp = 88.0  # начальная температура кофе
room_temp = 26.0  # температура окружающей среды
time_constant = 10.0  # постоянная времени (время, за которое температура уменьшается в 1/e раз)
measurement_noise = 1.0  # уровень шума в измерениях температуры
num_measurements = 120  # количество измерений

# Создаем временные отрезки для измерений
time_points = np.linspace(0, 60, num_measurements)

# Моделируем процесс остывания кофе
true_temps = coffee_cooling(initial_temp, room_temp, time_constant, time_points)

# Генерируем измерения с добавлением шума
measurements = generate_measurements(true_temps, measurement_noise)

# Строим график исходных данных
plt.figure(figsize=(10, 6))
plt.plot(time_points, true_temps, label='True Temperature', color='blue')
plt.scatter(time_points, measurements, label='Measurements', color='red')
plt.xlabel('Time (minutes)')
plt.ylabel('Temperature (°C)')
plt.title('Coffee Cooling Process')
plt.legend()
plt.grid(True)
plt.show()

# Строим линейную модель и анализируем ее адекватность
slope, intercept, r_value, p_value, std_err = linregress(time_points, measurements)
print(f"Slope: {slope}")
print(f"Intercept: {intercept}")
print(f"R-squared: {r_value**2}")
print(f"P-value: {p_value}")
