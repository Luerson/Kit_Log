#include "Data.h"
#include "implements.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));

    Solution s;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    double totalTime = 0.0;

    auto start = std::chrono::steady_clock::now();

    s = ILS(50, (n >= 150 ? n / 2 : n), data);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = end - start;

    totalTime += elapsedTime.count();

    cout << fixed << setprecision(6) << "Tempo total: " << totalTime << " segundos" << std::endl;

    exibirSolucao(s);

    return 0;
}
