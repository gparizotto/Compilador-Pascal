// Gabriel Zanforlin Parizotto - 211025194
// Desenvolvido em linux (Ubuntu 22.04 LTS)
// Compilador gcc 11.3.0

#include <bits/stdc++.h>
#include <ctype.h>

using namespace std;

bool programa(int *index);
bool bloco(int *index);
bool parte_de_declaracoes_de_variaveis(int *index);
bool declaracao_de_variaveis(int *index);
bool lista_identificadores(int *index);
bool identificador(int *index);
bool parte_de_declaracoes_de_sub_rotinas(int *index);
bool declaracao_de_procedimento(int *index);
bool declaracao_de_funcao(int *index);
bool parametros_formais(int *index);
bool secao_de_parametros_formais(int *index);  //----------------------
bool comando_composto(int *index);
bool comando(int *index);
bool comando_sem_rotulo(int *index);
bool atribuicao(int *index);
bool chamada_de_procedimento(int *index);
bool comando_condicional(int *index);
bool comando_repetitivo(int *index);
bool lista_de_expressoes(int *index);
bool expressao(int *index);
bool relacao(int *index);
bool expressao_simples(int *index);
bool termo(int *index);
bool fator(int *index);
bool variavel(int *index);
bool chamada_de_funcao(int *index);
bool numero(int *index);
bool digito(char c);
bool letra(char c);

vector<string> palavras_reservadas;
vector<pair<string, int>> atomos;

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

string programa_gerado;

int linha = 1, tab;

int qde_identificadores = 0;

bool pertence_simbolos_especiais(char c)
{
    for (int i = 0; i < simbolos_especiais.length(); i++)
        if (c == simbolos_especiais[i]) return true;

    return false;
}

bool letra(char c)
{
    if ((65 <= c && c <= 90) || (97 <= c && c <= 122)) return true;
    return false;
}

bool digito(char c)
{
    if (48 <= c && c <= 57) return true;

    return false;
}

bool pertence_letras_e_digitos(char c)
{
    if (letra(c) || digito(c)) return true;

    return false;
}

bool pertence_palavras_reservadas(string s)
{
    for (int i = 0; i < palavras_reservadas.size(); i++)
        if (s == palavras_reservadas[i]) return true;

    return false;
}

int PROXIMO(char *proximo, FILE *arquivo)
{
    *proximo = getc(arquivo);

    if (*proximo == EOF) return 0;

    if (*proximo == '\n') linha++;

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
    else if (s == "<=")
        return "c_menor_ou_igual";
    else if (s == ">=")
        return "c_maior_ou_igual";

    return "";
}

int ERRO(int tipo)
{
    if (tipo == 1)
        printf("erro na linha %d: identificador ou numero mal formados\n",
               linha);
    else if (tipo == 2)
        printf("erro na linha %d: simbolo especial desconhecido\n", linha);
    return 1;
}

int scanner(FILE *arquivo)
{
    char proximo = '\n';
    string atomo, s;

    while (proximo == '\n') PROXIMO(&proximo, arquivo);

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
            if (s == "<" && proximo == '=')
            {
                s = "<=";
                PROXIMO(&proximo, arquivo);
            }
            if (s == ">" && proximo == '=')
            {
                s = ">=";
                PROXIMO(&proximo, arquivo);
            }
            atomos.push_back({s, linha});
            simbolo = CODIGO(s);
        }
        else if (letra(proximo))
        {
            do
            {
                atomo += proximo;
                PROXIMO(&proximo, arquivo);
            } while (pertence_letras_e_digitos(proximo));
            if (pertence_palavras_reservadas(atomo))
            {
                simbolo = CODIGO(atomo);
                atomos.push_back({atomo, linha});
            }
            else
            {
                qde_identificadores++;

                simbolo =
                    "c_identificador" + to_string(qde_identificadores) + " ";
                atomos.push_back({atomo, linha});
            }
        }
        else if (digito(proximo))
        {
            do
            {
                atomo += proximo;
                PROXIMO(&proximo, arquivo);
            } while (digito(proximo));
            if (letra(proximo)) return ERRO(1);

            simbolo = "c_numero ";
            atomos.push_back({atomo, linha});
        }
        else if (!(0 <= proximo && proximo <= 32))
            return ERRO(2);

        if (simbolo.length())
        {
            programa_gerado += simbolo;
            // cout << simbolo;
            //  atomos.push_back(simbolo);
        }
        else
        {
            programa_gerado += proximo;
            // cout << proximo;
            PROXIMO(&proximo, arquivo);
        }
    }

    return 0;
}

