#include "buscaLocal.h"

bool bestImprovementSwap(Solution &s, Data &data)
{
    double bestDelta = 0;
    int best_i, best_j;

    const int size = s.sequencia.size();
    double totalLat = s.matriz_Seq[0][size - 1].C;

    for (int i = 1; i < size - 1; i++)
    {
        for (int j = i + 1; j < size - 1; j++)
        {
            Subsequence newSubseq = Subsequence::Concatenate(s.matriz_Seq[0][i - 1], s.matriz_Seq[j][j], data);
            double delta;

            if (j != i + 1)
            {
                newSubseq = Subsequence::Concatenate(newSubseq, s.matriz_Seq[i + 1][j - 1], data);
            }
            newSubseq = Subsequence::Concatenate(newSubseq, s.matriz_Seq[i][i], data);
            newSubseq = Subsequence::Concatenate(newSubseq, s.matriz_Seq[j + 1][size - 1], data);

            delta = newSubseq.C - totalLat;

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

        updateAllSubseq(s, data, best_i, best_j);

        return true;
    }
    return false;
}

bool bestImprovement20pt(Solution &s, Data &data)
{
    double bestDelta = 0;
    int best_j, best_i;

    const int size = s.sequencia.size();
    double totalLat = s.matriz_Seq[0][size - 1].C;

    for (int i = 1; i < size - 1; i++)
    {
        for (int j = i + 1; j < size - 1; j++)
        {
            Subsequence newSubSeq;
            double delta;

            newSubSeq = Subsequence::Concatenate(s.matriz_Seq[0][i - 1], s.matriz_Seq[j][i], data);
            newSubSeq = Subsequence::Concatenate(newSubSeq, s.matriz_Seq[j + 1][size - 1], data);
            delta = newSubSeq.C - totalLat;

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
        updateAllSubseq(s, data, best_i, best_j);
        return true;
    }

    return false;
}

bool bestImprovement0r0pt(Solution &s, Data &data, int len)
{
    double bestDelta = 0;
    int best_j, best_i;

    const int size = s.sequencia.size();
    double totalLat = s.matriz_Seq[0][size - 1].C;

    for (int i = 1; i < size - len; i++)
    {
        for (int j = 1; j < size - 1; j++)
        {
            if (j == i)
            {
                j += len - 1;
                continue;
            }

            Subsequence newSubSeq;
            double delta;

            if (j < i)
            {
                newSubSeq = Subsequence::Concatenate(s.matriz_Seq[0][j - 1], s.matriz_Seq[i][i + len - 1], data);
                newSubSeq = Subsequence::Concatenate(newSubSeq, s.matriz_Seq[j][i - 1], data);
                newSubSeq = Subsequence::Concatenate(newSubSeq, s.matriz_Seq[i + len][size - 1], data);
            }
            else
            {
                newSubSeq = Subsequence::Concatenate(s.matriz_Seq[0][i - 1], s.matriz_Seq[i + len][j], data);
                newSubSeq = Subsequence::Concatenate(newSubSeq, s.matriz_Seq[i][i + len - 1], data);
                newSubSeq = Subsequence::Concatenate(newSubSeq, s.matriz_Seq[j + 1][size - 1], data);
            }

            delta = newSubSeq.C;

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

        updateAllSubseq(s, data, (best_j < best_i ? best_j : best_i), (best_j < best_i ? best_i + len - 1 : best_j));
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