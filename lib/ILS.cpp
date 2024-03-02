#include "ILS.h"

Solution ILS(int maxIter, int maxIterILS, Graph &g)
{
    double totalTime = 0.0;
    double totalTime2 = 0.0;
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;

    for (int i = 0; i < maxIter; i++)
    {
        auto start2 = std::chrono::steady_clock::now();
        Solution s = construcao(g);
        auto end2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime2 = end2 - start2;

        totalTime2 += elapsedTime2.count();

        Solution best = s;

        int iterILS = 0;

        auto start = std::chrono::steady_clock::now();

        while (iterILS <= maxIterILS)
        {
            buscaLocal(s, g);
            if (s.valorObj < best.valorObj)
            {
                best = s;
                iterILS = 0;
            }

            s = perturbacao(best, g);
            iterILS++;
        }

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = end - start;

        totalTime += elapsedTime.count();

        if (best.valorObj < bestOfAll.valorObj)
        {
            bestOfAll = best;
        }
    }

    cout << fixed << setprecision(3) << "Tempo total: " << totalTime2 << " segundos" << std::endl;
    cout << fixed << setprecision(3) << "Tempo total: " << totalTime << " segundos" << std::endl;

    return bestOfAll;
}