bool parte_de_declaracoes_de_rotulos(int *index)
{
    if (atomos[*index].first != "label") return true;
    ++(*index);

    for (char c : atomos[*index].first)
        if (!digito(c)) return false;
    ++(*index);

    return true;
}

bool identificador(int *index)
{
    if (!letra(atomos[*index].first[0])) return false;

    int ind = 1, sz = atomos[*index].first.size();

    while (ind < sz && (letra(atomos[*index].first[ind]) ||
                        digito(atomos[*index].first[ind])))
        ind++;

    return true;
}

bool lista_identificadores(int *index)
{
    if (!identificador(index)) return false;
    ++(*index);

    while (atomos[*index].first == ",")
    {
        ++(*index);
        if (!identificador(index)) return false;
        ++(*index);
    }

    return true;
}

bool tipo(string s)
{
    return s == "integer" || s == "real" || s == "boolean" || s == "string";
}

bool declaracao_de_variaveis(int *index)
{
    if (!lista_identificadores(index)) return false;

    if (atomos[*index].first != ":") return false;
    ++(*index);

    if (!tipo(atomos[*index].first)) return false;
    ++(*index);

    return true;
}

bool parte_de_declaracoes_de_variaveis(int *index)
{
    if (atomos[*index].first != "var") return true;
    ++(*index);

    if (!declaracao_de_variaveis(index)) return false;

    while (atomos[*index].first == ";" && !pertence_palavras_reservadas(atomos[*index + 1].first))
    {
        ++(*index);
        if (declaracao_de_variaveis(index)) return false;
        (++index);
    }

    if (atomos[*index].first != ";") return false;
    ++(*index);

    return true;
}

bool secao_de_parametros_formais(int *index)
{
    if (atomos[*index].first == "var") ++(*index);

    if (!lista_identificadores(index)) return false;

    if (atomos[*index].first != ":") return false;
    ++(*index);

    if (!identificador(index)) return false;
    ++(*index);

    return true;
}

bool parametros_formais(int *index)
{
    if (!secao_de_parametros_formais(index)) return false;

    while (atomos[*index].first == ";")
    {
        ++(*index);
        if (!secao_de_parametros_formais(index)) return false;
        ++(*index);
    }

    return true;
}

bool declaracao_de_procedimento(int *index)
{
    if (atomos[*index].first != "procedure") return false;
    ++(*index);

    if (!identificador(index)) return false;
    ++(*index);

    parametros_formais(index);

    if (atomos[*index].first != ";") return false;
    ++(*index);

    if (!bloco(index)) return false;

    return true;
}

bool declaracao_de_funcao(int *index)
{
    if (atomos[*index].first != "function") return false;
    ++(*index);

    if (!identificador(index)) return false;
    ++(*index);

    parametros_formais(index);

    if (atomos[*index].first != ":") return false;
    ++(*index);

    if (!identificador(index)) return false;
    ++(*index);

    if (atomos[*index].first != ";") return false;
    ++(*index);

    if (!bloco(index)) return false;

    return true;
}

bool parte_de_declaracoes_de_sub_rotinas(int *index)
{
    while (declaracao_de_procedimento(index) || declaracao_de_funcao(index))
    {
        if (atomos[*index].first != ";") return false;
        ++(*index);
    }

    return true;
}

bool numero(int *index)
{
    for (int i = 0; i < atomos[*index].first.size(); i++)
        if (!digito(atomos[*index].first[i])) return false;

    return true;
}

bool variavel(int *index) { return identificador(index); }

bool lista_de_expressoes(int *index)
{
    if (!expressao(index)) return false;

    while (atomos[*index].first == ",")
    {
        ++(*index);
        if (!expressao(index)) return false;
        ++(*index);
    }

    return true;
}

bool chamada_de_funcao(int *index)
{
    if (!identificador(index)) return false;
    ++(*index);

    lista_de_expressoes(index);

    return true;
}

bool fator(int *index)
{
    if (variavel(index) /*|| numero(index) || chamada_de_funcao(index) || expressao(index) || !fator(index)*/)
    {
        ++(*index);
        return true;
    }
    if (numero(index))
    {
        ++(*index);
        return true;
    }
    if (chamada_de_funcao(index))
    {
        ++(*index);
        return true;
    }
    if (expressao(index))
    {
        ++(*index);
        return true;
    }
    if (!fator(index))
    {
        ++(*index);
        return true;
    }
    return false;
}

bool termo(int *index)
{
    bool parenteses = false;
    if (atomos[*index].first == "(")
    {
        ++(*index);
        parenteses = true;
    }

    if (!fator(index)) return false;

    while (atomos[*index].first == "*" || atomos[*index].first == "div" ||
           atomos[*index].first == "and")
    {
        ++(*index);
        if (!fator(index)) return false;
    }

    if (parenteses && atomos[*index].first != ")")
        return false;
    else if (parenteses && atomos[*index].first == ")")
        ++(*index);

    return true;
}

