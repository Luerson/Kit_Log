#include "construcao.h"

void preencherVazios(Instance &instancia, vector<vector<int>> &routes, vector<int> &CL)
{
    int size = instancia.totalVehicles;

    for (int i = 0; i < size; i++)
    {
        while (1)
        {
            int newIndex = rand() % CL.size();

            if (instancia.nodes[CL[newIndex]].demand <= instancia.capacity)
            {
                cout << CL[newIndex] << endl;
                routes[i].push_back(CL[newIndex]);
                CL.erase(CL.begin() + newIndex);
                break;
            }
        }
    }

    cout << endl;
    cout << endl;
}

vector<int> iniciaCL(int dimension)
{
    vector<int> CL;

    for (int i = 1; i < dimension; i++)
    {
        CL.push_back(i);
    }

    return CL;
}

/*vector<InsertionInfo> calcularCustoInsercao(vector<int> &subtour, set<int> &naoUsados, Data &data)
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
}*/

/*void inserirNaSolucao(vector<int> &subtour, InsertionInfo &no)
{
    subtour.insert(subtour.begin() + no.arestaRemovida.second, no.noInserido);
}*/

Solution construcao(Instance &instancia)
{
    int dimension = instancia.size;

    Solution s;
    s.routes.resize(instancia.totalVehicles);

    vector<int> CL = iniciaCL(dimension);

    preencherVazios(instancia, s.routes, CL);

    INSERTION_CRITERIA criterion = (rand() % 2 == 0 ? CHEAPEST_INS : NEAREST_NEIGH);
    INSERTION_STRATEGY strategy = (rand() % 2 == 0 ? SEQUENTIAL : PARALLEL);

    /*while (!CL.empty())
    {
        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s.routes, CL, instancia);

        sort(custoInsercao.begin(), custoInsercao.end());
        double alpha = (double)rand() / RAND_MAX;
        int selecionado = rand() % max(((int)ceil(alpha * custoInsercao.size())), 1);

        inserirNaSolucao(s.routes, custoInsercao[selecionado]);

        CL.erase(CL.begin() + custoInsercao[selecionado].noInserido);
    }

    calcularValorObj(s, data);*/

    return s;
}