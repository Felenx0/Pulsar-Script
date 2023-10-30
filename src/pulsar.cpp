#include <iostream>
#include <fstream>
#include <string>
#include "interpreter.cpp"

using namespace std;

string text;

int open_file(string fileName) {
    // Crie um objeto ifstream para ler o arquivo
    ifstream file(fileName);

    // Verifique se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        std::cerr << "Unable to open code";
        return 1; // Saia com um código de erro
    }

    // Variável para armazenar cada linha do arquivo
    std::string line;

    // Use um loop para ler e imprimir cada linha do arquivo
    while (getline(file, line)) {
        //cout << line << endl;
        text += line;
    }

    text += "<EOF>";

    // Feche o arquivo após a leitura
    file.close();

    return 0;
}

int main(int argc, char const *argv[])
{
    bool running = true;

    if (argc > 1) {
        open_file(argv[1]);
        vector<string> lexer = lex(text);
        parse(lexer);
    } else {
        while (running)
        {
            cout << "pulsar > ";
            getline(cin, text);
            vector<string> lexer = lex(text);
            parse(lexer);
        }
    }
    return 0;
}