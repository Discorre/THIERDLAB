#include <iomanip>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <random>
#include <string>

using namespace std;

#include <iomanip> // Подключение заголовочного файла для использования манипуляторов ввода-вывода.

#include <iostream> // Подключение заголовочного файла для работы с потоками ввода-вывода.
#include <vector> // Подключение заголовочного файла для использования векторов.
#include <unordered_map> // Подключение заголовочного файла для использования неупорядоченных ассоциативных контейнеров.
#include <cmath> // Подключение заголовочного файла для математических операций.
#include <random> // Подключение заголовочного файла для генерации случайных чисел.
#include <string> // Подключение заголовочного файла для работы со строками.

using namespace std; // Использование пространства имен std.

bool miller_rabin(long long n, int k = 100) { // Объявление функции Miller-Rabin для проверки на простоту.
    if (n == 2 || n == 3) // Если число равно 2 или 3, то оно простое.
        return true;
    if (n <= 1 || n % 2 == 0) // Если число меньше или равно 1, или четное, то оно не является простым.
        return false;

    long long r = 0, d = n - 1; // Объявление переменных r и d для представления n - 1 как (2^r) * d, где d нечетное.
    while (d % 2 == 0) { // Вычисление r и d.
        r++;
        d /= 2;
    }

    for (int i = 0; i < k; i++) { // Повторяем k раз.
        long long a = rand() % (n - 2) + 2; // Генерация случайного основания a в интервале [2, n-1].
        long long x = 1;
        for (long long j = 0; j < d; j++) { // Вычисление a^d mod n.
            x = (x * a) % n;
        }
        if (x == 1 || x == n - 1) // Если x равно 1 или n - 1, продолжаем проверку.
            continue;
        for (long long j = 0; j < r - 1; j++) { // Повторяем r - 1 раз.
            x = (x * x) % n; // Возведение x в квадрат и вычисление по модулю n.
            if (x == n - 1) // Если x равно n - 1, прерываем цикл.
                break;
        }
        if (x != n - 1) // Если x не равно n - 1, число n не простое.
            return false;
    }
    return true; // Если после всех итераций пройдена проверка, число вероятно простое.
}

long long pow_mod(long long base, long long exponent, long long modulus) { // Объявление функции для вычисления степени числа по модулю.
    long long result = 1;
    while (exponent > 0) { // Пока степень не достигнет 0.
        if (exponent % 2 == 1) // Если степень нечетная.
            result = (result * base) % modulus; // Умножаем результат на base по модулю.
        base = (base * base) % modulus; // Возводим base в квадрат и берем по модулю.
        exponent /= 2; // Уменьшаем степень вдвое.
    }
    return result; // Возвращаем результат.
}

bool lehmann_pocklington(long long p, long long R, long long F, int t = 1) { // Объявление функции Лемана-Поклингтона для проверки простоты.
    for (int i = 0; i < t; i++) { // Повторяем t раз.
        long long a = rand() % (p - 1) + 1; // Генерируем случайное основание a в интервале [1, p-1].
        if (pow_mod(a, (p - 1) / 2, p) != pow_mod(R, (p - 1) / 2, p)) // Проверяем условие для Лемана-Поклингтона.
            return false;
        if (pow_mod(a, p - 1, p) != 1) // Проверяем условие для Лемана-Поклингтона.
            return false;
        long long b = pow_mod(a, (p - 1) / 2, p); // Вычисляем a^(p-1)/2 mod p.
        if (b != 1 && b != p - 1) // Проверяем условие для Лемана-Поклингтона.
            return false;
        if (pow_mod(F, (p - 1) / 2, p) != 1) // Проверяем условие для Лемана-Поклингтона.
            return false;
    }
    return true; // Если после всех итераций пройдена проверка, число вероятно простое.
}


long long gost_31_10_94(long long q, int t) { // Функция для генерации числа по стандарту ГОСТ 34.10-94.
    long long N = ((pow(2, t - 1)) / q) + 1; // Вычисление значения N по заданным параметрам.
    if (N % 2 != 0) // Если N нечетное, увеличиваем его на 1.
        N++;
    long long u = 0; // Инициализация переменной u.
    while (true) { // Бесконечный цикл.
        long long p = (N + u) * q + 1; // Вычисление числа p по формуле ГОСТ.
        if (p > pow(2, t)) // Если p больше 2^t, выходим из цикла.
            break;
        if (pow_mod(2, p - 1, p) == 1 && pow_mod(2, N + u, p) != 1) // Проверка условий ГОСТ.
            return p; // Возвращаем найденное простое число p.
        u += 2; // Увеличиваем u на 2.
    }
}

