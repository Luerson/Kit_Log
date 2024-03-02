#include "Data.h"
#include "implements.h"
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char **argv)
{
    srand(time(NULL));

    Solution s;
    Graph myGraph;

    auto data = Data(argc, argv[1]);
    data.read();
    size_t n = data.getDimension();

    myGraph.adj.resize(n);
    for (int i = 0; i < n; i++)
    {
        myGraph.adj[i].resize(n);
        for (int j = 0; j < n; j++)
        {
            myGraph.adj[i][j] = data.getDistance(i + 1, j + 1);
        }
    }

    double totalTime = 0.0;

    auto start = std::chrono::steady_clock::now();

    s = ILS(50, (myGraph.adj.size() >= 150 ? myGraph.adj.size() / 2 : myGraph.adj.size()), myGraph);

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = end - start;

    totalTime += elapsedTime.count();

    cout << fixed << setprecision(3) << "Tempo total: " << totalTime << " segundos" << std::endl;

    exibirSolucao(s);

    return 0;
}
