#include "construcao.h"

void escolher3NosAleatorios(vector<int>& subtour, int graph_size) {
    for (int i = 0; i < 3; i++) {
        int newVertex = rand() % graph_size;

        if (find(subtour.begin(), subtour.end(), newVertex) == subtour.end()) {
            subtour.push_back(newVertex);
        } else {
            i--;
        }
    }
}

set<int> nosRestantes(vector<int>& subtour, int graph_size) {
    set<int> CL;

    for (int i = 0; i < graph_size; i++) {
        if (find(subtour.begin(), subtour.end(), i) == subtour.end()) {
            CL.insert(i);
        }
    }

    return CL;
}

vector<InsertionInfo> calcularCustoInsercao(vector<int>& subtour, set<int>& naoUsados, Graph& g) {
    vector<InsertionInfo> candidates;

    for (auto vertice : naoUsados) {
        for (int i = 0; i < subtour.size()-1; i++) {
            InsertionInfo candidate;

            candidate.noInserido = vertice;
            candidate.arestaRemovida = make_pair(subtour[i], subtour[i+1]);
            candidate.custo = g.adj[subtour[i]][subtour[i+1]];

            candidates.push_back(candidate);
        }
    }

    return candidates;
}

void inserirNaSolucao(vector<int>& subtour, int no) {
    subtour.pop_back();
    subtour.push_back(no);
    subtour.push_back(0);
}

long double calcCost(vector<int>& subtour, Graph& g) {
    long double cost = 0;

    for (int i = 0; i < subtour.size() - 1; i++) {
        cost += g.adj[subtour[i]][subtour[i+1]];
    }

    return cost;
}

Solution construcao(Graph& g) {
    int graph_size = g.adj.size();

    Solution s;

    s.sequencia.push_back(0);
    escolher3NosAleatorios(s.sequencia, graph_size);
    s.sequencia.push_back(0);

    set<int> CL = nosRestantes(s.sequencia, graph_size);

    while (!CL.empty()) {

        vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s.sequencia, CL, g);

        sort(custoInsercao.begin(), custoInsercao.end());
        double alpha = (double) rand()/RAND_MAX;
        int selecionado = rand() % ((int) ceil(alpha*custoInsercao.size()));

        inserirNaSolucao(s.sequencia, custoInsercao[selecionado].noInserido);
        CL.erase(custoInsercao[selecionado].noInserido);
    }

    s.valorObj = calcCost(s.sequencia, g);

    /*for (int i = 0; i < s.sequencia.size(); i++) {
        cout << s.sequencia[i] << " ";
    }
    cout << endl;*/

    cout << fixed << setprecision(6) << "cost = " << s.valorObj << endl;

    /*for (int i = 0; i < g.adj.size(); i++) {
        for (int j = 0; j < g.adj[i].size(); j++) {
            cout << g.adj[i][j] << " ";
        }
        cout << endl;
    }*/

    return s;
}