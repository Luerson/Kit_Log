#include "ILS.h"

Solution ILS(int Imax, int Iils, Data &data)
{
    Solution bestOfAll;
    bestOfAll.latTotal = INFINITY;

    for (int i = 0; i < Imax; i++)
    {

        double alpha = ((double)(rand() % 26)) / 100.0;
        Solution s = construcao(data, alpha);

        Solution best = s;

        int iterILS = 0;

        while (iterILS <= Iils)
        {
            buscaLocal(s, data);
            if (s.latTotal < best.latTotal)
            {
                best = s;
                iterILS = 0;
            }

            s = perturbacao(best, data);
            iterILS++;
        }

        if (best.latTotal < bestOfAll.latTotal)
        {
            bestOfAll = best;
        }
    }

    return bestOfAll;
}