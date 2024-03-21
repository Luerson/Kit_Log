#include "solucao.h"

using namespace std;

void exibirSolucao(Solution &s)
{
    for (int i = 0; i < s.routes.size(); i++)
    {
        for (int j = 0; j < s.routes[i].size() - 1; j++)
        {
            cout << s.routes[i][j] << " -> ";
        }
        cout << s.routes[i].back() << endl;
    }

    cout << s.valorObj << endl;
}

/*void calcularValorObj(Solution &s, Instance &data)
{
    s.valorObj = 0;
    for (int i = 0; i < s.sequencia.size() - 1; i++)
    {
        s.valorObj += data.getDistance(s.sequencia[i], s.sequencia[i + 1]);
    }
}*/