vector<long long> generate_primes_miller(int length, const vector<long long>& primes_table) { // Функция для генерации простых чисел методом Миллера.
    vector<long long> primes; // Инициализация вектора для хранения простых чисел.
    while (primes.size() < 10) { // Пока не сгенерировано 10 простых чисел.
        long long candidate = primes_table[rand() % primes_table.size()]; // Выбор кандидата из таблицы простых чисел.
        if (to_string(candidate).length() == length && miller_rabin(candidate)) // Проверка условий метода Миллера.
            primes.push_back(candidate); // Добавление простого числа в вектор.
    }
    return primes; // Возвращение вектора сгенерированных простых чисел.
}

vector<long long> generate_primes_pocklington(int length, const vector<long long>& primes_table) { // Функция для генерации простых чисел методом Лемана-Поклингтона.
    vector<long long> primes; // Инициализация вектора для хранения простых чисел.
    while (primes.size() < 10) { // Пока не сгенерировано 10 простых чисел.
        long long candidate = primes_table[rand() % primes_table.size()]; // Выбор кандидата из таблицы простых чисел.
        if (to_string(candidate).length() == length) { // Проверка длины числа.
            long long R = rand() % 3 + 1; // Генерация случайного значения R.
            long long F = rand() % 4 + 3; // Генерация случайного значения F.
            if (lehmann_pocklington(candidate, R, F)) // Проверка условий метода Лемана-Поклингтона.
                primes.push_back(candidate); // Добавление простого числа в вектор.
        }
    }
    return primes; // Возвращение вектора сгенерированных простых чисел.
}

vector<long long> generate_primes_gost(int length, const vector<long long>& primes_table) { // Функция для генерации простых чисел по стандарту ГОСТ 34.10-94.
    vector<long long> primes; // Инициализация вектора для хранения простых чисел.
    while (primes.size() < 10) { // Пока не сгенерировано 10 простых чисел.
        long long candidate = primes_table[rand() % primes_table.size()]; // Выбор кандидата из таблицы простых чисел.
        if (to_string(candidate).length() == length && gost_31_10_94(candidate, rand() % 3 + 1)) // Проверка условий стандарта ГОСТ.
            primes.push_back(candidate); // Добавление простого числа в вектор.
    }
    return primes; // Возвращение вектора сгенерированных простых чисел.
}


vector<int> check_primality(const vector<long long>& primes, int iterations = 100) {
    vector<int> results; // Создание вектора для хранения результатов проверки простоты.
    for (auto p : primes) { // Для каждого простого числа из входного вектора.
        int errors = 0; // Инициализация счетчика ошибок.
        for (int i = 0; i < iterations; i++) { // Повторяем проверку заданное количество раз.
            if (!miller_rabin(p)) // Если число не проходит тест Миллера-Рабина.
                errors++; // Увеличиваем счетчик ошибок.
        }
        results.push_back(errors); // Добавляем количество ошибок в результаты.
    }
    return results; // Возвращаем результаты проверки простоты для всех чисел.
}