bool expressao_simples(int *index)
{
    if (atomos[*index].first == "+" || atomos[*index].first == "-") ++(*index);

    if (!termo(index)) return false;

    while (atomos[*index].first == "+" || atomos[*index].first == "-" ||
           atomos[*index].first == "or" || atomos[*index].first == "*")
    {
        ++(*index);
        if (!termo(index)) return false;
    }

    return true;
}

bool relacao(int *index)
{
    string s = atomos[*index].first;
    return s == "=" || s == "<>" || s == "<" || s == ">" || s == "<=" ||
           s == ">=";
}

bool expressao(int *index)
{
    if (!expressao_simples(index)) return false;

    if (relacao(index))
    {
        ++(*index);
        if (!expressao_simples(index)) return false;
    }

    return true;
}

bool atribuicao(int *index)
{
    int i = *index;
    if (!variavel(&i)) return false;
    ++(i);

    if (atomos[i].first != ":=") return false;
    ++(i);

    if (!expressao(&i)) return false;

    *index = i;

    return true;
}

bool chamada_de_procedimento(int *index)
{
    int i = *index;
    if (!identificador(&i)) return false;
    ++(i);

    if (atomos[i].first != ";")
        lista_de_expressoes(&i);  // Modificação adicional

    *index = i;

    return true;
}

bool comando_condicional(int *index)
{
    int i = *index;
    if (atomos[i].first != "if") return false;
    ++(i);

    if (!expressao(&i)) return false;

    if (atomos[i].first != "then") return false;
    ++(i);

    if (!comando_sem_rotulo(&i)) return false;

    if (atomos[i].first == "else")
    {
        ++(i);
        if (!comando_sem_rotulo(&i)) return false;
    }

    *index = i;

    return true;
}

bool comando_repetitivo(int *index)
{
    int i = *index;

    if (atomos[i].first != "while") return false;
    ++(i);

    if (!expressao(&i)) return false;

    if (atomos[i].first != "do") return false;
    ++(i);

    if (!comando_sem_rotulo(&i)) return false;

    *index = i;

    return true;
}

bool comando_sem_rotulo(int *index)
{
    if (comando_condicional(index) || comando_repetitivo(index) ||
        atribuicao(index) || comando_composto(index) ||
        chamada_de_procedimento(index))
        return true;

    return false;
}

bool comando(int *index)
{
    if (numero(index))
    {
        ++(*index);
        if (atomos[*index].first != ":") return false;
    }

    if (!comando_sem_rotulo(index)) return false;

    return true;
}

bool comando_composto(int *index)
{
    int i = *index;

    if (atomos[i].first != "begin") return false;
    ++(i);

    if (!comando(&i)) return false;

    while (atomos[i].first == ";")
    {
        ++(i);
        if (atomos[i].first == "end")
            break;  // Modificação para verificar se é necessário sair do loop
        if (!comando(&i)) return false;
    }
    if (atomos[i].first != "end") return false;
    ++(i);

    *index = i;

    return true;
}

bool bloco(int *index)
{
    if (!parte_de_declaracoes_de_rotulos(index)) return false;
    if (!parte_de_declaracoes_de_variaveis(index)) return false;
    if (!parte_de_declaracoes_de_sub_rotinas(index)) return false;

    if (!comando_composto(index)) return false;

    return true;
}

bool programa(int *index)
{
    if (atomos[*index].first != "program") return false;
    ++(*index);

    if (!identificador(index)) return false;
    ++(*index);

    if (atomos[*index].first != ";") return false;
    ++(*index);

    if (!bloco(index)) return false;

    if (atomos[*index].first != ".") return false;
    ++(*index);

    return true;
}

int parser()
{
    int index = 0;

    if (!programa(&index)) return index;

    return -1;
}

int main()
{
    FILE *arquivo;

    init();

    arquivo = fopen("programa.pas", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!");
        return 1;
    }

    if (scanner(arquivo) == 0) cout << "Analise lexica realizada com sucesso\n";

    int index = parser();

    if (index == -1)
        cout << "Analise sintatica realizada com sucesso\n";
    else
    {
        cout << "Erro na analise sintatica\n\nErro na linha: "
             << atomos[index].second << '\n'
             << "No atomo: " << atomos[index].first << '\n';

        return 1;
    }

    cout << "\n\n" << programa_gerado << '\n';

    fclose(arquivo);
    return 0;
}
