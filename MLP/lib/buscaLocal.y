#include "buscaLocal.h"

bool bestImprovementSwap(Solution &s, Data &data)
{
    double bestDelta = 0;
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

            double delta;

            if (j == i + 1)
            {
                delta = data.getDistance(vi_prev, vj) + data.getDistance(vi, vj_next) - data.getDistance(vi_prev, vi) - data.getDistance(vj, vj_next);
            }
            else
            {
                delta = 0 - data.getDistance(vi_prev, vi) - data.getDistance(vi, vi_next);
                delta = delta - data.getDistance(vj_prev, vj) - data.getDistance(vj, vj_next);
                delta = delta + data.getDistance(vi_prev, vj) + data.getDistance(vj, vi_next);
                delta = delta + data.getDistance(vj_prev, vi) + data.getDistance(vi, vj_next);
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

bool bestImprovement20pt(Solution &s, Data &data)
{
    double bestDelta = 0;
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

            double delta = data.getDistance(prev_i, cur_j) + data.getDistance(cur_i, prox_j);
            delta -= data.getDistance(prev_i, cur_i) + data.getDistance(cur_j, prox_j);

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

bool bestImprovement0r0pt(Solution &s, Data &data, int len)
{
    double bestDelta = 0;
    int best_j, best_i;
    const int size = s.sequencia.size();

    for (int i = 1; i < size - len; i++)
    {
        int seq_l = s.sequencia[i];
        int seq_r = s.sequencia[i + len - 1];
        int prev_seq = s.sequencia[i - 1];
        int prox_Seq = s.sequencia[i + len];

        double custo_i = (-data.getDistance(prev_seq, seq_l)) - data.getDistance(seq_r, prox_Seq);

        for (int j = 1; j < size - 1; j++)
        {
            if (j == i)
            {
                j += len - 1;
                continue;
            }

            double delta;
            int spot, spot_next;

            if (j < i)
            {
                spot = s.sequencia[j - 1];
                spot_next = s.sequencia[j];
            }
            else
            {
                spot = s.sequencia[j];
                spot_next = s.sequencia[j + 1];
            }

            delta = custo_i - data.getDistance(spot, spot_next);
            delta += data.getDistance(prev_seq, prox_Seq) + data.getDistance(spot, seq_l) + data.getDistance(seq_r, spot_next);

            if (delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }

            if (j == i - 1)
            {
                j += len;
            }
        }
    }

    if (bestDelta < 0)
    {
        if (best_j < best_i)
        {
            rotate(s.sequencia.begin() + best_j, s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + len);
        }
        else
        {
            rotate(s.sequencia.begin() + best_i, s.sequencia.begin() + best_i + len, s.sequencia.begin() + best_j + 1);
        }

        s.valorObj += bestDelta;
        return true;
    }

    return false;
}

void buscaLocal(Solution &s, Data &data)
{
    vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while (!NL.empty())
    {
        int n = rand() % NL.size();

        switch (NL[n])
        {
        case 1:
            improved = bestImprovementSwap(s, data);
            break;
        case 2:
            improved = bestImprovement20pt(s, data);
            break;
        case 3:
            improved = bestImprovement0r0pt(s, data, 1);
            break;
        case 4:
            improved = bestImprovement0r0pt(s, data, 2);
            break;
        case 5:
            improved = bestImprovement0r0pt(s, data, 3);
            break;
        }

        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}