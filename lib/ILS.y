#include "ILS.h"

Solution ILS(int maxIter, int maxIterILS, Graph& g) {
    Solution bestOfAll;
    bestOfAll.valorObj = INFINITY;

    for (int i = 0; i < maxIter; i++) {
        Solution s = construcao(g);
        Solution best = s;

        int iterILS = 0;

        while (iterILS <= maxIterILS) {
            buscaLocal(s, g);
            if (s.valorObj < best.valorObj) {
                best = s;
                iterILS = 0;
            }

            s = perturbacao(best);
            iterILS++;
        }

        if (best.valorObj < bestOfAll.valorObj) {
            bestOfAll = best;
        }
    }

    return bestOfAll;
}