#include "Data.h"
#include "implements.h"
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void processarLinha(char *str, double tempoEsp, double custoEsp, ofstream &outputFile)
{
    Solution s;

    auto data = Data(2, str);
    data.read();
    size_t n = data.getDimension();

    double totalTime = 0.0;
    double midTime = 0.0;

    double totalSolution = 0.0;
    double midSolution = 0.0;

    for (int i = 0; i < 10; i++)
    {
        auto start = chrono::steady_clock::now();

        s = ILS(10, min((size_t)100, n), data);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsedTime = end - start;

        totalTime += elapsedTime.count();
        totalSolution += s.valorObj;
    }

    midTime = totalTime / 10.0;
    midSolution = totalSolution / 10.0;

    if (!outputFile.is_open())
    {
        outputFile.open("resultados.tex", ios_base::app);
    }

    string destaqueTempo = (tempoEsp >= midTime) ? "\\textbf{" : "";
    string destaqueCusto = (custoEsp >= midSolution) ? "\\textbf{" : "";

    string nomeInstancia = str;
    nomeInstancia = nomeInstancia.substr(nomeInstancia.find_last_of("/") + 1);

    outputFile << nomeInstancia << " & " << fixed << setprecision(3) << tempoEsp << " & " << destaqueTempo << fixed << setprecision(3) << midTime << " & " << fixed << setprecision(3) << custoEsp << " & " << destaqueCusto << fixed << setprecision(3) << midSolution << " \\\\" << endl;

    outputFile.close();
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    ifstream arquivo("instancias.txt");
    ofstream outputFile;

    if (arquivo.is_open())
    {
        string linha;
        while (getline(arquivo, linha))
        {
            char *linha_char = new char[linha.length() + 1];
            strcpy(linha_char, linha.c_str());

            char *str = strtok(linha_char, " ");
            double valor1 = atof(strtok(nullptr, " "));
            double valor2 = atof(strtok(nullptr, " "));

            processarLinha(str, valor1, valor2, outputFile);

            delete[] linha_char;
        }
    }
    else
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    return 0;
}
