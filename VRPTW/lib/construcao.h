#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <bits/stdc++.h>
#include "solucao.h"
#include "instance.h"

using namespace std;

struct InsertionInfo
{
    int noInserido;
    int correspond_rout;
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

bool feasible(Node &, Instance &, Solution &, pair<int, int>, int);
void preencherVazios(Instance &, vector<vector<int>> &, vector<int> &);
vector<int> iniciaCL(int);

int menorCusto(vector<int> &, Solution &, int, double, InsertionInfo &, Instance &);
void inserirNaSolucao(Solution &, InsertionInfo &, Instance &);

bool estrategiaSequencial(Solution &, Instance &, vector<int> &, INSERTION_CRITERIA);
bool estrategiaParalela(Solution &, Instance &, vector<int> &, INSERTION_CRITERIA);

Solution construcao(Instance &);

#endif