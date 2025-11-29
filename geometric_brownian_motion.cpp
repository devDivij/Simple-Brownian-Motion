#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
using namespace std;

void save_path(const vector<double> &A, const string &filename)
{
    ofstream out(filename);
    for (int i = 0; i < A.size(); ++i)
    {
        out << i << "," << A[i] << "\n";
    }
}
vector<double> brownian_motion(int n, double drift, double volatility)
{

    random_device rd;
    mt19937 gen(rd());
    vector<double> Z(n, 0.0);
    double dt = 1.0 / n;

    normal_distribution<double> dist(0.0, 1.0);
    for (int i = 0; i < n; ++i)
    {
        double z = dist(gen);
        Z[i] = z;
    }

    vector<double> S(n + 1, 1.0);

    for (int i = 1; i < n + 1; i++)
    {
        S[i] = S[i - 1] * exp((drift - pow(volatility, 2) / 2) * dt + volatility * sqrt(dt) * Z[i - 1]);
    }
    return S;
}

int main()
{

    auto GBM = brownian_motion(50, 1.0, 0.5);
    save_path(GBM, "plot.csv");
    return 0;
}