#include "Data.h"
#include "implements.h"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));

    Solution s;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    auto start = chrono::steady_clock::now();

    s = ILS(10, min(100, (int)n), data);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsedTime = end - start;

    cout << elapsedTime.count() << endl;

    cout << endl;
    cout << "chegou aqui" << endl;

    exibirSolucao(s);

    return 0;
}
