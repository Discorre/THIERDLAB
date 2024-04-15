#include <iomanip>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <random>
#include <string>

using namespace std;

#include <iomanip> // ����������� ������������� ����� ��� ������������� ������������� �����-������.

#include <iostream> // ����������� ������������� ����� ��� ������ � �������� �����-������.
#include <vector> // ����������� ������������� ����� ��� ������������� ��������.
#include <unordered_map> // ����������� ������������� ����� ��� ������������� ��������������� ������������� �����������.
#include <cmath> // ����������� ������������� ����� ��� �������������� ��������.
#include <random> // ����������� ������������� ����� ��� ��������� ��������� �����.
#include <string> // ����������� ������������� ����� ��� ������ �� ��������.

using namespace std; // ������������� ������������ ���� std.

bool miller_rabin(long long n, int k = 100) { // ���������� ������� Miller-Rabin ��� �������� �� ��������.
    if (n == 2 || n == 3) // ���� ����� ����� 2 ��� 3, �� ��� �������.
        return true;
    if (n <= 1 || n % 2 == 0) // ���� ����� ������ ��� ����� 1, ��� ������, �� ��� �� �������� �������.
        return false;

    long long r = 0, d = n - 1; // ���������� ���������� r � d ��� ������������� n - 1 ��� (2^r) * d, ��� d ��������.
    while (d % 2 == 0) { // ���������� r � d.
        r++;
        d /= 2;
    }

    for (int i = 0; i < k; i++) { // ��������� k ���.
        long long a = rand() % (n - 2) + 2; // ��������� ���������� ��������� a � ��������� [2, n-1].
        long long x = 1;
        for (long long j = 0; j < d; j++) { // ���������� a^d mod n.
            x = (x * a) % n;
        }
        if (x == 1 || x == n - 1) // ���� x ����� 1 ��� n - 1, ���������� ��������.
            continue;
        for (long long j = 0; j < r - 1; j++) { // ��������� r - 1 ���.
            x = (x * x) % n; // ���������� x � ������� � ���������� �� ������ n.
            if (x == n - 1) // ���� x ����� n - 1, ��������� ����.
                break;
        }
        if (x != n - 1) // ���� x �� ����� n - 1, ����� n �� �������.
            return false;
    }
    return true; // ���� ����� ���� �������� �������� ��������, ����� �������� �������.
}

long long pow_mod(long long base, long long exponent, long long modulus) { // ���������� ������� ��� ���������� ������� ����� �� ������.
    long long result = 1;
    while (exponent > 0) { // ���� ������� �� ��������� 0.
        if (exponent % 2 == 1) // ���� ������� ��������.
            result = (result * base) % modulus; // �������� ��������� �� base �� ������.
        base = (base * base) % modulus; // �������� base � ������� � ����� �� ������.
        exponent /= 2; // ��������� ������� �����.
    }
    return result; // ���������� ���������.
}

bool lehmann_pocklington(long long p, long long R, long long F, int t = 1) { // ���������� ������� ������-����������� ��� �������� ��������.
    for (int i = 0; i < t; i++) { // ��������� t ���.
        long long a = rand() % (p - 1) + 1; // ���������� ��������� ��������� a � ��������� [1, p-1].
        if (pow_mod(a, (p - 1) / 2, p) != pow_mod(R, (p - 1) / 2, p)) // ��������� ������� ��� ������-�����������.
            return false;
        if (pow_mod(a, p - 1, p) != 1) // ��������� ������� ��� ������-�����������.
            return false;
        long long b = pow_mod(a, (p - 1) / 2, p); // ��������� a^(p-1)/2 mod p.
        if (b != 1 && b != p - 1) // ��������� ������� ��� ������-�����������.
            return false;
        if (pow_mod(F, (p - 1) / 2, p) != 1) // ��������� ������� ��� ������-�����������.
            return false;
    }
    return true; // ���� ����� ���� �������� �������� ��������, ����� �������� �������.
}


long long gost_31_10_94(long long q, int t) { // ������� ��� ��������� ����� �� ��������� ���� 34.10-94.
    long long N = ((pow(2, t - 1)) / q) + 1; // ���������� �������� N �� �������� ����������.
    if (N % 2 != 0) // ���� N ��������, ����������� ��� �� 1.
        N++;
    long long u = 0; // ������������� ���������� u.
    while (true) { // ����������� ����.
        long long p = (N + u) * q + 1; // ���������� ����� p �� ������� ����.
        if (p > pow(2, t)) // ���� p ������ 2^t, ������� �� �����.
            break;
        if (pow_mod(2, p - 1, p) == 1 && pow_mod(2, N + u, p) != 1) // �������� ������� ����.
            return p; // ���������� ��������� ������� ����� p.
        u += 2; // ����������� u �� 2.
    }
}

