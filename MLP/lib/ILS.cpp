#include "ILS.h"

Solution ILS(int Imax, int Iils, Data &data)
{
    Solution bestOfAll;
    bestOfAll.latTotal = INFINITY;

    for (int i = 0; i < Imax; i++)
    {
        Solution s = construcao(data);

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