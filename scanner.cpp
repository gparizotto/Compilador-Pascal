// Gabriel Zanforlin Parizotto - 211025194
// Desenvolvido em linux (Ubuntu 22.04 LTS)
// Compilador gcc 11.3.0

#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

vector<string> palavras_reservadas, atomos;

void init()
{
    palavras_reservadas.push_back("program");
    palavras_reservadas.push_back("integer");
    palavras_reservadas.push_back("label");
    palavras_reservadas.push_back("var");
    palavras_reservadas.push_back("procedure");
    palavras_reservadas.push_back("function");
    palavras_reservadas.push_back("begin");
    palavras_reservadas.push_back("end");
    palavras_reservadas.push_back("if");
    palavras_reservadas.push_back("then");
    palavras_reservadas.push_back("else");
    palavras_reservadas.push_back("while");
    palavras_reservadas.push_back("do");
    palavras_reservadas.push_back("or");
    palavras_reservadas.push_back("and");
    palavras_reservadas.push_back("div");
    palavras_reservadas.push_back("not");
    palavras_reservadas.push_back("read");
    palavras_reservadas.push_back("write");
}

string simbolos_especiais = ".;,():=<>+-*";

string simbolo;

int linha = 1, tab;

int qde_identificadores = 0;

bool pertence_simbolos_especiais(char c)
{
    for (int i = 0; i < simbolos_especiais.length(); i++)
        if (c == simbolos_especiais[i])
            return true;

    return false;
}

bool pertence_letras(char c)
{
    if ((65 <= c && c <= 90) || (97 <= c && c <= 122))
        return true;
    return false;
}

bool pertence_digitos(char c)
{
    if (48 <= c && c <= 57)
        return true;

    return false;
}

bool pertence_letras_e_digitos(char c)
{
    if (pertence_letras(c) || pertence_digitos(c))
        return true;

    return false;
}

bool pertence_palavras_reservadas(string s)
{
    for (int i = 0; i < palavras_reservadas.size(); i++)
        if (s == palavras_reservadas[i])
            return true;

    return false;
}

int PROXIMO(char *proximo, FILE *arquivo)
{
    *proximo = getc(arquivo);

    if (*proximo == EOF)
        return 0;

    if (*proximo == '\n')
        linha++;

    return 1;
}

string CODIGO(string s)
{
    if (s == "program")
        return "c_program";
    else if (s == "var")
        return "c_var";
    else if (s == "procedure")
        return "c_procedure";
    else if (s == "integer")
        return "c_integer";
    else if (s == "begin")
        return "c_begin";
    else if (s == "end")
        return "c_end";
    else if (s == ":")
        return "c_dois_pontos";
    else if (s == ",")
        return "c_virgula";
    else if (s == ";")
        return "c_ponto_e_virgula";
    else if (s == ":=")
        return "c_atribuicao";
    else if (s == "if")
        return "c_if";
    else if (s == "else")
        return "c_else";
    else if (s == "div")
        return "c_div";
    else if (s == "*")
        return "c_multiplicacao";
    else if (s == "then")
        return "c_then";
    else if (s == "+")
        return "c_adicao";
    else if (s == "-")
        return "c_subtracao";
    else if (s == "read")
        return "c_read";
    else if (s == "(")
        return "c_abre_parenteses";
    else if (s == ")")
        return "c_fecha_parenteses";
    else if (s == "while")
        return "c_while";
    else if (s == "do")
        return "c_do";
    else if (s == "write")
        return "c_write";
    else if (s == ">")
        return "c_maior";
    else if (s == "<")
        return "c_menor";
    else if (s == "/")
        return "c_divisao";
    else if (s == "=")
        return "c_igual";
    else if (s == ".")
        return "c_ponto";

    return "";
}

int ERRO(int tipo)
{
    if (tipo == 1)
        printf("erro na linha %d: identificador ou numero mal formados\n", linha);
    else if (tipo == 2)
        printf("erro na linha %d: simbolo especial desconhecido\n", linha);
    return 1;
}

int main()
{
    FILE *arquivo;
    char proximo = '\n';
    string atomo, s;

    init();

    arquivo = fopen("programa.pas", "r"); // abrir o arquivo para leitura

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    while (proximo == '\n')
        PROXIMO(&proximo, arquivo);

    while (proximo != EOF)
    {
        atomo.erase();
        s.erase();
        simbolo.erase();
        if (pertence_simbolos_especiais(proximo))
        {
            s = proximo;
            PROXIMO(&proximo, arquivo);
            if (s == ":" && proximo == '=')
            {
                s = ":=";
                PROXIMO(&proximo, arquivo);
            }
            simbolo = CODIGO(s);
        }
        else if (pertence_letras(proximo))
        {
            do
            {
                atomo += proximo;
                PROXIMO(&proximo, arquivo);
            } while (pertence_letras_e_digitos(proximo));
            if (pertence_palavras_reservadas(atomo))
                simbolo = CODIGO(atomo);
            else
            {
                qde_identificadores++;                      

                simbolo = "c_identificador" + to_string(qde_identificadores) + " ";
            }
        }
        else if (pertence_digitos(proximo))
        {
            do
            {
                atomo += proximo;
                PROXIMO(&proximo, arquivo);
            } while (pertence_digitos(proximo));
            if (pertence_letras(proximo))
                return ERRO(1);

            simbolo = "c_numero ";
        }
        else if (!(0 <= proximo && proximo <= 32))
            return ERRO(2);

        if (simbolo.length()) {
            cout << simbolo;
            atomos.push_back(simbolo);
        }
        else
        {
            cout << proximo;
            PROXIMO(&proximo, arquivo);
        }
    }

    fclose(arquivo);
    return 0;
}
