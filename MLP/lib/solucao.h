#ifndef SOLUCAO_H
#define SOLUCAO_H

#include <bits/stdc++.h>
#include "../src/Data.h"

using namespace std;

struct Subsequence
{
    double T, C;
    int W;
    int first, last;
    inline static Subsequence Concatenate(Subsequence &sigma_1, Subsequence &sigma_2, Data &data)
    {
        Subsequence sigma;
        double temp = data.getDistance(sigma_1.last, sigma_2.first);
        sigma.W = sigma_1.W + sigma_2.W;
        sigma.T = sigma_1.T + temp + sigma_2.T;
        sigma.C = sigma_1.C + sigma_2.W * (sigma_1.T + temp) + sigma_2.C;
        sigma.first = sigma_1.first;
        sigma.last = sigma_2.last;

        return sigma;
    }
};

typedef struct
{
    vector<int> sequencia;
    vector<vector<Subsequence>> matriz_Seq;
    double latTotal;
    double custoTotal;
} Solution;

void exibirSolucao(Solution &);
void calcularValorObj(Solution &, Data &);
void updateAllSubseq(Solution &, Data &);

#endif