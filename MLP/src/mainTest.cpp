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

    s = ILS(10, min(100, (int)n), data);

    cout << endl;
    cout << "chegou aqui" << endl;

    exibirSolucao(s);

    return 0;
}
