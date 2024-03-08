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

Solution perturbacao(Solution &sequenciaPrev, Data &data)
{
    Solution s = sequenciaPrev;

    int len = s.sequencia.size();

    int s1, s2, end1, end2;
    int start1, start2;

    selecionarIndices(start1, start2, s1, s2, end1, end2, len);

    int prev_i_1 = s.sequencia[start1 - 1];
    int prev_i_2 = s.sequencia[start2 - 1];
    int prox_j_1 = s.sequencia[end1 + 1];
    int prox_j_2 = s.sequencia[end2 + 1];
    int seq_l_1 = s.sequencia[start1];
    int seq_l_2 = s.sequencia[start2];
    int seq_r_1 = s.sequencia[end1];
    int seq_r_2 = s.sequencia[end2];

    if (end1 + 1 == start2)
    {
        s.valorObj -= data.getDistance(prev_i_1, seq_l_1) + data.getDistance(seq_r_1, seq_l_2) + data.getDistance(seq_r_2, prox_j_2);
        s.valorObj += data.getDistance(prev_i_1, seq_l_2) + data.getDistance(seq_r_2, seq_l_1) + data.getDistance(seq_r_1, prox_j_2);
    }
    else
    {
        s.valorObj -= data.getDistance(prev_i_1, seq_l_1) + data.getDistance(seq_r_1, prox_j_1) + data.getDistance(prev_i_2, seq_l_2) + data.getDistance(seq_r_2, prox_j_2);
        s.valorObj += data.getDistance(prev_i_1, seq_l_2) + data.getDistance(seq_r_2, prox_j_1) + data.getDistance(prev_i_2, seq_l_1) + data.getDistance(seq_r_1, prox_j_2);
    }

    rotate(s.sequencia.begin() + start1, s.sequencia.begin() + end1 + 1, s.sequencia.begin() + end2 + 1);

    start2 -= s1;
    end2 -= s1;

    rotate(s.sequencia.begin() + start1, s.sequencia.begin() + start2, s.sequencia.begin() + end2 + 1);

    return s;
}