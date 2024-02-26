#include "buscaLocal.h"

bool bestImprovementSwap(Solution& s, Graph& g) {
    long double bestDelta = 0;
    int best_i, best_j;

    for (int i = 1; i < s.sequencia.size() - 1; i++) {
        int vi = s.sequencia[i];
        int vi_next = s.sequencia[i+1];
        int vi_prev = s.sequencia[i-1];

        for (int j = i + 2; j < s.sequencia.size() - 1; j++) {
            int vj = s.sequencia[j];
            int vj_next = s.sequencia[j + 1];
            int vj_prev = s.sequencia[j - 1];

            /*if (i == 1 && j == 2) {
                cout << endl;
                cout << vi_prev << " " << vi << endl;
                cout << vi << " " << vi_next << endl;
                cout << vj_prev << " " << vj << endl;
                cout << vj << " " << vj_next << endl;
                cout << g.adj[vi_prev][vi] << " " << g.adj[vi][vi_next] << endl;
                cout << g.adj[vj_prev][vj] << " " << g.adj[vj][vj_next] << endl;
                cout << g.adj[vi_prev][vj] << " " << g.adj[vj][vi_next] << endl;
                cout << g.adj[vj_prev][vi] << " " << g.adj[vi][vj_next] << endl;
            }*/

            long double delta = 0 - g.adj[vi_prev][vi] - g.adj[vi][vi_next];
            delta = delta - g.adj[vj_prev][vj] - g.adj[vj][vj_next];
            delta = delta + g.adj[vi_prev][vj] + g.adj[vj][vi_next];
            delta = delta + g.adj[vj_prev][vi] + g.adj[vi][vj_next];
            
            if (delta < bestDelta) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    //cout << endl << "best delta = " << bestDelta << endl;

    if (bestDelta < 0) {
        swap(s.sequencia[best_i], s.sequencia[best_j]);
        s.valorObj += bestDelta;

        cout << "custo apos swap = " << s.valorObj << endl;
        cout << "best_i = " << s.sequencia[best_i] << "; best_j = " << s.sequencia[best_j] << endl;

        return true;
    }
    return false;
}

void buscaLocal(Solution& s, Graph& g) {
    vector<int> NL = {1};
    bool improved = false;

    while (!NL.empty()) {
        int n = rand() % NL.size();

        switch (NL[n]) {
            case 1:
                improved = bestImprovementSwap(s, g);
                break;
            /*case 2:
                improved = bestImprovement20pt(s, g);
                break;
            case 3:
                improved = bestImprovement0r0pt(s, g, 1);
                break;
            case 4:
                improved = bestImprovement0r0pt(s, g, 2);
                break;
            case 5:
                improved = bestImprovement0r0pt(s, g, 3);
                break;*/
        }

        if (improved)
            NL = {1};
        else
            NL.erase(NL.begin() + n);
    }
}