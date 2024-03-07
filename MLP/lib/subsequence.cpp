#include "subsequence.h"

using namespace std;

void updateAllSubseq(Solution &s, vector<vector<Subsequence>> &subseq_matrix)
{
    int n = s.sequencia.size();

    for (int i = 0; i < n; i++)
    {
        int v = s.sequencia[i];
        subseq_matrix[i][i].W = (i > 0);
        subseq_matrix[i][i].C = 0;
        subseq_matrix[i][i].T = 0;
        subseq_matrix[i][i].first = v;
        subseq_matrix[i][i].last = v;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j - 1], subseq_matrix[j][j]);
        }
    }

    for (int i = n - 1; i < n; i--)
    {
        for (int j = i - 1; j < n; j--)
        {
            subseq_matrix[i][j] = Subsequence::Concatenate(subseq_matrix[i][j + 1], subseq_matrix[j][j]);
        }
    }
}