vector<long long> generate_primes_miller(int length, const vector<long long>& primes_table) { // ������� ��� ��������� ������� ����� ������� �������.
    vector<long long> primes; // ������������� ������� ��� �������� ������� �����.
    while (primes.size() < 10) { // ���� �� ������������� 10 ������� �����.
        long long candidate = primes_table[rand() % primes_table.size()]; // ����� ��������� �� ������� ������� �����.
        if (to_string(candidate).length() == length && miller_rabin(candidate)) // �������� ������� ������ �������.
            primes.push_back(candidate); // ���������� �������� ����� � ������.
    }
    return primes; // ����������� ������� ��������������� ������� �����.
}

vector<long long> generate_primes_pocklington(int length, const vector<long long>& primes_table) { // ������� ��� ��������� ������� ����� ������� ������-�����������.
    vector<long long> primes; // ������������� ������� ��� �������� ������� �����.
    while (primes.size() < 10) { // ���� �� ������������� 10 ������� �����.
        long long candidate = primes_table[rand() % primes_table.size()]; // ����� ��������� �� ������� ������� �����.
        if (to_string(candidate).length() == length) { // �������� ����� �����.
            long long R = rand() % 3 + 1; // ��������� ���������� �������� R.
            long long F = rand() % 4 + 3; // ��������� ���������� �������� F.
            if (lehmann_pocklington(candidate, R, F)) // �������� ������� ������ ������-�����������.
                primes.push_back(candidate); // ���������� �������� ����� � ������.
        }
    }
    return primes; // ����������� ������� ��������������� ������� �����.
}

vector<long long> generate_primes_gost(int length, const vector<long long>& primes_table) { // ������� ��� ��������� ������� ����� �� ��������� ���� 34.10-94.
    vector<long long> primes; // ������������� ������� ��� �������� ������� �����.
    while (primes.size() < 10) { // ���� �� ������������� 10 ������� �����.
        long long candidate = primes_table[rand() % primes_table.size()]; // ����� ��������� �� ������� ������� �����.
        if (to_string(candidate).length() == length && gost_31_10_94(candidate, rand() % 3 + 1)) // �������� ������� ��������� ����.
            primes.push_back(candidate); // ���������� �������� ����� � ������.
    }
    return primes; // ����������� ������� ��������������� ������� �����.
}


vector<int> check_primality(const vector<long long>& primes, int iterations = 100) {
    vector<int> results; // �������� ������� ��� �������� ����������� �������� ��������.
    for (auto p : primes) { // ��� ������� �������� ����� �� �������� �������.
        int errors = 0; // ������������� �������� ������.
        for (int i = 0; i < iterations; i++) { // ��������� �������� �������� ���������� ���.
            if (!miller_rabin(p)) // ���� ����� �� �������� ���� �������-������.
                errors++; // ����������� ������� ������.
        }
        results.push_back(errors); // ��������� ���������� ������ � ����������.
    }
    return results; // ���������� ���������� �������� �������� ��� ���� �����.
}

vector<vector<string>> build_results_table(const vector<long long>& primes, const vector<int>& primality_results) {
    vector<vector<string>> table; // ������� ��������� ������ ��� �������� ������� �����������.
    table.push_back({ "#", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }); // ��������� ��������� ��������.
    table.push_back({ "P" }); // ��������� ��������� ������� � �������� �������.
    table.push_back({ "R" }); // ��������� ��������� ������� � ������������ ��������.
    table.push_back({ "K" }); // ��������� ��������� ������� � ����������� ������.
    for (size_t i = 0; i < primes.size(); i++) { // ��� ������� �������� ����� � ��� �����������.
        table[1].push_back(to_string(primes[i])); // ��������� ������� ����� � �������.
        table[2].push_back(primality_results[i] < 10 ? "+" : "-"); // ��������� ��������� �������� � �������.
        table[3].push_back(to_string(primality_results[i])); // ��������� ���������� ������ � �������.
    }
    return table; // ���������� ����������� ������� �����������.
}

