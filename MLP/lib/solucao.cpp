#include "solucao.h"

using namespace std;

void exibirSolucao(Solution &s)
{
    for (int i = 0; i < s.sequencia.size() - 1; i++)
    {
        cout << s.sequencia[i] << " -> ";
    }
    cout << s.sequencia.back() << endl;

    cout << "custo total = " << s.matriz_Seq[0][s.sequencia.size() - 1].T << endl;
    cout << "latencia total = " << s.matriz_Seq[0][s.sequencia.size() - 1].C << endl;
}

void updateAllSubseq(Solution &s, Data &data)
{
    int n = s.sequencia.size();

    if (s.matriz_Seq.size() == 0)
    {
        s.matriz_Seq.resize(n);
        for (int i = 0; i < n; i++)
        {
            s.matriz_Seq[i].resize(n);
        }
    }

    for (int i = 0; i < n; i++)
    {
        int v = s.sequencia[i];
        s.matriz_Seq[i][i].W = (i > 0);
        s.matriz_Seq[i][i].C = 0;
        s.matriz_Seq[i][i].T = 0;
        s.matriz_Seq[i][i].first = v;
        s.matriz_Seq[i][i].last = v;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            s.matriz_Seq[i][j] = Subsequence::Concatenate(s.matriz_Seq[i][j - 1], s.matriz_Seq[j][j], data);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            s.matriz_Seq[i][j] = Subsequence::Concatenate(s.matriz_Seq[i][j + 1], s.matriz_Seq[j][j], data);
        }
    }

    s.latTotal = s.matriz_Seq[0][s.sequencia.size() - 1].C;
    s.custoTotal = s.matriz_Seq[0][s.sequencia.size() - 1].T;
}