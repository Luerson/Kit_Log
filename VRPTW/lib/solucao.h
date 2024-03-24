#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <bits/stdc++.h>
#include "instance.h"

using namespace std;

typedef struct
{
    vector<vector<double>> maxDecreaseTime;
    vector<vector<double>> maxIncreaseTime;

    vector<vector<double>> arriveTime;

    vector<int> total_load;
} ADS;

typedef struct
{
    vector<vector<int>> routes;
    double valorObj;
    bool feasible;

    ADS ads;
} Solution;

void startADS(ADS &, int, int);
void exibirSolucao(Solution &);
void fillTimeArrive(Solution &, Instance &, ADS &, int);
void fillTotalLoad(Solution &, Instance &, ADS &, int);
void fillTimeChange(Solution &, Instance &, ADS &, int);
void calcularValorObj(Solution &, Instance &);

#endif