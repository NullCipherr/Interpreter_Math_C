#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>

#define MAX_EXPR 100
#define MAX_PILHA 100
#define MAX_HISTORICO 10
#define MAX_VARIAVEIS 10

double pilha_num[MAX_PILHA] ;
char pilha_op[MAX_PILHA] ;
int topo_num = -1 ;
int topo_op = -1 ;

// Estrutura para armazenar histórico
typedef struct {
    char expressao[MAX_EXPR];
    double resultado;
} Historico;

Historico historico[MAX_HISTORICO];
int hist_count = 0;

// Estrutura para armazenar variáveis
typedef struct {
    char nome[10];
    double valor;
} Variavel;

Variavel variaveis[MAX_VARIAVEIS];
int var_count = 0;

// Função para obter o valor de uma variável
double obter_valor_variavel(const char* nome) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variaveis[i].nome, nome) == 0) {
            return variaveis[i].valor;
        }
    }
    printf("Erro: Variável '%s' não definida!\n", nome);
    return 0;
}

// Função para definir uma variável
void definir_variavel(const char* nome, double valor) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variaveis[i].nome, nome) == 0) {
            variaveis[i].valor = valor;
            return;
        }
    }
    if (var_count < MAX_VARIAVEIS) {
        strcpy(variaveis[var_count].nome, nome);
        variaveis[var_count].valor = valor;
        var_count++;
    } else {
        printf("Erro: Limite de variáveis atingido!\n");
    }
}

// Função para calcular funções matemáticas
double calcular_funcao(const char* func, double valor) {
    if (strcmp(func, "sin") == 0) return sin(valor);
    if (strcmp(func, "cos") == 0) return cos(valor);
    if (strcmp(func, "tan") == 0) return tan(valor);
    if (strcmp(func, "log") == 0) return log(valor);
    if (strcmp(func, "sqrt") == 0) return sqrt(valor);
    printf("Erro: Função '%s' não reconhecida!\n", func);
    return 0;
}

// Funções para manipulação de pilha

// Empilha um numero na pilha númerica.
void empilha_num(double num)
{
    pilha_num[++topo_num] = num ;
}

// Empilha uma operação na pilha de operações.
void empilha_op(char op)
{
    pilha_op[++topo_op] = op ;
}

// Função que desempilha um numero da pilha numérica.
double desempilha_num()
{
    return pilha_num[topo_num--] ;
}

// Função que desempilha a operação da pilha de operações.
char desempilha_op()
{
    return pilha_op[topo_op--] ;
}

// Função que verifica a precedencia dos operadores.
int verifica_precedencia(char op)
{
    switch(op)
    {
        case '+' : case '-' : return 1 ;
        case '*' : case '/' : return 2 ;
        case '^' : return 3 ;
        case '%' : return 2 ;
        default: return 0 ;
    }
}

// Função para calcular fatorial
double fatorial(int n) {
    if (n == 0) return 1;
    double resultado = 1;
    for (int i = 1; i <= n; i++) {
        resultado *= i;
    }
    return resultado;
}

// Modificar a função calcular para incluir novos operadores
double calcular(double a, double b, char op) {
    switch(op) {
        case '+' : return a + b;
        case '-' : return a - b;
        case '*' : return a * b;
        case '/' : return a / b;
        case '^' : return pow(a, b);
        case '%' : return fmod(a, b);
        case '&' : return (int)a & (int)b; // AND lógico
        case '|' : return (int)a | (int)b; // OR lógico
        default: return 0;
    }
}

// Função para verificar se a expressão contém apenas caracteres válidaos
bool expressao_valida(const char* expr) {
    const char* caracteres_validos = "0123456789+-*/^%() .sincostanlogqrtpiexyzabc=";
    
    for(int i = 0; expr[i] != '\0'; i++) {
        if(expr[i] == ' ') continue;  // Ignora espaços
        if(strchr(caracteres_validos, expr[i]) == NULL) {
            printf("Erro: Caractere inválido '%c' na expressão!\n", expr[i]);
            return false;
        }
    }
    return true;
}

