#include "perturbacao.h"

void selecionarIndices(int &start1, int &start2, int &s1, int &s2, int &end1, int &end2, int len)
{

    s1 = (rand() % (len / 10)) + 1;
    s2 = (rand() % (len / 10)) + 1;

    start1 = rand() % (len - s1 - 1) + 1;
    end1 = start1 + s1 - 1;
    do
    {
        start2 = rand() % (len - s2 - 1) + 1;
        end2 = start2 + s2 - 1;
    } while (end1 >= start2 && start1 <= end2);

    if (start1 > start2)
    {
        swap(start1, start2);
        swap(end1, end2);
        swap(s1, s2);
    }
}

Solution perturbacao(Solution &sequenciaPrev, Graph &g)
{
    Solution s = sequenciaPrev;

    int len = s.sequencia.size();

    int s1, s2, end1, end2;
    int start1, start2;

    selecionarIndices(start1, start2, s1, s2, end1, end2, len);

    int swaps1 = start2 - end1 - 1;
    int swaps2 = end2 - start1;

    for (int i = s2; i > 0; i--)
    {
        for (int j = 0; j < swaps2; j++)
        {
            swap(s.sequencia[end2 - j], s.sequencia[end2 - j - 1]);
        }
        start1++;
        end1++;
    }

    for (int i = s1; i > 0; i--)
    {
        for (int j = 0; j < swaps1; j++)
        {
            swap(s.sequencia[start1 + j], s.sequencia[start1 + j + 1]);
        }
    }

    calcularValorObj(s, g);

    return s;
}