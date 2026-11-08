#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"

#define ARQ_VEICULOS "veiculos.bin"
#define ARQ_CLIENTES "clientes.bin"

/*
 * Formato de cada arquivo binario:
 *   1) um int com a quantidade de registros
 *   2) os registros, um seguido do outro
 */

void carregarDados(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
)
{
    FILE *arquivo;
    int quantidade;
    int novaCapacidade;

    /* Vendas ainda nao foram implementadas */
    (void)vendas;
    (void)totalVendas;
    (void)capacidadeVendas;

    /* ===================== VEICULOS ===================== */
    arquivo = fopen(ARQ_VEICULOS, "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo de veiculos nao encontrado. Iniciando sem veiculos.\n");
    }
    else
    {
        if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 || quantidade < 0)
        {
            printf("Arquivo de veiculos invalido. Iniciando sem veiculos.\n");
        }
        else
        {
            novaCapacidade = quantidade + INCREMENTO;

            Veiculo *temporario = realloc(
                *veiculos, novaCapacidade * sizeof(Veiculo));

            if (temporario == NULL)
            {
                printf("Erro ao alocar memoria para os veiculos.\n");
            }
            else
            {
                *veiculos = temporario;
                *capacidadeVeiculos = novaCapacidade;
                *totalVeiculos = (int)fread(*veiculos, sizeof(Veiculo), quantidade, arquivo);

                if (*totalVeiculos < quantidade)
                {
                    printf("Aviso: arquivo de veiculos incompleto.\n");
                }

                printf("%d veiculo(s) carregado(s).\n", *totalVeiculos);
            }
        }

        fclose(arquivo);
    }

    /* ===================== CLIENTES ===================== */
    arquivo = fopen(ARQ_CLIENTES, "rb");

    if (arquivo == NULL)
    {
        printf("Arquivo de clientes nao encontrado. Iniciando sem clientes.\n");
    }
    else
    {
        if (fread(&quantidade, sizeof(int), 1, arquivo) != 1 || quantidade < 0)
        {
            printf("Arquivo de clientes invalido. Iniciando sem clientes.\n");
        }
        else
        {
            novaCapacidade = quantidade + INCREMENTO;

            Cliente *temporario = realloc(
                *clientes, novaCapacidade * sizeof(Cliente));

            if (temporario == NULL)
            {
                printf("Erro ao alocar memoria para os clientes.\n");
            }
            else
            {
                *clientes = temporario;
                *capacidadeClientes = novaCapacidade;
                *totalClientes = (int)fread(*clientes, sizeof(Cliente), quantidade, arquivo);

                if (*totalClientes < quantidade)
                {
                    printf("Aviso: arquivo de clientes incompleto.\n");
                }

                printf("%d cliente(s) carregado(s).\n", *totalClientes);
            }
        }

        fclose(arquivo);
    }
}

void salvarDados(
    const Veiculo *veiculos, int totalVeiculos,
    const Cliente *clientes, int totalClientes,
    const Venda *vendas, int totalVendas
)
{
    FILE *arquivo;

    /* Vendas ainda nao foram implementadas */
    (void)vendas;
    (void)totalVendas;

    /* ===================== VEICULOS ===================== */
    arquivo = fopen(ARQ_VEICULOS, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de veiculos para salvar.\n");
    }
    else
    {
        if (fwrite(&totalVeiculos, sizeof(int), 1, arquivo) != 1 ||
            (int)fwrite(veiculos, sizeof(Veiculo), totalVeiculos, arquivo) != totalVeiculos)
        {
            printf("Erro ao salvar os veiculos.\n");
        }
        else
        {
            printf("%d veiculo(s) salvo(s).\n", totalVeiculos);
        }

        fclose(arquivo);
    }

    /* ===================== CLIENTES ===================== */
    arquivo = fopen(ARQ_CLIENTES, "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de clientes para salvar.\n");
    }
    else
    {
        if (fwrite(&totalClientes, sizeof(int), 1, arquivo) != 1 ||
            (int)fwrite(clientes, sizeof(Cliente), totalClientes, arquivo) != totalClientes)
        {
            printf("Erro ao salvar os clientes.\n");
        }
        else
        {
            printf("%d cliente(s) salvo(s).\n", totalClientes);
        }

        fclose(arquivo);
    }
}