double avaliar_expressao(char* expr) {
    // Verificar se é uma atribuição de variável
    char var_nome[10];
    char* igual = strchr(expr, '=');
    if (igual != NULL) {
        int pos = igual - expr;
        strncpy(var_nome, expr, pos);
        var_nome[pos] = '\0';
        // Remove espaços em branco
        char* p = var_nome;
        while (*p == ' ') p++;
        char* end = p + strlen(p) - 1;
        while (end > p && *end == ' ') end--;
        *(end + 1) = '\0';
        
        // Avalia o lado direito da expressão
        double valor = avaliar_expressao(igual + 1);
        definir_variavel(var_nome, valor);
        return valor;
    }

    // Se for uma expressão que contém apenas uma variável
    if (isalpha(expr[0]) && !strchr(expr, '+') && !strchr(expr, '-') && 
        !strchr(expr, '*') && !strchr(expr, '/') && !strchr(expr, '^')) {
        char* espaco = strchr(expr, ' ');
        if (espaco) *espaco = '\0';
        double valor = obter_valor_variavel(expr);
        if (valor == 0 && strcmp(expr, "0") != 0) {
            printf("Erro: Variável '%s' não definida!\n", expr);
        }
        return valor;
    }

    // Se for uma expressão com operadores, processa cada token
    int i;
    double num = 0;
    char token[MAX_EXPR];
    int token_pos = 0;
    
    for(i = 0; expr[i] != '\0'; i++) {
        if(isspace(expr[i])) continue;

        if(isalpha(expr[i])) {
            // Coleta o nome da variável
            token_pos = 0;
            while(isalpha(expr[i])) {
                token[token_pos++] = expr[i++];
            }
            token[token_pos] = '\0';
            i--;
            
            double valor = obter_valor_variavel(token);
            empilha_num(valor);
        }
        else if(isdigit(expr[i]) || expr[i] == '.') {
            // Processa números como antes
            num = 0;
            double decimal = 0.1;
            bool ponto_decimal = false;
            
            while(isdigit(expr[i]) || expr[i] == '.') {
                if(expr[i] == '.') {
                    ponto_decimal = true;
                } else if(!ponto_decimal) {
                    num = num * 10 + (expr[i] - '0');
                } else {
                    num = num + (expr[i] - '0') * decimal;
                    decimal *= 0.1;
                }
                i++;
            }
            i--;
            empilha_num(num);
        }
        else if(strchr("+-*/^%()", expr[i])) {
            // Processa operadores como antes
            if(expr[i] == '(') {
                empilha_op(expr[i]);
            }
            else if(expr[i] == ')') {
                while(topo_op >= 0 && pilha_op[topo_op] != '(') {
                    double b = desempilha_num();
                    double a = desempilha_num();
                    empilha_num(calcular(a, b, desempilha_op()));
                }
                if(topo_op >= 0) desempilha_op();
            }
            else {
                while(topo_op >= 0 && pilha_op[topo_op] != '(' && 
                      verifica_precedencia(pilha_op[topo_op]) >= verifica_precedencia(expr[i])) {
                    double b = desempilha_num();
                    double a = desempilha_num();
                    empilha_num(calcular(a, b, desempilha_op()));
                }
                empilha_op(expr[i]);
            }
        }
        else if(expr[i] == '!') {
            double a = desempilha_num();
            empilha_num(fatorial((int)a));
        }
        else if(expr[i] == '&' && expr[i+1] == '&') {
            i++; // Avança o índice para o próximo caractere
            double b = desempilha_num();
            double a = desempilha_num();
            empilha_num(calcular(a, b, '&'));
        }
        else if(expr[i] == '|' && expr[i+1] == '|') {
            i++; // Avança o índice para o próximo caractere
            double b = desempilha_num();
            double a = desempilha_num();
            empilha_num(calcular(a, b, '|'));
        }
    }

    // Processa operadores restantes
    while(topo_op >= 0) {
        double b = desempilha_num();
        double a = desempilha_num();
        empilha_num(calcular(a, b, desempilha_op()));
    }

    return pilha_num[topo_num];
}

// Função para limpar a tela
void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para mostrar o histórico
void mostrar_historico() {
    if (hist_count == 0) {
        printf("Histórico vazio!\n");
        return;
    }
    printf("\nHistórico de cálculos:\n");
    for (int i = hist_count - 1; i >= 0; i--) {
        printf("%d: %s = %.4f\n", hist_count - i, 
               historico[i].expressao, historico[i].resultado);
    }
}

// Função para exportar histórico
void exportar_historico() {
    FILE *arquivo = fopen("historico_calculos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo de histórico!\n");
        return;
    }
    
    fprintf(arquivo, "Histórico de Cálculos\n");
    fprintf(arquivo, "===================\n\n");
    for (int i = 0; i < hist_count; i++) {
        fprintf(arquivo, "%s = %.4f\n", 
                historico[i].expressao, historico[i].resultado);
    }
    fclose(arquivo);
    printf("Histórico exportado para 'historico_calculos.txt'\n");
}

