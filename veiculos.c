
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"

void listarVeiculos(const Veiculo *veiculos, int total)
{
    if (total == 0)
    {
        printf("Nao ha nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\nVeiculo %d\n", i + 1);
        printf("Codigo: %d\n", veiculos[i].codigo);
        printf("Modelo: %s\n", veiculos[i].modelo);
        printf("Ano: %d\n", veiculos[i].ano);
        printf("Preco: R$ %.2f\n", veiculos[i].preco);
    }
}

void consultarVeiculo(const Veiculo *veiculos, int total)
{
    int codigolido;

    printf("Digite o codigo do veiculo que quer consultar: ");
    if (!lerInteiro(&codigolido))
    {
        printf("Codigo invalido.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (veiculos[i].codigo == codigolido)
        {
            printf("Veiculo encontrado.\n");
            printf("Codigo: %d\n", veiculos[i].codigo);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Ano: %d\n", veiculos[i].ano);
            printf("Preco: R$ %.2f\n", veiculos[i].preco);
            return;
        }
    }

    printf("Veiculo nao encontrado.\n");
}

void alterarVeiculo(Veiculo *veiculos, int total)
{
    int codigolido;
    Veiculo novo;

    printf("Digite o codigo do veiculo que quer alterar: ");
    if (!lerInteiro(&codigolido))
    {
        printf("Codigo invalido.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (veiculos[i].codigo == codigolido)
        {
            printf("Veiculo encontrado.\n");

            novo = veiculos[i];

            printf("Digite o novo modelo: ");
            if (!lerTexto(novo.modelo, sizeof(novo.modelo)))
            {
                printf("Modelo invalido.\n");
                return;
            }

            printf("Digite o novo ano: ");
            if (!lerInteiro(&novo.ano) || novo.ano < 1886 || novo.ano > 2027)
            {
                printf("Ano invalido.\n");
                return;
            }

            printf("Digite o novo preco: ");
            if (!lerReal(&novo.preco) || !(novo.preco >= 0))
            {
                printf("Preco invalido.\n");
                return;
            }

            veiculos[i] = novo;

            printf("Veiculo alterado com sucesso!\n");
            return;
        }
    }

    printf("Veiculo nao encontrado.\n");
}

void removerVeiculo(Veiculo **veiculos, int *total, int *capacidade)
{
    int codigolido;

    printf("Digite o codigo do veiculo que quer remover: ");
    if (!lerInteiro(&codigolido))
    {
        printf("Codigo invalido.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if ((*veiculos)[i].codigo == codigolido)
        {
            if (*capacidade - (*total - 1) > INCREMENTO)
            {
                int novaCapacidade = *total - 1 + INCREMENTO;
                Veiculo *temporario = realloc(
                    *veiculos, novaCapacidade * sizeof(Veiculo));

                if (temporario == NULL)
                {
                    printf("Nao foi possivel ajustar a memoria. Remocao cancelada.\n");
                    return;
                }

                *veiculos = temporario;
                *capacidade = novaCapacidade;
            }

            for (int j = i; j < *total - 1; j++)
            {
                (*veiculos)[j] = (*veiculos)[j + 1];
            }

            (*total)--;

            printf("Veiculo removido com sucesso.\n");
            return;
        }
    }

    printf("Veiculo nao encontrado.\n");
}

void cadastrarVeiculo(Veiculo **veiculos, int *total, int *capacidade)
{
    int codigo;

    printf("Digite o codigo do veiculo: ");
    if (!lerInteiro(&codigo))
    {
        printf("Codigo invalido.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if ((*veiculos)[i].codigo == codigo)
        {
            printf("Ja existe um veiculo com esse codigo.\n");
            return;
        }
    }

    Veiculo novo;
    novo.codigo = codigo;

    printf("Digite o modelo: ");
    if (!lerTexto(novo.modelo, sizeof(novo.modelo)))
    {
        printf("Modelo invalido.\n");
        return;
    }

    printf("Digite o ano: ");
    if (!lerInteiro(&novo.ano) || novo.ano < 1886 || novo.ano > 2027)
    {
        printf("Ano invalido.\n");
        return;
    }

    printf("Digite o preco:");
    if (!lerReal(&novo.preco) || !(novo.preco >= 0))
    {
        printf("Preco invalido.\n");
        return;
    }

    if (*total >= *capacidade)
    {
        int novaCapacidade = *capacidade + INCREMENTO;

        Veiculo *temporario = realloc(
            *veiculos, novaCapacidade * sizeof(Veiculo));

        if (temporario == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            return;
        }

        *veiculos = temporario;
        *capacidade = novaCapacidade;
    }

    (*veiculos)[*total] = novo;
    (*total)++;

    printf("Veiculo cadastrado.\n");
}
