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

vector<int> nosRestantes(vector<int> &subtour, int dimension)
{
    vector<int> CL;

    for (int i = 1; i <= dimension; i++)
    {
        if (find(subtour.begin(), subtour.end(), i) == subtour.end())
        {
            CL.push_back(i);
        }
    }

    return CL;
}

vector<InsertionInfo> calcularCustoInsercao(vector<int> &subtour, vector<int> &naoUsados, Data &data)
{
    vector<InsertionInfo> candidates;

    for (int i = 0; i < naoUsados.size(); i++)
    {
        for (int j = 0; j < subtour.size() - 1; j++)
        {
            InsertionInfo candidate;

            candidate.noInserido = i;
            candidate.arestaRemovida = make_pair(j, j + 1);
            candidate.custo = data.getDistance(subtour[j], naoUsados[i]) + data.getDistance(naoUsados[i], subtour[j + 1]) - data.getDistance(subtour[j], subtour[j + 1]);

            candidates.push_back(candidate);
        }
    }

    return candidates;
}

void inserirNaSolucao(vector<int> &subtour, InsertionInfo &no, vector<int> naoUsados)
{
    subtour.insert(subtour.begin() + no.arestaRemovida.second, naoUsados[no.noInserido]);
}

Solution construcao(Data &data)
{
    int dimension = data.getDimension();

    Solution s;

    s.sequencia.push_back(1);
    escolher3NosAleatorios(s.sequencia, dimension);
    s.sequencia.push_back(1);

    vector<int> CL = nosRestantes(s.sequencia, dimension);

    while (!CL.empty())
    {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s.sequencia, CL, data);

        sort(custoInsercao.begin(), custoInsercao.end());
        double alpha = (double)rand() / RAND_MAX;
        int selecionado = rand() % max(((int)ceil(alpha * custoInsercao.size())), 1);

        inserirNaSolucao(s.sequencia, custoInsercao[selecionado], CL);

        CL.erase(CL.begin() + custoInsercao[selecionado].noInserido);
    }

    calcularValorObj(s, data);

    return s;
}