#include "perturbacao.h"

void selecionarIndices(int &start1, int &start2, int &s1, int &s2, int &end1, int &end2, int len)
{

    s1 = max((rand() % (len / 10)), 2);
    s2 = max((rand() % (len / 10)), 2);

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

    vector<int> subSeq1(s.sequencia.begin() + start1, s.sequencia.begin() + end1 + 1);
    vector<int> subSeq2(s.sequencia.begin() + start2, s.sequencia.begin() + end2 + 1);

    start2 -= s1;
    end2 -= s1;

    s.sequencia.erase(s.sequencia.begin() + start1, s.sequencia.begin() + end1 + 1);
    s.sequencia.erase(s.sequencia.begin() + start2, s.sequencia.begin() + end2 + 1);

    s.sequencia.insert(s.sequencia.begin() + start1, subSeq2.begin(), subSeq2.end());
    s.sequencia.insert(s.sequencia.begin() + start2 + s2, subSeq1.begin(), subSeq1.end());

    calcularValorObj(s, g);

    return s;
}