#include "buscaLocal.h"

bool bestImprovementSwap(Solution &s, Graph &g)
{
    long double bestDelta = 0;
    int best_i, best_j;
    const int size = s.sequencia.size();

    for (int i = 0; i < size - 1; i++)
    {
        int vi = s.sequencia[i];
        int vi_next = s.sequencia[i + 1];
        int vi_prev = s.sequencia[(i + size - 1) % size];

        for (int j = 1; i + j < size; j++)
        {
            int vj = s.sequencia[i + j];
            int vj_next = s.sequencia[(i + j + 1) % size];
            int vj_prev = s.sequencia[i + j - 1];

            long double delta;

            if (j == 1)
            {
                delta = g.adj[vi_prev][vj] + g.adj[vi][vj_next] - g.adj[vi_prev][vi] - g.adj[vj][vj_next];
            }
            else if (i == 0 && i + j == size - 1)
            {
                delta = g.adj[vj_prev][vi] + g.adj[vj][vi_next] - g.adj[vj_prev][vj] - g.adj[vi][vi_next];
            }
            else
            {
                delta = 0 - g.adj[vi_prev][vi] - g.adj[vi][vi_next];
                delta = delta - g.adj[vj_prev][vj] - g.adj[vj][vj_next];
                delta = delta + g.adj[vi_prev][vj] + g.adj[vj][vi_next];
                delta = delta + g.adj[vj_prev][vi] + g.adj[vi][vj_next];
            }

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = i + j;
            }
        }
    }

    if (bestDelta < 0)
    {
        swap(s.sequencia[best_i], s.sequencia[best_j]);

        s.valorObj += bestDelta;

        return true;
    }
    return false;
}

bool bestImprovement20pt(Solution &s, Graph &g)
{
    long double bestDelta = 0;
    int best_j, best_i;
    const int size = s.sequencia.size();

    for (int i = 0; i < size - 1; i++)
    {
        int prev_i = s.sequencia[(i + size - 1) % size];
        int cur_i = s.sequencia[i];
        for (int j = 1; j < size - 2; j++)
        {
            int cur_j = s.sequencia[(i + j - 1) % size];
            int prox_j = s.sequencia[(i + j) % size];

            long double delta = g.adj[prev_i][cur_j] + g.adj[cur_i][prox_j];
            delta -= g.adj[prev_i][cur_i] + g.adj[cur_j][prox_j];

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = (i + j - 1) % size;
            }
        }
    }

    if (bestDelta < 0)
    {
        for (int i = best_i, j = best_j; i < j; i = (i + 1) % size, j = (j + size - 1) % size)
        {
            swap(s.sequencia[i], s.sequencia[j]);
        }
        s.valorObj += bestDelta;
        return true;
    }

    return false;
}

bool bestImprovement0r0pt(Solution &s, Graph &g, int len)
{
    long double bestDelta = 0;
    int best_j, best_i;
    const int size = s.sequencia.size();

    for (int i = 0; i < size; i++)
    {
        int seq_l = s.sequencia[i];
        int seq_r = s.sequencia[(i + len - 1) % size];
        int prev_seq = s.sequencia[(i + size - 1) % size];
        int prox_Seq = s.sequencia[(i + len) % size];

        for (int j = 0; j < size; j++)
        {
            if ((i + len - 1) % size >= (i + size - 1) % size && j >= i - 1 && j <= i + len - 1)
                continue;
            else if ((i + len - 1) % size < (i + size - 1) % size && (j <= (i + len - 1) % size || j >= (i + size - 1) % size))
                continue;

            int spot = s.sequencia[j];
            int spot_next = s.sequencia[(j + 1) % size];

            long double delta;
            delta = g.adj[prev_seq][prox_Seq] - g.adj[prev_seq][seq_l] - g.adj[seq_r][prox_Seq];
            delta += g.adj[spot][seq_l] + g.adj[seq_r][spot_next];
            delta -= g.adj[spot][spot_next];

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if (bestDelta < 0)
    {
        for (int node = 0; node < len; node++)
        {
            for (int i = best_i; i != best_j; i = (i + 1) % size)
            {
                swap(s.sequencia[i], s.sequencia[(i + 1) % size]);
            }
        }
        s.valorObj += bestDelta;
        return true;
    }

    return false;
}

void buscaLocal(Solution &s, Graph &g)
{
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    s.sequencia.pop_back();

    while (!NL.empty())
    {
        int n = rand() % NL.size();

        switch (NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, g);
            break;
        case 2:
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
            break;
        }

        // cout << s.valorObj << endl;

        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
    s.sequencia.push_back(s.sequencia[0]);
}