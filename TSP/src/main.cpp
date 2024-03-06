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
        auto start = std::chrono::steady_clock::now();

        s = ILS(50, (n >= 150 ? n / 2 : n), data);

        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsedTime = end - start;

        totalTime += elapsedTime.count();
        totalSolution += s.valorObj;
    }

    midTime = totalTime / 10.0;
    midSolution = totalSolution / 10.0;

    // Abre o arquivo de saída em modo de escrita, adicionando ao final
    if (!outputFile.is_open())
    {
        outputFile.open("resultados.tex", std::ios_base::app);
    }

    // Determinar qual variável (tempo ou solução) tem o menor valor
    string destaqueTempo = (tempoEsp >= midTime) ? "\\textbf{" : "";
    string destaqueCusto = (custoEsp >= midSolution) ? "\\textbf{" : "";

    // Remover o prefixo '../instances/' do nome da instância
    string nomeInstancia = str;
    nomeInstancia = nomeInstancia.substr(nomeInstancia.find_last_of("/") + 1);

    // Escrever os dados no arquivo de saída com três casas decimais
    outputFile << nomeInstancia << " & " << fixed << setprecision(3) << tempoEsp << " & " << destaqueTempo << fixed << setprecision(3) << midTime << " & " << fixed << setprecision(3) << custoEsp << " & " << destaqueCusto << fixed << setprecision(3) << midSolution << " \\\\" << endl;

    // Fecha o arquivo de saída
    outputFile.close();
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    ifstream arquivo("instancias.txt"); // Abre o arquivo "instancias.txt" para leitura
    ofstream outputFile;

    if (arquivo.is_open())
    { // Verifica se o arquivo foi aberto corretamente
        std::string linha;
        while (getline(arquivo, linha))
        {
            // Converter a string para ponteiro de char
            char *linha_char = new char[linha.length() + 1];
            std::strcpy(linha_char, linha.c_str());

            // Usar strtok para dividir a linha pelo primeiro espaço
            char *str = std::strtok(linha_char, " ");
            double valor1 = std::atof(std::strtok(nullptr, " "));
            double valor2 = std::atof(std::strtok(nullptr, " "));

            // Chame a função processarLinha com os valores lidos
            processarLinha(str, valor1, valor2, outputFile);

            // Liberar memória alocada para linha_char
            delete[] linha_char;
        }
    }
    else
    {
        cerr << "Erro ao abrir o arquivo!" << std::endl; // Exibe uma mensagem de erro se o arquivo não puder ser aberto
    }

    return 0;
}
