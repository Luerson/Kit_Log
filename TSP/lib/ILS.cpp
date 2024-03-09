#include "ILS.h"

Solution ILS(int maxIter, int maxIterILS, Data &data)
{
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;

    for (int i = 0; i < maxIter; i++)
    {
        Solution s = construcao(data);

        Solution best = s;

        int iterILS = 0;

        while (iterILS <= maxIterILS)
        {
            buscaLocal(s, data);
            if (s.valorObj < best.valorObj)
            {
                best = s;
                iterILS = 0;
            }

            s = perturbacao(best, data);
            iterILS++;
        }

        if (best.valorObj < bestOfAll.valorObj)
        {
            bestOfAll = best;
        }
    }

    return bestOfAll;
}