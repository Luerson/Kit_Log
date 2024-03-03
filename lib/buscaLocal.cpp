#include "buscaLocal.h"

bool bestImprovementSwap(Solution &s, Graph &g)
{
    long double bestDelta = 0;
    int best_i, best_j;
    const int size = s.sequencia.size();

    for (int i = 1; i < size - 1; i++)
    {
        int vi = s.sequencia[i];
        int vi_next = s.sequencia[i + 1];
        int vi_prev = s.sequencia[i - 1];

        for (int j = i + 1; j < size - 1; j++)
        {
            int vj = s.sequencia[j];
            int vj_next = s.sequencia[j + 1];
            int vj_prev = s.sequencia[j - 1];

            long double delta;

            if (j == i + 1)
            {
                delta = g.adj[vi_prev][vj] + g.adj[vi][vj_next] - g.adj[vi_prev][vi] - g.adj[vj][vj_next];
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
                best_j = j;
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

    for (int i = 1; i < size - 1; i++)
    {
        int prev_i = s.sequencia[i - 1];
        int cur_i = s.sequencia[i];

        for (int j = i + 1; j < size - 1; j++)
        {
            int cur_j = s.sequencia[j];
            int prox_j = s.sequencia[j + 1];

            long double delta = g.adj[prev_i][cur_j] + g.adj[cur_i][prox_j];
            delta -= g.adj[prev_i][cur_i] + g.adj[cur_j][prox_j];

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
        reverse(s.sequencia.begin() + best_i, s.sequencia.begin() + best_j + 1);
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

    for (int i = 1; i < size - len; i++)
    {
        int seq_l = s.sequencia[i];
        int seq_r = s.sequencia[i + len - 1];
        int prev_seq = s.sequencia[i - 1];
        int prox_Seq = s.sequencia[i + len];

        for (int j = 1; j < size; j++)
        {
            if (j >= i && j <= i + len)
                continue;

            long double delta;
            int spot, spot_next;

            spot = s.sequencia[j - 1];
            spot_next = s.sequencia[j];

            delta = (-g.adj[prev_seq][seq_l]) - g.adj[seq_r][prox_Seq] - g.adj[spot][spot_next];
            delta += g.adj[prev_seq][prox_Seq] + g.adj[spot][seq_l] + g.adj[seq_r][spot_next];

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
        vector<int> toReplace(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + len);
        if (best_j > best_i)
            best_j -= len;

        s.sequencia.erase(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + len);
        s.sequencia.insert(s.sequencia.begin() + best_j, toReplace.begin(), toReplace.end());

        s.valorObj += bestDelta;
        return true;
    }

    return false;
}

void buscaLocal(Solution &s, Graph &g)
{
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

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

        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}