void mostrar_menu_inicial() {
    printf("\033[1;36m"); // Cor ciano brilhante
    printf("  ╔════════════════════════════════════════╗\n");
    printf("  ║          Interpreter Math C            ║\n");
    printf("  ╚════════════════════════════════════════╝\n");
    printf("\033[0m"); // Reset cor

    printf("\033[1;33m"); // Cor amarela brilhante
    printf("\n┌─────────── Comandos Disponíveis ───────────┐\n");
    printf("│ %-42s   │\n", "'q' ou 'sair' → Sair do programa");
    printf("│ %-42s   │\n", "'ajuda'       → Ver operadores");
    printf("│ %-42s   │\n", "'limpar'      → Limpar a tela");
    printf("│ %-43s   │\n", "'historico'   → Ver cálculos anteriores");
    printf("│ %-43s   │\n", "'exportar'    → Salvar histórico");
    printf("└────────────────────────────────────────────┘\n");
    printf("\033[0m"); // Reset cor

    printf("\033[1;32m"); // Cor verde brilhante
    printf("\n┌──────────── Exemplos de Uso ───────────────┐\n");
    printf("│ %-43s │\n", "Expressões: 2 + 3 * 4");
    printf("│ %-43s │\n", "Parênteses: (2 + 3) * 4");
    printf("│ %-42s │\n", "Decimais:   2.5 * 3.7");
    printf("│ %-43s │\n", "Potência:   2 ^ 3");
    printf("│ %-43s │\n", "Módulo:     10 % 3");
    printf("│ %-44s │\n", "Funções:    sin(pi/2)");
    printf("└────────────────────────────────────────────┘\n");
    printf("\033[0m"); // Reset cor
}

void mostrar_ajuda() {
    printf("\033[1;35m"); // Cor magenta brilhante
    printf("\n┌─────────── Operadores ───────────────────┐\n");
    printf("│ %-8s → %-27s │\n", "+", "Adição");
    printf("│ %-8s → %-27s │\n", "-", "Subtração");
    printf("│ %-8s → %-27s │\n", "*", "Multiplicação");
    printf("│ %-8s → %-27s │\n", "/", "Divisão");
    printf("│ %-8s → %-27s │\n", "^", "Exponenciação");
    printf("│ %-8s → %-27s │\n", "%", "Módulo");
    printf("│ %-8s → %-27s │\n", "!", "Fatorial");
    printf("│ %-8s → %-27s │\n", "&&", "AND Lógico");
    printf("│ %-8s → %-27s │\n", "||", "OR Lógico");
    printf("└──────────────────────────────────────────┘\n");

    printf("\n┌─────────── Funções ─────────────────────┐\n");
    printf("│ %-8s → %-27s │\n", "sin(x)", "Seno");
    printf("│ %-8s → %-27s │\n", "cos(x)", "Cosseno");
    printf("│ %-8s → %-27s │\n", "tan(x)", "Tangente");
    printf("│ %-8s → %-27s │\n", "log(x)", "Logaritmo Natural");
    printf("│ %-8s → %-27s │\n", "sqrt(x)", "Raiz Quadrada");
    printf("└──────────────────────────────────────────┘\n");

    printf("\n┌─────────── Constantes ──────────────────┐\n");
    printf("│ %-8s → %-27s │\n", "pi", "3.141592...");
    printf("│ %-8s → %-27s │\n", "e", "2.718281...");
    printf("└──────────────────────────────────────────┘\n");
    printf("\033[0m"); // Reset cor
}

int main() {
    limpar_tela();
    mostrar_menu_inicial();

    while(1) {
        char expressao[MAX_EXPR];
        printf(">>> ");
        fgets(expressao, MAX_EXPR, stdin);
        expressao[strcspn(expressao, "\n")] = 0;

        // Verifica comandos especiais primeiro
        if(strcmp(expressao, "q") == 0 || strcmp(expressao, "sair") == 0) {
            printf("\nObrigado por utilizar o Interpreter Math C... <3 <3 !\n");
            break;
        }

        if(strcmp(expressao, "limpar") == 0) {
            limpar_tela();
            mostrar_menu_inicial();
            continue;
        }

        if(strcmp(expressao, "historico") == 0) {
            mostrar_historico();
            continue;
        }

        if(strcmp(expressao, "exportar") == 0) {
            exportar_historico();
            continue;
        }

        if(strcmp(expressao, "ajuda") == 0) {
            mostrar_ajuda();
            continue;
        }

        // Se não for comando especial, avalia como expressão matemática
        double resultado = avaliar_expressao(expressao);
        
        // Adiciona ao histórico apenas se for uma expressão válida e calculada com sucesso
        if (resultado != 0 || strcmp(expressao, "0") == 0) {
            if (hist_count == MAX_HISTORICO) {
                for (int i = 0; i < MAX_HISTORICO - 1; i++) {
                    strcpy(historico[i].expressao, historico[i+1].expressao);
                    historico[i].resultado = historico[i+1].resultado;
                }
                hist_count--;
            }
            strcpy(historico[hist_count].expressao, expressao);
            historico[hist_count].resultado = resultado;
            hist_count++;
            printf("= %.4f\n", resultado);
        }
    }
    
    return 0;
}