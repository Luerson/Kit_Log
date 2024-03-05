#include "construcao.h"

void escolher3NosAleatorios(vector<int> &subtour, int dimension)
{
    for (int i = 0; i < 3; i++)
    {
        int newVertex = rand() % dimension + 1;

        if (find(subtour.begin(), subtour.end(), newVertex) == subtour.end())
        {
            subtour.push_back(newVertex);
        }
        else
        {
            i--;
        }
    }
}

set<int> nosRestantes(vector<int> &subtour, int dimension)
{
    set<int> CL;

    for (int i = 1; i <= dimension; i++)
    {
        if (find(subtour.begin(), subtour.end(), i) == subtour.end())
        {
            CL.insert(i);
        }
    }

    return CL;
}

vector<InsertionInfo> calcularCustoInsercao(vector<int> &subtour, set<int> &naoUsados, Data &data)
{
    vector<InsertionInfo> candidates(naoUsados.size() * (subtour.size() - 1));
    int l = 0;

    for (auto vertice : naoUsados)
    {
        for (int j = 0; j < subtour.size() - 1; j++)
        {
            InsertionInfo candidate;

            candidate.noInserido = vertice;
            candidate.arestaRemovida = make_pair(j, j + 1);
            candidate.custo = data.getDistance(subtour[j], vertice) + data.getDistance(vertice, subtour[j + 1]) - data.getDistance(subtour[j], subtour[j + 1]);

            candidates[l] = candidate;
            l++;
        }
    }

    return candidates;
}

void inserirNaSolucao(vector<int> &subtour, InsertionInfo &no)
{
    subtour.insert(subtour.begin() + no.arestaRemovida.second, no.noInserido);
}

Solution construcao(Data &data)
{
    int dimension = data.getDimension();

    Solution s;

    s.sequencia.push_back(1);
    escolher3NosAleatorios(s.sequencia, dimension);
    s.sequencia.push_back(1);

    set<int> CL = nosRestantes(s.sequencia, dimension);

    while (!CL.empty())
    {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s.sequencia, CL, data);

        sort(custoInsercao.begin(), custoInsercao.end());
        double alpha = (double)rand() / RAND_MAX;
        int selecionado = rand() % max(((int)ceil(alpha * custoInsercao.size())), 1);

        inserirNaSolucao(s.sequencia, custoInsercao[selecionado]);

        CL.erase(custoInsercao[selecionado].noInserido);
    }

    calcularValorObj(s, data);

    return s;
}