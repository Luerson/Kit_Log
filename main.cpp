#include <bits/stdc++.h>
#include "pugixml-1.14/src/pugixml.hpp"
#include "implements.h"

#define ld long double

using namespace std;
using namespace pugi;

void readFile(Graph& myGraph) {
    string s = "tests/a280.xml";
    const char* nomeArquivo = s.c_str();

    xml_document doc;
    xml_parse_result result = doc.load_file(nomeArquivo);

    if (!result) {
        cout << "Erro ao caregar o arquivo XML: " << result.description() << endl;
    }

    xml_node travellingSalesmanProblemInstance = doc.child("travellingSalesmanProblemInstance");
    if (!travellingSalesmanProblemInstance) {
        cerr << "Elemento 'travellingSalesmanProblemInstance' não encontrado no documento XML." << endl;
        return;
    }

    xml_node graph_xml = travellingSalesmanProblemInstance.child("graph");
    if (!graph_xml) {
        cerr << "Elemento 'graph' não encontrado dentro do elemento 'travellingSalesmanProblemInstance'." << endl;
        return;
    }

    int i = 0, j = 0;

    for (xml_node vertex = graph_xml.child("vertex"); vertex; vertex = vertex.next_sibling(), i++) {
        myGraph.adj.push_back(vector<ld>(0));
        j = 0;

        for (xml_node edge = vertex.child("edge"); edge; edge = edge.next_sibling(), j++) {
            if (i == j) {
                myGraph.adj[i].push_back(0);
                j++;
            }
            myGraph.adj[i].push_back(edge.attribute("cost").as_float());
        }

        if (i == j) {
            myGraph.adj[i].push_back(0);
            j++;
        }
    }
}

int main () {
    srand(time(NULL));

    Graph myGraph;
    Solution s;

    readFile(myGraph);

    /*for (int i = 0; i < myGraph.adj.size(); i++) {
        for (int j = 0; j < myGraph.adj[i].size(); j++) {
            cout << myGraph.adj[i][j] << " ";
        }
        cout << endl;
    }*/

    s = construcao(myGraph);
    buscaLocal(s, myGraph);

    //s = ILS(100, 100, myGraph);

    return 0;
}