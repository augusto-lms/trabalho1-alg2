#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "menus.h"

/* Le uma linha inteira e descarta o excesso se ela nao couber. */
int lerTexto(char *texto, int tamanho)
{
    int caractere;
    int i = 0;
    int excesso = 0;
    int temTexto = 0;

    while ((caractere = getchar()) != '\n' && caractere != EOF)
    {
        if (i < tamanho - 1)
        {
            texto[i] = (char)caractere;
            i++;
        }
        else
        {
            excesso = 1;
        }

        if (!isspace((unsigned char)caractere))
            temTexto = 1;
    }

    texto[i] = '\0';
    return !excesso && temTexto;
}

int lerInteiro(int *numero)
{
    char texto[64];
    char *fim;
    long valor;

    if (!lerTexto(texto, sizeof(texto)))
        return 0;

    errno = 0;
    valor = strtol(texto, &fim, 10);

    if (fim == texto || errno == ERANGE || valor < INT_MIN || valor > INT_MAX)
        return 0;

    /* Permite espacos depois do numero, mas rejeita letras e outros simbolos. */
    while (isspace((unsigned char)*fim))
        fim++;

    if (*fim != '\0')
        return 0;

    *numero = (int)valor;
    return 1;
}

int lerReal(float *numero)
{
    char texto[64];
    char *fim;
    float valor;

    if (!lerTexto(texto, sizeof(texto)))
        return 0;

    errno = 0;
    valor = strtof(texto, &fim);

    if (fim == texto || errno == ERANGE || !isfinite(valor))
        return 0;

    while (isspace((unsigned char)*fim))
        fim++;

    if (*fim != '\0')
        return 0;

    *numero = valor;
    return 1;
}

static int lerOpcao(void)
{
    int opcao;

    if (!lerInteiro(&opcao))
    {
        if (feof(stdin))
            return 0;

        return -1;
    }

    if (opcao < 0 || opcao > 7)
        return -1;

    return opcao;
}

static void menuVeiculos(Veiculo **veiculos, int *total, int *capacidade) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("       GERENCIAR VEICULOS\n");
        printf("====================================\n");
        printf("1 - Cadastrar Veiculo\n");
        printf("2 - Consultar Veiculo\n");
        printf("3 - Alterar Veiculo\n");
        printf("4 - Remover Veiculo\n");
        printf("5 - Listar Veiculos\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                cadastrarVeiculo(veiculos, total, capacidade);
                break;
            case 2:
                consultarVeiculo(*veiculos, *total);
                break;
            case 3:
                alterarVeiculo(*veiculos, *total);
                break;
            case 4:
                removerVeiculo(*veiculos, total);
                break;
            case 5:
                listarVeiculos(*veiculos, *total);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

static void menuClientes(Cliente **clientes, int *total, int *capacidade) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("       GERENCIAR CLIENTES\n");
        printf("====================================\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Consultar Cliente\n");
        printf("3 - Alterar Cliente\n");
        printf("4 - Remover Cliente\n");
        printf("5 - Listar Clientes\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes, total, capacidade);
                break;
            case 2:
                consultarCliente(*clientes, *total);
                break;
            case 3:
                alterarCliente(*clientes, *total);
                break;
            case 4:
                removerCliente(*clientes, total);
                break;
            case 5:
                listarClientes(*clientes, *total);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

static void menuVendas(void) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("        GERENCIAR VENDAS\n");
        printf("====================================\n");
        printf("1 - Cadastrar Venda\n");
        printf("2 - Consultar Venda\n");
        printf("3 - Alterar Venda\n");
        printf("4 - Remover Venda\n");
        printf("5 - Listar Vendas\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        if (opcao >= 1 && opcao <= 5) {
            printf("Funcionalidade ainda nao integrada.\n");
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

static void menuConsultasVendas(void) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("     CONSULTAR VENDAS POR CRITERIO\n");
        printf("====================================\n");
        printf("1 - Pesquisar por CPF do Cliente\n");
        printf("2 - Pesquisar por Codigo do Veiculo\n");
        printf("3 - Pesquisar por Data da Venda\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        if (opcao >= 1 && opcao <= 3) {
            printf("Consulta ainda nao integrada.\n");
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

static void menuRelatoriosVendas(void) {
    int opcao;

    do {
        printf("\n====================================\n");
        printf("        RELATORIOS DE VENDAS\n");
        printf("====================================\n");
        printf("1 - Relatorio por CPF do Cliente\n");
        printf("2 - Relatorio por Codigo do Veiculo\n");
        printf("3 - Relatorio por Data da Venda\n");
        printf("0 - Voltar\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        if (opcao >= 1 && opcao <= 3) {
            printf("Relatorio ainda nao integrado.\n");
        } else if (opcao != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void menuPrincipal(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
) {
    int opcao;

    (void)vendas;
    (void)totalVendas;
    (void)capacidadeVendas;

    do {
        printf("\n====================================\n");
        printf("   SISTEMA DE CONCESSIONARIA\n");
        printf("====================================\n");
        printf("1 - Gerenciar Veiculos\n");
        printf("2 - Gerenciar Clientes\n");
        printf("3 - Gerenciar Vendas\n");
        printf("4 - Listar todos os Veiculos\n");
        printf("5 - Listar todos os Clientes\n");
        printf("6 - Consultar Vendas por Criterio\n");
        printf("7 - Gerar Relatorio de Vendas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        opcao = lerOpcao();

        switch (opcao) {
            case 1:
                menuVeiculos(veiculos, totalVeiculos, capacidadeVeiculos);
                break;
            case 2:
                menuClientes(clientes, totalClientes, capacidadeClientes);
                break;
            case 3:
                menuVendas();
                break;
            case 4:
                listarVeiculos(*veiculos, *totalVeiculos);
                break;
            case 5:
                listarClientes(*clientes, *totalClientes);
                break;
            case 6:
                menuConsultasVendas();
                break;
            case 7:
                menuRelatoriosVendas();
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
