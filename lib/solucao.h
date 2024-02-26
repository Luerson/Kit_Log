#ifndef SOLUCAO_H
#define SOLUCAO_H


#include<bits/stdc++.h>

using namespace std;

typedef struct {
    vector<int> sequencia;
    long double valorObj;
}Solution;

typedef struct {
    vector<vector<long double>> adj;
}Graph;

void exibirSolucao(Solution&);
void calcularValorObj(Solution&, Graph&);


#endif