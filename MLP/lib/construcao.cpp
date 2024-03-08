#include "construcao.h"

set<int> nosRestantes(int dimension)
{
    set<int> CL;

    for (int i = 2; i <= dimension; i++)
    {
        CL.insert(i);
    }

    return CL;
}

vector<InsertionInfo> calcularDistancia(vector<int> &subtour, set<int> &naoUsados, Data &data)
{
    vector<InsertionInfo> candidates(naoUsados.size());
    int r = subtour.back();
    int l = 0;

    for (auto vertice : naoUsados)
    {
        InsertionInfo candidate;

        candidate.no = vertice;
        candidate.distance_to_r = data.getDistance(r, vertice);

        candidates[l] = candidate;
        l++;
    }

    return candidates;
}

Solution construcao(Data &data)
{
    int dimension = data.getDimension();

    Solution s;

    s.sequencia.push_back(1);

    set<int> CL = nosRestantes(dimension);

    while (!CL.empty())
    {
        vector<InsertionInfo> custoInsercao = calcularDistancia(s.sequencia, CL, data);

        sort(custoInsercao.begin(), custoInsercao.end());
        double alpha = ((double)(rand() % 26)) / 100.0;
        int selecionado = rand() % max(((int)ceil(alpha * custoInsercao.size())), 1);

        s.sequencia.push_back(custoInsercao[selecionado].no);

        CL.erase(custoInsercao[selecionado].no);
    }

    s.sequencia.push_back(1);

    updateAllSubseq(s, data);

    exibirSolucao(s);

    return s;
}