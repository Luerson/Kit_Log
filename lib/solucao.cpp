#include "solucao.h"

using namespace std;

void exibirSolucao(Solution &s)
{
    for (int i = 0; i < s.sequencia.size() - 1; i++)
    {
        cout << s.sequencia[i] << " -> ";
    }
    cout << s.sequencia.back() << endl;

    cout << s.valorObj << endl;
}

void calcularValorObj(Solution &s, Data &data)
{
    s.valorObj = 0;
    for (int i = 0; i < s.sequencia.size() - 1; i++)
    {
        s.valorObj += data.getDistance(s.sequencia[i], s.sequencia[i + 1]);
    }
}