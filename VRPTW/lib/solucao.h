#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <bits/stdc++.h>
#include "instance.h"

using namespace std;

typedef struct
{
    vector<vector<int>> routes;
    double valorObj;
} Solution;

void exibirSolucao(Solution &);
// void calcularValorObj(Solution &, Instance &);

#endif