vector<vector<int>> lehmann_pocklington_table(const vector<int>& numbers, const vector<int>& R_values, const vector<int>& F_values, int t = 100) {
    srand(time(nullptr)); // ������������� ���������� ��������� �����.
    vector<vector<int>> results; // �������� ���������� ������� ��� �������� �����������.
    for (int p : numbers) { // ��� ������� ����� �� �������� �������.
        int errors = 0; // ������������� �������� ������.
        for (int i = 0; i < t; ++i) { // ��������� �������� �������� ���������� ���.
            int R = R_values[rand() % R_values.size()]; // ��������� ���������� �������� R.
            int F = F_values[rand() % F_values.size()]; // ��������� ���������� �������� F.
            if (!lehmann_pocklington(p, R, F)) // ���� ����� �� �������� ���� ������-�����������.
                errors++; // ����������� ������� ������.
        }
        int error_probability = static_cast<double>(errors) / t; // ��������� ����������� ������.
        vector<int> row = { p, R_values[rand() % R_values.size()], error_probability }; // ������� ������ �����������.
        results.push_back(row); // ��������� ������ ����������� � �������.
    }
    return results; // ���������� ������� �����������.
}

vector<int> generate_gost_numbers(const vector<int>& qs, const vector<int>& ts) {
    vector<int> results; // �������� ������� ��� �������� �����������.
    for (size_t i = 0; i < qs.size(); ++i) { // ��� ������ ���� �������� q � t.
        int p = gost_31_10_94(qs[i], ts[i]); // ���������� ����� �� ��������� ���� 34.10-94.
        results.push_back(p); // ��������� ��������� � ������.
    }
    return results; // ���������� ������ ��������������� �����.
}


unordered_map<int, int> prime_factors(int n) {
    unordered_map<int, int> factors_count; // �������� �������������� ���������� ��� �������� ������� ���������� � �� ��������.
    while (n % 2 == 0) { // ���� ����� ������� �� 2 ��� �������.
        factors_count[2]++; // ����������� ������� �������� ��������� 2.
        n /= 2; // ������ ������� �� ������� ����� �� 2.
    }
    for (int i = 3; i <= sqrt(n); i += 2) { // ���������� �������� ����� �� 3 �� ����� �� n.
        while (n % i == 0) { // ���� ����� ������� �� ������� �������� i ��� �������.
            factors_count[i]++; // ����������� ������� �������� ��������� i.
            n /= i; // ������ ������� �� ������� ����� �� i.
        }
    }
    if (n > 2) // ���� ������� �� ������� ������ 2, �� ��� ������� ���������.
        factors_count[n]++; // ����������� ������� �������� ��������� n.
    return factors_count; // ���������� ������������� ��������� � �������� ����������� � �� ���������.
}

string factors_to_string(const unordered_map<int, int>& factors) {
    string factors_str = ""; // �������� ������ ��� ������������� ������� ���������� � �� ��������.
    for (const auto& factor : factors) { // ��� ������ ���� ����-�������� � ������������� ����������.
        if (factor.second > 1) // ���� ������� �������� ��������� ������ 1.
            factors_str += to_string(factor.first) + "^" + to_string(factor.second) + " * "; // ��������� � ������ ������� ��������� � ��� �������.
        else // ���� ������� �������� ��������� ����� 1.
            factors_str += to_string(factor.first) + " * "; // ��������� � ������ ������ ������� ���������.
    }
    return factors_str.substr(0, factors_str.length() - 3); // ���������� ������, ������ ��������� ��� ������� (������ � ���������).
}

vector<vector<int>> miller_rabin_table(const vector<int>& numbers) {
    vector<vector<int>> table; // ������� ��������� ������ ��� �������� ������� ����������� ����� �������-������.
    for (int p : numbers) { // ��� ������� ����� �� �������� �������.
        int errors = 0; // ������������� �������� ������.
        if (!miller_rabin(p)) // ���� ����� �� �������� ���� �������-������.
            errors++; // ����������� ������� ������.
        auto factors = prime_factors(p - 1); // �������� ������� ��������� ����� p - 1 � �� �������.
        int error_probability = 1.0 / pow(2, factors.size()); // ��������� ����������� ������.
        table.push_back({ p, error_probability }); // ��������� ���������� � �������.
    }
    return table; // ���������� ������� �����������.
}

