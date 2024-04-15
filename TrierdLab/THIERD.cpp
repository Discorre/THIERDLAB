//#include <iostream> // ����������� ���������� ��� �����/������ ����� �������.
//#include <vector> // ����������� ���������� ��� ������������� ��������.
//#include <numeric> // ����������� ���������� ��� ���������� ��������� �������� � ��������������������.
//#include <cmath> // ����������� ���������� ��� �������������� ��������.
//#include <stdexcept> // ����������� ���������� ��� ��������� ����������.
//
//using namespace std;// ������������� ������������ ������������ ����.
//
//// ��������� ��� �������� ������������� �������� �������������.
//struct ApproximationResult {
//    double a; // ����������� ������� ������.
//    double b; // ��������� ���� ��������� ������.
//};
//
//// ��������� ��� �������� ������������� ����������.
//struct CorrelationResult {
//    double correlation; // ����������� ����������.
//    double t_value; // �������� t-����������.
//};
//
//// ������� ��� ���������� �������� ������������� �� ������ ���������� ���������.
//ApproximationResult aproks(const vector<double>& x, const vector<double>& y);
//
//// ������� ��� ������� ������������ ���������� � t-����������.
//CorrelationResult korrel(const vector<double>& x, const vector<double>& y);
//
//// ������� ��� ������������� ��������� ����������� ���� �� ��������.
//vector<double> coffee(double T, double Ts, double r, int time);
//
//// ������� ��� ������ ������ � ����������� ���� �� ��������.
//void printCoffee(vector<double> temperatures, vector<double>times);
//
//// ������� ��� ������ ����������� ������������� � ����������.
//void printApproximationResult(ApproximationResult result);
//void printCorrelationResult(CorrelationResult result);
//
//int main() {
//    double T = 90; // ��������� ����������� ����
//    double Ts = 26; // ����������� �������
//    double r = 0.01; // ����������� ���������
//    int time = 60; // ��������� ������ � �������
//
//    vector<double> temperatures = coffee(T, Ts, r, time); // ������������� ��������� ����������� ����.
//
//    vector<double> times(time + 1);// ������ ��������� ����������.
//    iota(times.begin(), times.end(), 0);// ���������� ��������� ���������� �� 0 �� time.
//
//    ApproximationResult approx_result = aproks(times, temperatures);// ���������� �������� �������������.
//    CorrelationResult corr_result = korrel(times, temperatures);// ���������� ������������ ���������� � t-����������.
//
//    printApproximationResult(approx_result);// ����� ����������� �������������.
//    printCorrelationResult(corr_result);// ����� ����������� ����������.
//    printCoffee(temperatures, times);// ����� ������ � ����������� ���� �� ��������.
//
//    return 0;
//}
//
//// ���������� ������� ��� ���������� �������� ������������� �� ������ ���������� ���������.
//ApproximationResult aproks(const vector<double>& x, const vector<double>& y) {
//    double x_sum = accumulate(x.begin(), x.end(), 0.0);// ����� �������� �� ������� x.
//    double y_sum = accumulate(y.begin(), y.end(), 0.0);// ����� �������� �� ������� y.
//    double x2_sum = inner_product(x.begin(), x.end(), x.begin(), 0.0);// ����� ��������� �������� �� ������� x.
//    double xy_sum = inner_product(x.begin(), x.end(), y.begin(), 0.0);// ����� ������������ �������� �� �������� x � y.
//    size_t n = x.size();// ���������� ��������� � ������� x.
//
//    double a = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);// ���������� ������������ ������� ������.
//    double b = (y_sum - a * x_sum) / n;// ���������� ���������� ����� ��������� ������.
//
//    return { a, b };// ����������� ����������� �������������.
//}
//
//// ������� ��� ���������� �������� �������� ��������� �������.
//// ��������� ������ ������������ ����� � �������� ���������.
//// ���������� ������� �������� ��������� �������.
//double mean(const vector<double>& vec) {
//    // ������������ ����������� �������� accumulate ��� ������������ ���� ��������� �������.
//    // ��������� �������� ����� ������ ��� 0.0.
//    // ��������� ������� accumulate - ����� ���� ��������� �������.
//    // ����� ��������� ������� �� ���������� ��������� ������� (��� ������) ��� ��������� �������� ��������.
//    return accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
//}
//
//// ���������� ������� ��� ������� ������������ ���������� � t-����������.
//CorrelationResult korrel(const vector<double>& x, const vector<double>& y) {
//    if (x.size() != y.size() || x.empty()) {// �������� �� ���������� ������ � ��������� ��������.
//        throw invalid_argument("Vectors must be of the same size and not empty.");// ������ ����������, ���� ������� �� �����������.
//    }
//
//    double x_mean = mean(x); // ���������� �������� �������� ������� x.
//    double y_mean = mean(y);// ���������� �������� �������� ������� y.
//    double sum_xy = 0.0;// ������������� ���������� ��� ����� ������������ (x_i - x_mean) * (y_i - y_mean).
//    double sum_x2 = 0.0;// ������������� ���������� ��� ����� ��������� (x_i - x_mean).
//    double sum_y2 = 0.0;// ������������� ���������� ��� ����� ��������� (y_i - y_mean).
//    size_t n = x.size();// ���������� ��������� � ������� x
//
//    for (size_t i = 0; i < n; ++i) {// ���� �� ���� ��������� �������� x � y.
//        sum_xy += (x[i] - x_mean) * (y[i] - y_mean);// ���������� ����� ������������.
//        sum_x2 += (x[i] - x_mean) * (x[i] - x_mean); // ���������� ����� ��������� ��� x.
//        sum_y2 += (y[i] - y_mean) * (y[i] - y_mean); // ���������� ����� ��������� ��� y.
//    }
//
//    double r = sum_xy / (sqrt(sum_x2) * sqrt(sum_y2));// ���������� ������������ ����������.
//    double t = r * sqrt(n - 2) / sqrt(1 - r * r);// ���������� ������������ ����������.
//
//    return { r, t };// ����������� ����������� ����������.
//}
//// ���������� ������� ��� ������������� ��������� ����������� ���� �� ��������.
//vector<double> coffee(double T, double Ts, double r, int time) {
//    vector<double> temperatures;// ������������� ������� ��� �������� ����������.
//
//    for (int t = 0; t <= time; t++) {// ���� �� ���� ��������� ���������� �� 0 �� time.
//        double temperature = Ts + (T - Ts) * exp(-r * t);// ���������� ����������� ���� � ������ ������� t.
//        temperatures.push_back(temperature);// ���������� ����������� � ������.
//    }
//
//    return temperatures;// ����������� ������� ����������.
//}
//
//// ���������� ������� ��� ������ ������ � ����������� ���� �� ��������.
//void printApproximationResult(ApproximationResult result) {
//    cout << "Approximation Result:" << endl;// ���� �� ���� ��������� ������� ����������.
//    cout << "a: " << result.a << ", b = " << result.b << endl; // ����� ������� � ����������� ����.
//}
//
//void printCorrelationResult(CorrelationResult result) {
//    cout << "Correlation Result:" << endl;
//    cout << "Correlation: " << result.correlation << endl;
//    cout << "T-value: " << result.t_value << endl;
//}
//
//void printCoffee(vector<double> temperatures, vector<double>times) {
//    for (int i = 0; i < temperatures.size(); i++) {
//        cout << "Time - " << times[i] << ":  " << temperatures[i] << " C" << endl;
//    }
//}
