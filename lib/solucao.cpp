#include "solucao.h"

using namespace std;

void exibirSolucao(Solution& s) {
    for (int i = 0; i < s.sequencia.size() - 1; i++) {
        cout << s.sequencia[i] << " -> ";
    }
    cout << s.sequencia.back() << endl;
}

void calcularValorObj(Solution& s, Graph& g) {
    s.valorObj = 0;
    for (int i = 0; i < s.sequencia.size() - 1; i++) {
        s.valorObj += g.adj[s.sequencia[i]][s.sequencia[i+1]];
    }
}