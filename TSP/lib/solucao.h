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

void exibirSolucao(Solution &);
void calcularValorObj(Solution &, Data &);

#endif