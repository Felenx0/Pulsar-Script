#include <iostream>
#include <vector>

using namespace std;

vector<string> lex(string text) {
    string tok;
    string str;
    bool isStr = false;
    bool isPrint = false;

    vector<string> tokens;

    for (int i = 0; i < text.size(); i++) {
        tok += text[i];

        if (tok == " " and !isStr) {
            tok = "";
        }
        else if (tok == "\n" or tok == "<EOF>") {
            tok = "";
        }
        else if (tok == "print(") {
            //cout << "PRINT START" << endl;
            tokens.push_back("PRINT(");
            isPrint = true;
            tok = "";
        }
        else if (tok == "lprint(") {
            //cout << "PRINT START" << endl;
            tokens.push_back("LPRINT(");
            isPrint = true;
            tok = "";
        }
        else if (tok == ")" and isPrint) {
            //cout << "PRINT END" << endl;
            tokens.push_back(")PR");
            isPrint = false;
            tok = "";
        }
        else if (tok == ",") {
            tokens.push_back(",");
            tok = "";
        }
        else if (tok == "\"" and !isStr) {
            //cout << "STRING START" << endl;
            str = "";
            isStr = true;
            tok = "";
        }
        else if (isStr and tok != "\"") {
            str += tok;
            tok = "";
        }
        else if (tok == "\"" and isStr) {
            //cout << "STRING END" << endl;
            tokens.push_back("STRING:" + str);
            isStr = false;
            tok = "";
        }

        if (tok == "exit()") {
            exit(0);
        }
    }

    //cout << str << endl;
    /*cout << "[";
    for (int i = 0; i < tokens.size(); i++) {
        if (i < tokens.size()) {
            cout << "[" << tokens[i] << "],";
        }
        else if (i >= tokens.size()){
            cout << "[" << tokens[i] << "]";
        }
    }
    cout << "]" << endl;*/

    return tokens;
}

void parse(vector<string> tokens) {
    int i = 0;

    while(i < tokens.size()) {
        if (tokens[i] == "PRINT(") {
            i++; // Avance para o primeiro argumento
            string printedString = "";
            printedString += tokens[i].substr(7);

            while (i < tokens.size() and tokens[i] != ")PR") {
                if (printedString != "" and tokens[i] == ",") {
                    ++i;
                    printedString += tokens[i].substr(7);
                }
                else if (tokens[i] != ",") {
                    i++;
                }
            }
            
            cout << printedString;
        }
        else if (tokens[i] == "LPRINT(") {
            i++; // Avance para o primeiro argumento
            string printedString = "";
            printedString += tokens[i].substr(7);

            while (i < tokens.size() and tokens[i] != ")PR") {
                if (printedString != "" and tokens[i] == ",") {
                    ++i;
                    printedString += tokens[i].substr(7);
                }
                else if (tokens[i] != ",") {
                    i++;
                }
            }

            cout << printedString << endl;
        }
        else {
            i++;
        }
    }
}