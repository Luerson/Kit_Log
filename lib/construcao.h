#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <bits/stdc++.h>
#include "solucao.h"

using namespace std;

struct InsertionInfo
{
    int noInserido;
    pair<int, int> arestaRemovida;
    long double custo;

    bool operator<(InsertionInfo other) const
    {
        return custo < other.custo;
    }
};

void escolher3NosAleatorios(vector<int> &, int);
vector<int> nosRestantes(vector<int> &, int);
void inserirNaSolucao(vector<int> &, InsertionInfo &);
vector<InsertionInfo> calcularCustoInsercao(vector<int> &, vector<int> &, Data &);
Solution construcao(Data &);

#endif