vector<int> sieve_of_eratosthenes(int limit) {
    vector<bool> sieve(limit + 1, true); // ������� ������ ����������.
    vector<int> primes; // ������� ������ ��� �������� ������� �����.
    for (int p = 2; p * p <= limit; ++p) { // ���������� ����� �� 2 �� ����� �� limit.
        if (sieve[p]) { // ���� ������� ����� �������� �������.
            primes.push_back(p); // ��������� ��� � ������ ������� �����.
            for (int i = p * p; i <= limit; i += p) { // �������� ��� ������� �������� ����� ��� ���������.
                sieve[i] = false;
            }
        }
    }
    for (int p = (int)sqrt(limit) + 1; p <= limit; ++p) { // ��������� ���������� ������� ����� � ������.
        if (sieve[p]) {
            primes.push_back(p);
        }
    }
    return primes; // ���������� ������ ������� �����.
}

vector<int> generate_primes_miller(int length, const vector<int>& primes_table) {
    vector<int> primes; // ������� ������ ��� �������� ��������������� ������� �����.
    int attempts = 0; // �������������� ������� ������� ���������.
    while (primes.size() < 10 && attempts < 1000) { // ���� �� ������������� 10 ������� ����� ��� �� ��������� ������������ ���������� �������.
        int candidate = primes_table[rand() % primes_table.size()]; // �������� ��������� ����� �� ������� ������� �����.
        if (to_string(candidate).length() == length && miller_rabin(candidate)) { // ���� ����� ����� ������������� �������� � ��� �������� ���� �������-������.
            primes.push_back(candidate); // ��������� ��� � ������.
        }
        attempts++; // ����������� ������� �������.
    }
    return primes; // ���������� ������ ��������������� ������� �����.
}

vector<int> generate_primes_pocklington(int length, const vector<int>& primes_table) {
    vector<int> primes; // ������� ������ ��� �������� ��������������� ������� �����.
    int attempts = 0; // �������������� ������� ������� ���������.
    while (primes.size() < 10 && attempts < 1000) { // ���� �� ������������� 10 ������� ����� ��� �� ��������� ������������ ���������� �������.
        int candidate = primes_table[rand() % primes_table.size()]; // �������� ��������� ����� �� ������� ������� �����.
        if (to_string(candidate).length() == length) { // ���� ����� ����� ������������� ��������.
            int R = rand() % 3 == 0 ? 4 : (rand() % 3 == 1 ? 7 : 15); // ���������� �������� R.
            int F = rand() % 4 == 0 ? 3 : (rand() % 3 == 1 ? 4 : (rand() % 2 == 0 ? 8 : 20)); // ���������� �������� F.
            if (lehmann_pocklington(candidate, R, F)) { // ���� ����� �������� ���� ������-�����������.
                primes.push_back(candidate); // ��������� ��� � ������.
            }
        }
        attempts++; // ����������� ������� �������.
    }
    return primes; // ���������� ������ ��������������� ������� �����.
}

vector<int> generate_primes_gost(int length, const vector<int>& primes_table) {
    vector<int> primes; // ������� ������ ��� �������� ��������������� ������� �����.
    int attempts = 0; // �������������� ������� ������� ���������.
    while (primes.size() < 10 && attempts < 1000) { // ���� �� ������������� 10 ������� ����� ��� �� ��������� ������������ ���������� �������.
        int candidate = primes_table[rand() % primes_table.size()]; // �������� ��������� ����� �� ������� ������� �����.
        if (to_string(candidate).length() == length && gost_31_10_94(candidate, rand() % 3 == 0 ? 4 : (rand() % 3 == 1 ? 7 : 15)) != -1) { // ���� ����� ����� ������������� �������� � ��� �������� �������� ���� 34.10-94.
            primes.push_back(candidate); // ��������� ��� � ������.
        }
        attempts++; // ����������� ������� �������.
    }
    return primes; // ���������� ������ ��������������� ������� �����.
}

// �������� ������� ����� �� �������� � ������� �������������� �����
vector<int> check_primality(const vector<int>& primes, int iterations = 100) {
    vector<int> results; // ������� ������ ��� �������� ����������� �������� ��������.
    for (int p : primes) { // ��� ������� �������� ����� �� �������� �������.
        int errors = 0; // �������������� ������� ������.
        for (int i = 0; i < iterations; ++i) { // ��������� �������� �������� ���������� ���.
            if (!miller_rabin(p)) { // ���� ����� �� �������� ���� �������-������.
                errors += 1; // ����������� ������� ������.
            }
        }
        results.push_back(errors); // ��������� ���������� ������ � ����������.
    }
    return results; // ���������� ���������� �������� �������� ��� ���� �����.
}