vector<vector<string>> build_results_table(const vector<long long>& primes, const vector<int>& primality_results) {
    vector<vector<string>> table; // Создаем двумерный вектор для хранения таблицы результатов.
    table.push_back({ "#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }); // Добавляем заголовки столбцов.
    table.push_back({ "P" }); // Добавляем заголовок столбца с простыми числами.
    table.push_back({ "R" }); // Добавляем заголовок столбца с результатами простоты.
    table.push_back({ "K" }); // Добавляем заголовок столбца с количеством ошибок.
    for (size_t i = 0; i < primes.size(); i++) { // Для каждого простого числа и его результатов.
        table[1].push_back(to_string(primes[i])); // Добавляем простое число в таблицу.
        table[2].push_back(primality_results[i] < 10 ? "+" : "-"); // Добавляем результат простоты в таблицу.
        table[3].push_back(to_string(primality_results[i])); // Добавляем количество ошибок в таблицу.
    }
    return table; // Возвращаем построенную таблицу результатов.
}

vector<vector<int>> lehmann_pocklington_table(const vector<int>& numbers, const vector<int>& R_values, const vector<int>& F_values, int t = 100) {
    srand(time(nullptr)); // Инициализация генератора случайных чисел.
    vector<vector<int>> results; // Создание двумерного вектора для хранения результатов.
    for (int p : numbers) { // Для каждого числа из входного вектора.
        int errors = 0; // Инициализация счетчика ошибок.
        for (int i = 0; i < t; ++i) { // Повторяем проверку заданное количество раз.
            int R = R_values[rand() % R_values.size()]; // Генерация случайного значения R.
            int F = F_values[rand() % F_values.size()]; // Генерация случайного значения F.
            if (!lehmann_pocklington(p, R, F)) // Если число не проходит тест Лемана-Поклингтона.
                errors++; // Увеличиваем счетчик ошибок.
        }
        int error_probability = static_cast<double>(errors) / t; // Вычисляем вероятность ошибки.
        vector<int> row = { p, R_values[rand() % R_values.size()], error_probability }; // Создаем строку результатов.
        results.push_back(row); // Добавляем строку результатов в таблицу.
    }
    return results; // Возвращаем таблицу результатов.
}

vector<int> generate_gost_numbers(const vector<int>& qs, const vector<int>& ts) {
    vector<int> results; // Создание вектора для хранения результатов.
    for (size_t i = 0; i < qs.size(); ++i) { // Для каждой пары значений q и t.
        int p = gost_31_10_94(qs[i], ts[i]); // Генерируем число по стандарту ГОСТ 34.10-94.
        results.push_back(p); // Добавляем результат в вектор.
    }
    return results; // Возвращаем вектор сгенерированных чисел.
}


unordered_map<int, int> prime_factors(int n) {
    unordered_map<int, int> factors_count; // Создание ассоциативного контейнера для хранения простых множителей и их степеней.
    while (n % 2 == 0) { // Пока число делится на 2 без остатка.
        factors_count[2]++; // Увеличиваем степень простого множителя 2.
        n /= 2; // Делаем частное от деления числа на 2.
    }
    for (int i = 3; i <= sqrt(n); i += 2) { // Перебираем нечетные числа от 3 до корня из n.
        while (n % i == 0) { // Пока число делится на текущее значение i без остатка.
            factors_count[i]++; // Увеличиваем степень простого множителя i.
            n /= i; // Делаем частное от деления числа на i.
        }
    }
    if (n > 2) // Если остаток от деления больше 2, то это простой множитель.
        factors_count[n]++; // Увеличиваем степень простого множителя n.
    return factors_count; // Возвращаем ассоциативный контейнер с простыми множителями и их степенями.
}

string factors_to_string(const unordered_map<int, int>& factors) {
    string factors_str = ""; // Создание строки для представления простых множителей и их степеней.
    for (const auto& factor : factors) { // Для каждой пары ключ-значение в ассоциативном контейнере.
        if (factor.second > 1) // Если степень простого множителя больше 1.
            factors_str += to_string(factor.first) + "^" + to_string(factor.second) + " * "; // Добавляем в строку простой множитель и его степень.
        else // Если степень простого множителя равна 1.
            factors_str += to_string(factor.first) + " * "; // Добавляем в строку только простой множитель.
    }
    return factors_str.substr(0, factors_str.length() - 3); // Возвращаем строку, убирая последние три символа (пробел и звездочка).
}

vector<vector<int>> miller_rabin_table(const vector<int>& numbers) {
    vector<vector<int>> table; // Создаем двумерный вектор для хранения таблицы результатов теста Миллера-Рабина.
    for (int p : numbers) { // Для каждого числа из входного вектора.
        int errors = 0; // Инициализация счетчика ошибок.
        if (!miller_rabin(p)) // Если число не проходит тест Миллера-Рабина.
            errors++; // Увеличиваем счетчик ошибок.
        auto factors = prime_factors(p - 1); // Получаем простые множители числа p - 1 и их степени.
        int error_probability = 1.0 / pow(2, factors.size()); // Вычисляем вероятность ошибки.
        table.push_back({ p, error_probability }); // Добавляем результаты в таблицу.
    }
    return table; // Возвращаем таблицу результатов.
}

vector<int> sieve_of_eratosthenes(int limit) {
    vector<bool> sieve(limit + 1, true); // Создаем решето Эратосфена.
    vector<int> primes; // Создаем вектор для хранения простых чисел.
    for (int p = 2; p * p <= limit; ++p) { // Перебираем числа от 2 до корня из limit.
        if (sieve[p]) { // Если текущее число является простым.
            primes.push_back(p); // Добавляем его в вектор простых чисел.
            for (int i = p * p; i <= limit; i += p) { // Помечаем все кратные текущему числу как составные.
                sieve[i] = false;
            }
        }
    }
    for (int p = (int)sqrt(limit) + 1; p <= limit; ++p) { // Добавляем оставшиеся простые числа в вектор.
        if (sieve[p]) {
            primes.push_back(p);
        }
    }
    return primes; // Возвращаем вектор простых чисел.
}

vector<int> generate_primes_miller(int length, const vector<int>& primes_table) {
    vector<int> primes; // Создаем вектор для хранения сгенерированных простых чисел.
    int attempts = 0; // Инициализируем счетчик попыток генерации.
    while (primes.size() < 10 && attempts < 1000) { // Пока не сгенерировано 10 простых чисел или не превышено максимальное количество попыток.
        int candidate = primes_table[rand() % primes_table.size()]; // Выбираем случайное число из таблицы простых чисел.
        if (to_string(candidate).length() == length && miller_rabin(candidate)) { // Если длина числа соответствует заданной и оно проходит тест Миллера-Рабина.
            primes.push_back(candidate); // Добавляем его в вектор.
        }
        attempts++; // Увеличиваем счетчик попыток.
    }
    return primes; // Возвращаем вектор сгенерированных простых чисел.
}

vector<int> generate_primes_pocklington(int length, const vector<int>& primes_table) {
    vector<int> primes; // Создаем вектор для хранения сгенерированных простых чисел.
    int attempts = 0; // Инициализируем счетчик попыток генерации.
    while (primes.size() < 10 && attempts < 1000) { // Пока не сгенерировано 10 простых чисел или не превышено максимальное количество попыток.
        int candidate = primes_table[rand() % primes_table.size()]; // Выбираем случайное число из таблицы простых чисел.
        if (to_string(candidate).length() == length) { // Если длина числа соответствует заданной.
            int R = rand() % 3 == 0 ? 4 : (rand() % 3 == 1 ? 7 : 15); // Генерируем значение R.
            int F = rand() % 4 == 0 ? 3 : (rand() % 3 == 1 ? 4 : (rand() % 2 == 0 ? 8 : 20)); // Генерируем значение F.
            if (lehmann_pocklington(candidate, R, F)) { // Если число проходит тест Лемана-Поклингтона.
                primes.push_back(candidate); // Добавляем его в вектор.
            }
        }
        attempts++; // Увеличиваем счетчик попыток.
    }
    return primes; // Возвращаем вектор сгенерированных простых чисел.
}

vector<int> generate_primes_gost(int length, const vector<int>& primes_table) {
    vector<int> primes; // Создаем вектор для хранения сгенерированных простых чисел.
    int attempts = 0; // Инициализируем счетчик попыток генерации.
    while (primes.size() < 10 && attempts < 1000) { // Пока не сгенерировано 10 простых чисел или не превышено максимальное количество попыток.
        int candidate = primes_table[rand() % primes_table.size()]; // Выбираем случайное число из таблицы простых чисел.
        if (to_string(candidate).length() == length && gost_31_10_94(candidate, rand() % 3 == 0 ? 4 : (rand() % 3 == 1 ? 7 : 15)) != -1) { // Если длина числа соответствует заданной и оно проходит стандарт ГОСТ 34.10-94.
            primes.push_back(candidate); // Добавляем его в вектор.
        }
        attempts++; // Увеличиваем счетчик попыток.
    }
    return primes; // Возвращаем вектор сгенерированных простых чисел.
}

// Проверка простых чисел на простоту с помощью вероятностного теста
vector<int> check_primality(const vector<int>& primes, int iterations = 100) {
    vector<int> results; // Создаем вектор для хранения результатов проверки простоты.
    for (int p : primes) { // Для каждого простого числа из входного вектора.
        int errors = 0; // Инициализируем счетчик ошибок.
        for (int i = 0; i < iterations; ++i) { // Повторяем проверку заданное количество раз.
            if (!miller_rabin(p)) { // Если число не проходит тест Миллера-Рабина.
                errors += 1; // Увеличиваем счетчик ошибок.
            }
        }
        results.push_back(errors); // Добавляем количество ошибок в результаты.
    }
    return results; // Возвращаем результаты проверки простоты для всех чисел.
}

// Построение таблиц результатов
vector<vector<string>> build_results_table(const vector<int>& primes, const vector<int>& primality_results) {
    vector<vector<string>> table(4, vector<string>(11)); // Создаем двумерный вектор для хранения таблицы результатов.
    table[0][0] = "#"; // Заголовок столбца с порядковыми номерами.
    table[1][0] = "P"; // Заголовок столбца с простыми числами.
    table[2][0] = "R"; // Заголовок столбца с результатами простоты.
    table[3][0] = "K"; // Заголовок столбца с количеством ошибок.
    int num_primes = primes.size(); // Получаем количество найденных простых чисел.
    for (int i = 0; i < 10; ++i) { // Для каждой строки таблицы.
        table[0][i + 1] = to_string(i + 1); // Заполняем порядковые номера.
        if (i < num_primes) { // Проверяем, что индекс в пределах размера вектора.
            table[1][i + 1] = to_string(primes[i]); // Заполняем столбец с простыми числами.
        }
        else {
            table[1][i + 1] = ""; // Если простых чисел не хватает, оставляем ячейку пустой.
        }
        table[2][i + 1] = i < num_primes && primality_results[i] < 0.1 ? "+" : "-"; // Заполняем столбец с результатами простоты.
        table[3][i + 1] = i < num_primes ? to_string(primality_results[i]) : ""; // Заполняем столбец с количеством ошибок.
    }
    return table; // Возвращаем построенную таблицу результатов.
}


int main() {
    setlocale(LC_ALL, "Russian"); // Устанавливаем локаль для корректного отображения русского текста.

    vector<int> miller_numbers = { 13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373 }; // Задаем список чисел для теста Миллера-Рабина.
    auto miller_table = miller_rabin_table(miller_numbers); // Получаем таблицу результатов теста Миллера-Рабина.
    cout << "Результаты теста Миллера-Рабина:" << endl; // Выводим заголовок таблицы.
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.
    cout << setw(15) << left << "Простое число p" << setw(20) << left << "Разложение (p - 1)" << setw(25) << left << "Вероятность ошибки" << endl; // Выводим заголовки столбцов.
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.
    for (const auto& row : miller_table) { // Для каждой строки в таблице результатов.
        int p = row[0]; // Получаем простое число.
        auto factors = prime_factors(p - 1); // Получаем простые множители числа p - 1.
        string factors_str = factors_to_string(factors); // Преобразуем множители в строку.
        double error = row[1]; // Получаем вероятность ошибки.
        cout << setw(15) << left << p << setw(20) << left << factors_str << setw(25) << left << error << endl; // Выводим данные о числе, его разложении и вероятности ошибки.
    }
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.

    vector<int> pocklington_numbers = { 13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373 }; // Задаем список чисел для теста Лемана-Поклингтона.
    vector<int> R_values = { 4, 7, 15, 12, 13, 43, 89, 22, 209, 23, 77, 41, 89, 93, 85, 1549, 177 }; // Задаем список значений R.
    vector<int> F_values = { 3, 4, 4, 8, 8, 4, 2, 16, 2, 20, 8, 20, 8, 20, 12, 64, 72, 4, 36 }; // Задаем список значений F.
    int iterations = 100; // Задаем количество итераций.
    auto pocklington_table = lehmann_pocklington_table(pocklington_numbers, R_values, F_values, iterations); // Получаем таблицу результатов теста Лемана-Поклингтона.
    cout << "Результаты теста Лемана-Поклингтона:" << endl; // Выводим заголовок таблицы.
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.
    cout << setw(15) << left << "Простое число p" << setw(20) << left << "Разложение F" << setw(10) << left << "R" << setw(25) << left << "Вероятность ошибки" << endl; // Выводим заголовки столбцов.
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.
    for (const auto& row : pocklington_table) { // Для каждой строки в таблице результатов.
        auto factors = prime_factors(row[0] - 1); // Получаем простые множители числа p - 1.
        string factors_str = factors_to_string(factors); // Преобразуем множители в строку.
        cout << setw(15) << left << row[0] << setw(20) << left << factors_str << setw(10) << left << row[1] << setw(25) << left << row[2] << endl;
    }
    cout << "---------------------------------------------------------------------" << endl; // Выводим разделительную строку.

    // Примеры значений q и t для процедуры ГОСТ 31.10-94
    vector<int> gost_qs = { 3, 5, 7, 5, 11, 11, 13, 13, 17, 17, 19, 23, 29, 31, 37, 41, 19, 23 }; // Задаем значения q.
    vector<int> gost_ts = { 4, 6, 5, 5, 7, 8, 7, 8, 9, 10, 9, 9, 9, 9, 11, 11, 10, 10 }; // Задаем значения t.

    vector<int> gost_results = generate_gost_numbers(gost_qs, gost_ts); // Получаем простые числа по процедуре ГОСТ 31.10-94.

    // Вывод результатов
    cout << "\nРезультаты ГОСТ 31.10-94:\n"; // Выводим заголовок таблицы.
    cout << "---------------------------------------------------------------------\n"; // Выводим разделительную строку.
    cout << "q\tt\tПростое число p\n"; // Выводим заголовки столбцов.
    cout << "---------------------------------------------------------------------\n"; // Выводим разделительную строку.
    for (size_t i = 0; i < gost_qs.size(); ++i) { // Для каждой пары значений q и t.
        cout << gost_qs[i] << "\t" << gost_ts[i] << "\t" << gost_results[i] << "\n"; // Выводим значения q, t и полученное простое число p.
    }
    cout << "---------------------------------------------------------------------\n"; // Выводим разделительную строку.


    srand(time(0));

    // Построение таблицы простых чисел меньше 500
    vector<int> primes_table = sieve_of_eratosthenes(500);

    // Получение 10 простых чисел длины 3 на основе теста Миллера
    vector<int> primes_miller = generate_primes_miller(3, primes_table);
    // Получение 10 простых чисел длины 3 на основе теста Поклингтона
    vector<int> primes_pocklington = generate_primes_pocklington(3, primes_table);
    // Получение 10 простых чисел длины 3 на основе ГОСТ Р 34.10-94
    vector<int> primes_gost = generate_primes_gost(3, primes_table);

    // Проверка простых чисел на простоту с помощью вероятностного теста
    vector<int> primality_results_miller = check_primality(primes_miller);
    vector<int> primality_results_pocklington = check_primality(primes_pocklington);
    vector<int> primality_results_gost = check_primality(primes_gost);

    // Построение таблиц результатов
    vector<vector<string>> results_table_miller = build_results_table(primes_miller, primality_results_miller);
    vector<vector<string>> results_table_pocklington = build_results_table(primes_pocklington, primality_results_pocklington);
    vector<vector<string>> results_table_gost = build_results_table(primes_gost, primality_results_gost);

    // Вывод результатов
    cout << "Простые числа длины 3, полученные на основе теста Миллера:" << endl; // Вывод заголовка для результатов теста Миллера.
    for (const auto& row : results_table_miller) { // Для каждой строки в таблице результатов теста Миллера.
        for (const auto& cell : row) { // Для каждой ячейки в строке.
            cout << cell << "\t"; // Выводим содержимое ячейки с табуляцией.
        }
        cout << endl; // Переходим на новую строку после вывода каждой строки таблицы.
    }
    cout << "\nПростые числа длины 3, полученные на основе теста Поклингтона:" << endl; // Вывод заголовка для результатов теста Поклингтона.
    for (const auto& row : results_table_pocklington) { // Для каждой строки в таблице результатов теста Поклингтона.
        for (const auto& cell : row) { // Для каждой ячейки в строке.
            cout << cell << "\t"; // Выводим содержимое ячейки с табуляцией.
        }
        cout << endl; // Переходим на новую строку после вывода каждой строки таблицы.
    }
    cout << "\nПростые числа длины 3, полученные на основе ГОСТ Р 34.10-94:" << endl; // Вывод заголовка для результатов ГОСТ Р 34.10-94.
    for (const auto& row : results_table_gost) { // Для каждой строки в таблице результатов ГОСТ Р 34.10-94.
        for (const auto& cell : row) { // Для каждой ячейки в строке.
            cout << cell << "\t"; // Выводим содержимое ячейки с табуляцией.
        }
        cout << endl; // Переходим на новую строку после вывода каждой строки таблицы.
    }


    return 0;
}