
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"

void listarClientes(const Cliente *clientes, int total)
{
    if (total == 0)
    {
        printf("Nao ha nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        printf("\nCliente %d\n", i + 1);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Nome: %s\n", clientes[i].nome);
        printf("Telefone: %s\n", clientes[i].telefone);
        printf("Email: %s\n", clientes[i].email);
    }
}

void consultarCliente(const Cliente *clientes, int total)
{
    char cpfLido[15];

    printf("Digite o CPF do cliente que quer consultar: ");
    if (scanf(" %14s", cpfLido) != 1)
    {
        printf("CPF invalido.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (strcmp(clientes[i].cpf, cpfLido) == 0)
        {
            printf("Cliente encontrado.\n");
            printf("CPF: %s\n", clientes[i].cpf);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("Email: %s\n", clientes[i].email);
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
}

void alterarCliente(Cliente *clientes, int total)
{
    char cpfLido[15];
    Cliente novo;

    printf("Digite o CPF do cliente que quer alterar: ");
    if (scanf(" %14s", cpfLido) != 1)
    {
        printf("CPF invalido.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (strcmp(clientes[i].cpf, cpfLido) == 0)
        {
            printf("Cliente encontrado.\n");

            novo = clientes[i];

            printf("Digite o novo nome: ");
            if (scanf(" %99[^\n]", novo.nome) != 1)
            {
                printf("Nome invalido.\n");
                return;
            }

            printf("Digite o novo telefone: ");
            if (scanf(" %19s", novo.telefone) != 1)
            {
                printf("Telefone invalido.\n");
                return;
            }

            printf("Digite o novo email: ");
            if (scanf(" %99s", novo.email) != 1)
            {
                printf("Email invalido.\n");
                return;
            }

            clientes[i] = novo;

            printf("Cliente alterado com sucesso!\n");
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
}

void removerCliente(Cliente *clientes, int *total)
{
    char cpfLido[15];

    printf("Digite o CPF do cliente que quer remover: ");
    if (scanf(" %14s", cpfLido) != 1)
    {
        printf("CPF invalido.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if (strcmp(clientes[i].cpf, cpfLido) == 0)
        {
            for (int j = i; j < *total - 1; j++)
            {
                clientes[j] = clientes[j + 1];
            }

            (*total)--;

            printf("Cliente removido com sucesso.\n");
            return;
        }
    }

    printf("Cliente nao encontrado.\n");
}

void cadastrarCliente(Cliente **clientes, int *total, int *capacidade)
{
    char cpfLido[15];

    printf("Digite o CPF do cliente: ");
    if (scanf(" %14s", cpfLido) != 1)
    {
        printf("CPF invalido.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if (strcmp((*clientes)[i].cpf, cpfLido) == 0)
        {
            printf("Ja existe um cliente com esse CPF.\n");
            return;
        }
    }

    Cliente novo;
    strcpy(novo.cpf, cpfLido);

    printf("Digite o nome: ");
    if (scanf(" %99[^\n]", novo.nome) != 1)
    {
        printf("Nome invalido.\n");
        return;
    }

    printf("Digite o telefone: ");
    if (scanf(" %19s", novo.telefone) != 1)
    {
        printf("Telefone invalido.\n");
        return;
    }

    printf("Digite o email: ");
    if (scanf(" %99s", novo.email) != 1)
    {
        printf("Email invalido.\n");
        return;
    }

    if (*total >= *capacidade)
    {
        int novaCapacidade = *capacidade + INCREMENTO;

        Cliente *temporario = realloc(
            *clientes, novaCapacidade * sizeof(Cliente));

        if (temporario == NULL)
        {
            printf("Erro ao alocar memoria.\n");
            return;
        }

        *clientes = temporario;
        *capacidade = novaCapacidade;
    }

    (*clientes)[*total] = novo;
    (*total)++;

    printf("Cliente cadastrado com sucesso.\n");
}
