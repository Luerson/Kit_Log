#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <bits/stdc++.h>
#include "../src/Data.h"

using namespace std;

typedef struct
{
    vector<int> sequencia;
    double valorObj;
} Solution;

typedef struct
{
    vector<vector<double>> adj;
} Graph;

void exibirSolucao(Solution &);
void calcularValorObj(Solution &, Graph &);

#endif