#include <iostream>
#include <vector>
#include <cctype>
#include <sstream>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

vector<string> lex(string text) {
    string tok;
    string str;
    string comment;
    string expr;
    string varName;
    bool isStr = false;
    bool isPrint = false;
    bool isInput = false;
    bool isComment = false;
    bool isFloat = false;
    bool isVar = false;
    bool isAdd = false;

    vector<string> tokens;

    for (int i = 0; i < text.size(); i++) {
        tok += text[i];

        if (tok == " " and !isStr) {
            /*if (expr != "") {
                for (int i = 0; i < expr.size(); i++) {
                    if (expr[i] == '.') {
                        isFloat = true;
                        i = expr.size();
                    }
                }
                if (isFloat) {
                    tokens.push_back("EXPR-F:" + expr);
                }
                else {
                    tokens.push_back("EXPR-I:" + expr);
                }
                expr = "";
            }*/
            if (isVar and varName != "") {
                isVar = false;
                tokens.push_back("VAR:" + varName);
            }
            tok = "";
        }
        else if (tok == "\n" or tok == "{EOF}") {
            if (expr != "") {
                for (int i = 0; i < expr.size(); i++) {
                    if (expr[i] == '.') {
                        isFloat = true;
                        i = expr.size();
                    }
                }
                if (isFloat) {
                    tokens.push_back("EXPR-F:" + expr);
                }
                else {
                    tokens.push_back("EXPR-I:" + expr);
                }
                expr = "";
            }
            if (isVar and varName != "") {
                isVar = false;
                tokens.push_back("VAR:" + varName);
            }
            if (isComment and comment != "") {
                isComment = false;
                tok = "";
            }

            tok = "";
        }
        
        if (!isStr) {
            if (tok == "#" and !isComment) {
                isComment = true;
                comment = "";
                tok = "";
            }
            else if (isComment and tok != "#") {
                comment += tok;
                tok = "";
            }
            else if (tok == "#" and isComment) {
                isComment = false;
                tok = "";
            }
            else if (tok == "$") {
                isVar = true;
                varName = "";
            }
            else if (isVar and tok != " " and tok != "(" and tok != ")" and tok != ",") {
                varName += tok;
                tok = "";
            }
            else if (tok == "=") {
                tokens.push_back("EQUALS");
                tok = "";
            }
            else if (tok == "0" or tok == "1" or tok == "2" or tok == "3" or tok == "4" or tok == "5" or tok == "6" or tok == "7" or tok == "8" or tok == "9" or tok == ".") {
                expr += tok;
                tok = "";
            }
            else if (tok == "+" or tok == "-" or tok == "*" or tok == "/") {
                expr += tok;
                tok = "";
            }
            else if (tok == "," and !isStr) {
                if (expr != "") {
                    for (int i = 0; i < expr.size(); i++) {
                        if (expr[i] == '.') {
                            isFloat = true;
                            i = expr.size();
                        }
                    }
                    if (isFloat) {
                        tokens.push_back("EXPR-F:" + expr);
                    }
                    else {
                        tokens.push_back("EXPR-I:" + expr);
                    }
                    expr = "";
                }
                if (isVar and varName != "") {
                    isVar = false;
                    tokens.push_back("VAR:" + varName);
                }
                tokens.push_back(",");
                tok = "";
            }
        }
        if (tok == "print(") {
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
        else if (tok == "input(") {
            tokens.push_back("INPUT(");
            isInput = true;
            tok = "";
        }
        else if (tok == "add(") {
            tokens.push_back("ADD(");
            isAdd = true;
            tok = "";
        }
        else if (tok == ")" and isInput) {
            if (isVar and varName != "") {
                isVar = false;
                tokens.push_back("VAR:" + varName);
            }

            tokens.push_back(")IN");
            isInput = false;
            tok = "";
        }
        else if (tok == ")" and isAdd) {
            if (expr != "") {
                for (int i = 0; i < expr.size(); i++) {
                    if (expr[i] == '.') {
                        isFloat = true;
                        i = expr.size();
                    }
                }
                if (isFloat) {
                    tokens.push_back("EXPR-F:" + expr);
                }
                else {
                    tokens.push_back("EXPR-I:" + expr);
                }
                expr = "";
            }
            if (isVar and varName != "") {
                isVar = false;
                tokens.push_back("VAR:" + varName);
            }

            //cout << "PRINT END" << endl;
            tokens.push_back(")AD");
            isAdd = false;
            tok = "";
        }
        else if (tok == ")" and isPrint) {
            if (expr != "") {
                for (int i = 0; i < expr.size(); i++) {
                    if (expr[i] == '.') {
                        isFloat = true;
                        i = expr.size();
                    }
                }
                if (isFloat) {
                    tokens.push_back("EXPR-F:" + expr);
                }
                else {
                    tokens.push_back("EXPR-I:" + expr);
                }
                expr = "";
            }
            if (isVar and varName != "") {
                isVar = false;
                tokens.push_back("VAR:" + varName);
            }

            //cout << "PRINT END" << endl;
            tokens.push_back(")PR");
            isPrint = false;
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

    //cout << comment << endl;
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

int evalInt(const string& expression) {
    istringstream iss(expression);
    int result = 0;
    int current_number = 0;
    int last_number = 0;
    char last_operator = '+';
    char current_operator;
    vector<int> operand_stack;

    while (iss >> current_operator) {
        if (current_operator == '(') {
            // Empurra o resultado parcial e o operador para as pilhas de operandos e operadores.
            operand_stack.push_back(result);
            result = 0;
            operand_stack.push_back((last_operator == '-') ? -1 : 1);
            last_operator = '+';
        } else if (current_operator == ')') {
            // Calcula o resultado dentro dos parênteses.
            int inside_result = result;
            while (!operand_stack.empty() && operand_stack.back() != 1 && operand_stack.back() != -1) {
                inside_result *= operand_stack.back();
                operand_stack.pop_back();
            }
            if (!operand_stack.empty() && (operand_stack.back() == 1 || operand_stack.back() == -1)) {
                inside_result *= operand_stack.back();
                operand_stack.pop_back();
            }
            result = operand_stack.back() == -1 ? inside_result : result + inside_result;
            operand_stack.pop_back();
        } else if (current_operator == '+' || current_operator == '-') {
            if (last_operator == '+' || last_operator == '-') {
                // Primeiro, calculamos a operação pendente.
                if (last_operator == '+') {
                    result += current_number;
                } else if (last_operator == '-') {
                    result -= current_number;
                }
            } else {
                result = current_number;  // Inicializa o resultado com o primeiro número
            }
            current_number = 0;
            last_operator = current_operator;
        } else if (current_operator == '*' || current_operator == '/') {
            // Lê o próximo número
            int number;
            iss >> number;

            if (current_operator == '*') {
                // Multiplicação
                current_number = last_number * number;
            } else if (current_operator == '/') {
                // Divisão
                if (number == 0) {
                    throw runtime_error("Divisão por zero.");
                }
                current_number = last_number / number;
            }
        } else {
            // Se não é um operador, assume-se que é um número.
            iss.putback(current_operator); // Coloca o operador de volta na stream
            iss >> current_number;

            // Mantém o último número para operações de multiplicação e divisão
            last_number = current_number;
        }
    }

    // Última operação
    if (last_operator == '+' || last_operator == '-') {
        result += current_number;
    }

    return result;
}

double evalFloat(const string& expression) {
    istringstream iss(expression);
    double result = 0.0;
    double current_number = 0.0;
    double last_number = 0.0;
    char last_operator = '+';
    char current_operator;
    vector<double> operand_stack;

    while (iss >> current_operator) {
        if (current_operator == '(') {
            // Empurra o resultado parcial e o operador para as pilhas de operandos e operadores.
            operand_stack.push_back(result);
            result = 0.0;
            operand_stack.push_back((last_operator == '-') ? -1.0 : 1.0);
            last_operator = '+';
        } else if (current_operator == ')') {
            // Calcula o resultado dentro dos parênteses.
            double inside_result = result;
            while (!operand_stack.empty() && operand_stack.back() != 1.0 && operand_stack.back() != -1.0) {
                inside_result *= operand_stack.back();
                operand_stack.pop_back();
            }
            if (!operand_stack.empty() && (operand_stack.back() == 1.0 || operand_stack.back() == -1.0)) {
                inside_result *= operand_stack.back();
                operand_stack.pop_back();
            }
            result = operand_stack.back() == -1.0 ? inside_result : result + inside_result;
            operand_stack.pop_back();
        } else if (current_operator == '+' || current_operator == '-') {
            if (last_operator == '+' || last_operator == '-') {
                // Primeiro, calculamos a operação pendente.
                if (last_operator == '+') {
                    result += current_number;
                } else if (last_operator == '-') {
                    result -= current_number;
                }
            } else {
                result = current_number;  // Inicializa o resultado com o primeiro número
            }
            current_number = 0.0;
            last_operator = current_operator;
        } else if (current_operator == '*' || current_operator == '/') {
            // Lê o próximo número
            double number;
            iss >> number;

            if (current_operator == '*') {
                // Multiplicação
                current_number = last_number * number;
            } else if (current_operator == '/') {
                // Divisão
                if (number == 0.0) {
                    throw runtime_error("Divisão por zero.");
                }
                current_number = last_number / number;
            }
        } else {
            // Se não é um operador, assume-se que é um número.
            iss.putback(current_operator); // Coloca o operador de volta na stream
            iss >> current_number;

            // Mantém o último número para operações de multiplicação e divisão
            last_number = current_number;
        }
    }

    // Última operação
    if (last_operator == '+' || last_operator == '-') {
        result += current_number;
    }

    return result;
}

bool haveTwoDecimalPlaces(double num) {
    return abs(num - round(num)) < 0.01; // Verifica se a diferença entre o número e seu arredondamento é menor que 0.01.
}

void parse(vector<string> tokens) {
    int i = 0;

    map<string, string> variables;

    while(i < tokens.size()) {
        if (tokens[i] == "PRINT(") {
            i++; // Avance para o primeiro argumento
            string printedString = "";
            if (tokens[i].substr(0, 6) == "STRING") {
                printedString += tokens[i].substr(7);
            } else if (tokens[i].substr(0, 6) == "EXPR-I") {
                printedString += to_string(evalInt(tokens[i].substr(7)));
            } else if (tokens[i].substr(0, 6) == "EXPR-F") {
                if (haveTwoDecimalPlaces(evalFloat(tokens[i].substr(7)))) {
                    ostringstream stream;
                    stream << fixed << setprecision(2) << evalFloat(tokens[i].substr(7));
                    printedString += stream.str();
                }
                else {
                    printedString += to_string(evalFloat(tokens[i].substr(7)));
                }
            } else if (tokens[i].substr(0, 3) == "VAR") {
                printedString += variables[tokens[i].substr(4)];
            }

            while (i < tokens.size() and tokens[i] != ")PR") {
                if (printedString != "" and tokens[i] == ",") {
                    ++i;
                    if (tokens[i].substr(0, 6) == "STRING") {
                        printedString += tokens[i].substr(7);
                    } else if (tokens[i].substr(0, 6) == "EXPR-I") {
                        printedString += to_string(evalInt(tokens[i].substr(7)));
                    } else if (tokens[i].substr(0, 6) == "EXPR-F") {
                        if (haveTwoDecimalPlaces(evalFloat(tokens[i].substr(7)))) {
                            ostringstream stream;
                            stream << fixed << setprecision(2) << evalFloat(tokens[i].substr(7));
                            printedString += stream.str();
                        }
                        else {
                            printedString += to_string(evalFloat(tokens[i].substr(7)));
                        }
                    } else if (tokens[i].substr(0, 3) == "VAR") {
                        if (variables[tokens[i].substr(4)].substr(0,6) == "EXPR-I") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else if (variables[tokens[i].substr(4)].substr(0,6) == "EXPR-F") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else if (variables[tokens[i].substr(4)].substr(0,6) == "STRING") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else {
                            printedString += variables[tokens[i].substr(4)];
                        }
                    }
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
            if (tokens[i].substr(0, 6) == "STRING") {
                printedString += tokens[i].substr(7);
            } else if (tokens[i].substr(0, 6) == "EXPR-I") {
                printedString += to_string(evalInt(tokens[i].substr(7)));
            } else if (tokens[i].substr(0, 6) == "EXPR-F") {
                if (haveTwoDecimalPlaces(evalFloat(tokens[i].substr(7)))) {
                    ostringstream stream;
                    stream << fixed << setprecision(2) << evalFloat(tokens[i].substr(7));
                    printedString += stream.str();
                }
                else {
                    printedString += to_string(evalFloat(tokens[i].substr(7)));
                }
            } else if (tokens[i].substr(0, 3) == "VAR") {
                printedString += variables[tokens[i].substr(4)];
            }

            while (i < tokens.size() and tokens[i] != ")PR") {
                if (printedString != "" and tokens[i] == ",") {
                    ++i;
                    if (tokens[i].substr(0, 6) == "STRING") {
                        printedString += tokens[i].substr(7);
                    } else if (tokens[i].substr(0, 6) == "EXPR-I") {
                        printedString += to_string(evalInt(tokens[i].substr(7)));
                    } else if (tokens[i].substr(0, 6) == "EXPR-F") {
                        if (haveTwoDecimalPlaces(evalFloat(tokens[i].substr(7)))) {
                            ostringstream stream;
                            stream << fixed << setprecision(2) << evalFloat(tokens[i].substr(7));
                            printedString += stream.str();
                        }
                        else {
                            printedString += to_string(evalFloat(tokens[i].substr(7)));
                        }
                    } else if (tokens[i].substr(0, 3) == "VAR") {
                        if (variables[tokens[i].substr(4)].substr(0,6) == "EXPR-I") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else if (variables[tokens[i].substr(4)].substr(0,6) == "EXPR-F") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else if (variables[tokens[i].substr(4)].substr(0,6) == "STRING") {
                            printedString += variables[tokens[i].substr(4)].substr(7);
                        }
                        else {
                            printedString += variables[tokens[i].substr(4)];
                        }
                    }
                }
                else if (tokens[i] != ",") {
                    i++;
                }
            }

            cout << printedString << endl;
        }
        else if (tokens[i] == "INPUT(") {
            i++;

            string text;
            string input;

            if (tokens[i].substr(0, 6) == "STRING") {
                text = tokens[i].substr(7);
                cout << text;
            }
            else if (tokens[i].substr(0, 3) == "VAR") {
                getline(cin, input);

                if ((input.find("0") != string::npos or input.find("1") != string::npos or input.find("2") != string::npos or input.find("3") != string::npos or input.find("4") != string::npos or input.find("5") != string::npos or input.find("6") != string::npos or input.find("7") != string::npos or input.find("8") != string::npos or input.find("9") != string::npos) and !input.find(".") != string::npos) {
                    cout << "True" << endl;
                }
                else {
                    cout << "False" << endl;
                }

                variables[tokens[i].substr(4)] = input;
                //cout << variables[tokens[i].substr(4)] << endl;
            }
            
            while (i < tokens.size() and tokens[i] != ")IN") {
                if (text != "" and tokens[i] == ",") {
                    ++i;
                    if (tokens[i].substr(0, 3) == "VAR") {
                        getline(cin, input);

                        if ((input.find("0") != string::npos or input.find("1") != string::npos or input.find("2") != string::npos or input.find("3") != string::npos or input.find("4") != string::npos or input.find("5") != string::npos or input.find("6") != string::npos or input.find("7") != string::npos or input.find("8") != string::npos or input.find("9") != string::npos) and input.find(".") == string::npos) {
                            variables[tokens[i].substr(4)] = "EXPR-I:" + input;
                        }
                        else if ((input.find("0") != string::npos or input.find("1") != string::npos or input.find("2") != string::npos or input.find("3") != string::npos or input.find("4") != string::npos or input.find("5") != string::npos or input.find("6") != string::npos or input.find("7") != string::npos or input.find("8") != string::npos or input.find("9") != string::npos) and input.find(".") != string::npos) {
                            variables[tokens[i].substr(4)] = "EXPR-F:" + input;
                        }
                        else {
                            variables[tokens[i].substr(4)] = "STRING:" + input;
                        }
                        //cout << variables[tokens[i].substr(4)] << endl;
                    }
                }
                else if (tokens[i] != ",") {
                    i++;
                }
            }
        }
        /*else if (tokens[i].substr(0, 3) + " " + tokens[i+1] == "VAR EQUALS") {
            if (tokens[i+2].substr(0, 6) == "STRING") {
                variables[tokens[i].substr(4)] = tokens[i+2].substr(7);
                //cout << variables[tokens[i].substr(4)] << endl;
                i+=3;
            }
            else if (tokens[i+2].substr(0, 6) == "EXPR-I") {
                variables[tokens[i].substr(4)] = to_string(evalInt(tokens[i+2].substr(7)));
                //cout << variables[tokens[i].substr(4)] << endl;
                i+=3;
            }
            else if (tokens[i+2].substr(0, 6) == "EXPR-F") {
                variables[tokens[i].substr(4)] = to_string(evalFloat(tokens[i+2].substr(7)));
                //cout << variables[tokens[i].substr(4)] << endl;
                i+=3;
            }
            else if (tokens[i+2].substr(0,3) == "VAR") {
                if (tokens[i+3].substr(0, 8) == "EXPR-I:+" ) {
                    int res = evalInt(variables[tokens[i+2].substr(4)]) + evalInt(tokens[i+3].substr(8));

                    variables[tokens[i].substr(4)] = to_string(res);
                    //cout << res << endl;
                }
                else if (tokens[i+3].substr(0, 8) == "EXPR-F:+" ) {
                    double res = evalFloat(variables[tokens[i+2].substr(4)]) + evalFloat(tokens[i+3].substr(8));

                    variables[tokens[i].substr(4)] = to_string(res);
                    //cout << res << endl;
                }
                else if (tokens[i+3].substr(0,8) + " " + tokens[i+4].substr(0,3) == "EXPR-I:+ VAR") {
                    //double res = evalFloat(variables[tokens[i+2].substr(4)]) + evalFloat(tokens[i+3].substr(8));

                    //variables[tokens[i].substr(4)] = to_string(res);
                    //cout << res << endl;
                    cout << "True" << endl;
                }
                else {
                    variables[tokens[i].substr(4)] = variables[tokens[i+2].substr(4)];
                }
                //cout << tokens[i+3].substr(0, 8) + " " + tokens[i+4].substr(0, 3) << endl;
                i+=3;
            }
            //cout << (variables[tokens[i].substr(4)].find("EXPR-I") ? "True" : "False") << endl;
        }*/
        else if (tokens[i].substr(0,3) + " " + tokens[i+1] == "VAR EQUALS") {
            i += 2;
            //cout << tokens[i-2] << endl;

            if (tokens[i].substr(0,6) == "STRING") {
                variables[tokens[i-2].substr(4)] = "STRING:" + tokens[i].substr(7);
                //cout << variables[tokens[i-2].substr(4)] << endl;
            }
            else if (tokens[i].substr(0,6) == "EXPR-I") {
                variables[tokens[i-2].substr(4)] = "EXPR-I:" + to_string(evalInt(tokens[i].substr(7)));
                //cout << variables[tokens[i-2].substr(4)] << endl;
            }
            else if (tokens[i].substr(0,6) == "EXPR-F") {
                variables[tokens[i-2].substr(4)] = "EXPR-F:" + to_string(evalFloat(tokens[i].substr(7)));
                //cout << variables[tokens[i-2].substr(4)] << endl;
            }
            else if (tokens[i].substr(0,3) == "VAR") {
                variables[tokens[i-2].substr(4)] = variables[tokens[i].substr(4)];
                //cout << variables[tokens[i-2].substr(4)] << endl;
            }

            i++;
        }
        else if (tokens[i] == "ADD(") {
            i++;
            string varName = "";
            string content = "";

            if (tokens[i].substr(0,3) == "VAR") {
                varName = tokens[i].substr(4);
                //cout << varName << endl;
            }

            while (i < tokens.size() and tokens[i] != ")AD") {
                if (varName != "" and tokens[i] == ",") {
                    ++i;
                    if (tokens[i].substr(0,6) == "STRING") {
                        content += tokens[i].substr(7);
                    }
                    else if (tokens[i].substr(0,3) == "VAR") {
                        //content += variables[tokens[i].substr(4)];
                        if (variables[tokens[i].substr(4)].substr(0,6) == "STRING") {
                            content += variables[tokens[i].substr(4)].substr(7);
                        }
                        else if (variables[tokens[i].substr(4)].substr(0,6) == "EXPR-I" or variables[tokens[i].substr(4)].substr(0,6) == "EXPR-F") {
                            if (variables[varName].substr(0,6) == "STRING") {
                                content += variables[tokens[i].substr(4)].substr(7);
                            }
                            else {
                                content += "+" + variables[tokens[i].substr(4)].substr(7);
                            }
                        }
                    }
                    if (variables[varName].substr(0,6) == "STRING") {
                        if (tokens[i].substr(0,6) == "EXPR-I") {
                            content += to_string(evalInt(tokens[i].substr(7)));
                            //cout << content << endl;
                        } else if (tokens[i].substr(0,6) == "EXPR-F") {
                            content += to_string(evalFloat(tokens[i].substr(7)));
                            //cout << content << endl;
                        }
                    }
                    else {
                        if (tokens[i].substr(0,6) == "EXPR-I") {
                            content += "+" + to_string(evalInt(tokens[i].substr(7)));
                            //cout << content << endl;
                        } else if (tokens[i].substr(0,6) == "EXPR-F") {
                            content += "+" + to_string(evalFloat(tokens[i].substr(7)));
                            //cout << content << endl;
                        }
                    }
                }
                else if (tokens[i] != ",") {
                    i++;
                }
            }

            //variables[varName] += content;

            if (variables[varName].substr(0,6) == "STRING") {
                string res = variables[varName].substr(7) + content;
                variables[varName] = res;
            }
            else if (variables[varName].substr(0,6) == "EXPR-I") {
                string res = variables[varName].substr(7) + content;
                variables[varName] = to_string(evalInt(res));
                //cout << res << endl;
            }
            else if (variables[varName].substr(0,6) == "EXPR-F") {
                string res = variables[varName].substr(7) + content;
                variables[varName] = to_string(evalFloat(res));
                //cout << res << endl;
            }

            //cout << variables[varName] << endl;
        }
        else {
            i++;
        }
    }
}