// ���������� ������ �����������
vector<vector<string>> build_results_table(const vector<int>& primes, const vector<int>& primality_results) {
    vector<vector<string>> table(4, vector<string>(11)); // ������� ��������� ������ ��� �������� ������� �����������.
    table[0][0] = "#"; // ��������� ������� � ����������� ��������.
    table[1][0] = "P"; // ��������� ������� � �������� �������.
    table[2][0] = "R"; // ��������� ������� � ������������ ��������.
    table[3][0] = "K"; // ��������� ������� � ����������� ������.
    int num_primes = primes.size(); // �������� ���������� ��������� ������� �����.
    for (int i = 0; i < 10; ++i) { // ��� ������ ������ �������.
        table[0][i + 1] = to_string(i + 1); // ��������� ���������� ������.
        if (i < num_primes) { // ���������, ��� ������ � �������� ������� �������.
            table[1][i + 1] = to_string(primes[i]); // ��������� ������� � �������� �������.
        }
        else {
            table[1][i + 1] = ""; // ���� ������� ����� �� �������, ��������� ������ ������.
        }
        table[2][i + 1] = i < num_primes && primality_results[i] < 0.1 ? "+" : "-"; // ��������� ������� � ������������ ��������.
        table[3][i + 1] = i < num_primes ? to_string(primality_results[i]) : ""; // ��������� ������� � ����������� ������.
    }
    return table; // ���������� ����������� ������� �����������.
}


