#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <bits/stdc++.h>
#include "solucao.h"

using namespace std;

struct InsertionInfo
{
    int no;
    double distance_to_r;

    bool operator<(InsertionInfo other) const
    {
        return distance_to_r < other.distance_to_r;
    }
};

set<int> nosRestantes(vector<int> &, int);
vector<InsertionInfo> calcularDistancia(vector<int> &, set<int> &, Data &);
Solution construcao(Data &);

#endif