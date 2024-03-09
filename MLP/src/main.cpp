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

        s = ILS(10, min(100, (int)n), data);

        auto end = chrono::steady_clock::now();
        chrono::duration<double> elapsedTime = end - start;

        totalTime += elapsedTime.count();
        totalSolution += s.latTotal;
    }

    midTime = totalTime / 10.0;
    midSolution = totalSolution / 10.0;

    if (!outputFile.is_open())
    {
        outputFile.open("resultados.tex", ios_base::app);
    }

    string nomeInstancia = str;
    nomeInstancia = nomeInstancia.substr(nomeInstancia.find_last_of("/") + 1);
    nomeInstancia.substr(0, nomeInstancia.size() - 4);

    double per_temp = ((tempoEsp - midTime) / tempoEsp) * 100;
    double per_custo = ((custoEsp - midSolution) / custoEsp) * 100;

    outputFile << nomeInstancia << " & ";
    outputFile << fixed << setprecision(1) << per_temp << " & ";
    outputFile << fixed << setprecision(3) << per_custo << " & ";
    outputFile << fixed << setprecision(3) << tempoEsp << " & ";
    outputFile << fixed << setprecision(1) << custoEsp << " & ";
    outputFile << fixed << setprecision(3) << midTime << " & ";
    outputFile << fixed << setprecision(1) << midSolution << " \\\\" << endl;

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