int main() {
    setlocale(LC_ALL, "Russian"); // ������������� ������ ��� ����������� ����������� �������� ������.

    vector<int> miller_numbers = { 13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373 }; // ������ ������ ����� ��� ����� �������-������.
    auto miller_table = miller_rabin_table(miller_numbers); // �������� ������� ����������� ����� �������-������.
    cout << "���������� ����� �������-������:" << endl; // ������� ��������� �������.
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.
    cout << setw(15) << left << "������� ����� p" << setw(20) << left << "���������� (p - 1)" << setw(25) << left << "����������� ������" << endl; // ������� ��������� ��������.
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.
    for (const auto& row : miller_table) { // ��� ������ ������ � ������� �����������.
        int p = row[0]; // �������� ������� �����.
        auto factors = prime_factors(p - 1); // �������� ������� ��������� ����� p - 1.
        string factors_str = factors_to_string(factors); // ����������� ��������� � ������.
        double error = row[1]; // �������� ����������� ������.
        cout << setw(15) << left << p << setw(20) << left << factors_str << setw(25) << left << error << endl; // ������� ������ � �����, ��� ���������� � ����������� ������.
    }
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.

    vector<int> pocklington_numbers = { 13, 29, 61, 97, 157, 173, 179, 353, 419, 461, 617, 821, 1069, 5953, 6121, 6197, 6373 }; // ������ ������ ����� ��� ����� ������-�����������.
    vector<int> R_values = { 4, 7, 15, 12, 13, 43, 89, 22, 209, 23, 77, 41, 89, 93, 85, 1549, 177 }; // ������ ������ �������� R.
    vector<int> F_values = { 3, 4, 4, 8, 8, 4, 2, 16, 2, 20, 8, 20, 8, 20, 12, 64, 72, 4, 36 }; // ������ ������ �������� F.
    int iterations = 100; // ������ ���������� ��������.
    auto pocklington_table = lehmann_pocklington_table(pocklington_numbers, R_values, F_values, iterations); // �������� ������� ����������� ����� ������-�����������.
    cout << "���������� ����� ������-�����������:" << endl; // ������� ��������� �������.
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.
    cout << setw(15) << left << "������� ����� p" << setw(20) << left << "���������� F" << setw(10) << left << "R" << setw(25) << left << "����������� ������" << endl; // ������� ��������� ��������.
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.
    for (const auto& row : pocklington_table) { // ��� ������ ������ � ������� �����������.
        auto factors = prime_factors(row[0] - 1); // �������� ������� ��������� ����� p - 1.
        string factors_str = factors_to_string(factors); // ����������� ��������� � ������.
        cout << setw(15) << left << row[0] << setw(20) << left << factors_str << setw(10) << left << row[1] << setw(25) << left << row[2] << endl;
    }
    cout << "---------------------------------------------------------------------" << endl; // ������� �������������� ������.

    // ������� �������� q � t ��� ��������� ���� 31.10-94
    vector<int> gost_qs = { 3, 5, 7, 5, 11, 11, 13, 13, 17, 17, 19, 23, 29, 31, 37, 41, 19, 23 }; // ������ �������� q.
    vector<int> gost_ts = { 4, 6, 5, 5, 7, 8, 7, 8, 9, 10, 9, 9, 9, 9, 11, 11, 10, 10 }; // ������ �������� t.

    vector<int> gost_results = generate_gost_numbers(gost_qs, gost_ts); // �������� ������� ����� �� ��������� ���� 31.10-94.

    // ����� �����������
    cout << "\n���������� ���� 31.10-94:\n"; // ������� ��������� �������.
    cout << "---------------------------------------------------------------------\n"; // ������� �������������� ������.
    cout << "q\tt\t������� ����� p\n"; // ������� ��������� ��������.
    cout << "---------------------------------------------------------------------\n"; // ������� �������������� ������.
    for (size_t i = 0; i < gost_qs.size(); ++i) { // ��� ������ ���� �������� q � t.
        cout << gost_qs[i] << "\t" << gost_ts[i] << "\t" << gost_results[i] << "\n"; // ������� �������� q, t � ���������� ������� ����� p.
    }
    cout << "---------------------------------------------------------------------\n"; // ������� �������������� ������.


    srand(time(0));

    // ���������� ������� ������� ����� ������ 500
    vector<int> primes_table = sieve_of_eratosthenes(500);

    // ��������� 10 ������� ����� ����� 3 �� ������ ����� �������
    vector<int> primes_miller = generate_primes_miller(3, primes_table);
    // ��������� 10 ������� ����� ����� 3 �� ������ ����� �����������
    vector<int> primes_pocklington = generate_primes_pocklington(3, primes_table);
    // ��������� 10 ������� ����� ����� 3 �� ������ ���� � 34.10-94
    vector<int> primes_gost = generate_primes_gost(3, primes_table);

    // �������� ������� ����� �� �������� � ������� �������������� �����
    vector<int> primality_results_miller = check_primality(primes_miller);
    vector<int> primality_results_pocklington = check_primality(primes_pocklington);
    vector<int> primality_results_gost = check_primality(primes_gost);

    // ���������� ������ �����������
    vector<vector<string>> results_table_miller = build_results_table(primes_miller, primality_results_miller);
    vector<vector<string>> results_table_pocklington = build_results_table(primes_pocklington, primality_results_pocklington);
    vector<vector<string>> results_table_gost = build_results_table(primes_gost, primality_results_gost);

    // ����� �����������
    cout << "������� ����� ����� 3, ���������� �� ������ ����� �������:" << endl; // ����� ��������� ��� ����������� ����� �������.
    for (const auto& row : results_table_miller) { // ��� ������ ������ � ������� ����������� ����� �������.
        for (const auto& cell : row) { // ��� ������ ������ � ������.
            cout << cell << "\t"; // ������� ���������� ������ � ����������.
        }
        cout << endl; // ��������� �� ����� ������ ����� ������ ������ ������ �������.
    }
    cout << "\n������� ����� ����� 3, ���������� �� ������ ����� �����������:" << endl; // ����� ��������� ��� ����������� ����� �����������.
    for (const auto& row : results_table_pocklington) { // ��� ������ ������ � ������� ����������� ����� �����������.
        for (const auto& cell : row) { // ��� ������ ������ � ������.
            cout << cell << "\t"; // ������� ���������� ������ � ����������.
        }
        cout << endl; // ��������� �� ����� ������ ����� ������ ������ ������ �������.
    }
    cout << "\n������� ����� ����� 3, ���������� �� ������ ���� � 34.10-94:" << endl; // ����� ��������� ��� ����������� ���� � 34.10-94.
    for (const auto& row : results_table_gost) { // ��� ������ ������ � ������� ����������� ���� � 34.10-94.
        for (const auto& cell : row) { // ��� ������ ������ � ������.
            cout << cell << "\t"; // ������� ���������� ������ � ����������.
        }
        cout << endl; // ��������� �� ����� ������ ����� ������ ������ ������ �������.
    }


    return 0;
}