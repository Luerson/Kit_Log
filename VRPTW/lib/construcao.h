#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <bits/stdc++.h>
#include "solucao.h"
#include "instance.h"

using namespace std;

struct InsertionInfo
{
    int noInserido;
    pair<int, int> arestaRemovida;
    double custo;

    bool operator<(InsertionInfo other) const
    {
        return custo < other.custo;
    }
};

enum INSERTION_CRITERIA
{
    CHEAPEST_INS,
    NEAREST_NEIGH
};

enum INSERTION_STRATEGY
{
    SEQUENTIAL,
    PARALLEL
};

// void escolher3NosAleatorios(vector<int> &, int);
// set<int> nosRestantes(vector<int> &, int);
// void inserirNaSolucao(vector<int> &, InsertionInfo &);
// vector<InsertionInfo> calcularCustoInsercao(vector<int> &, set<int> &, Data &);
void preencherVazios(Instance &, vector<vector<int>> &, vector<int> &);
vector<int> iniciaCL(int);
Solution construcao(Instance &);

#endif