
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"

int normalizarCPF(char *cpf)
{
    char digitos[12];
    int tamanho = strlen(cpf);
    int j = 0;

    if (tamanho != 11 && tamanho != 14)
        return 0;

    for (int i = 0; i < tamanho; i++)
    {
        if (tamanho == 14 && (i == 3 || i == 7 || i == 11))
        {
            if ((i == 11 && cpf[i] != '-') || (i != 11 && cpf[i] != '.'))
                return 0;
        }
        else
        {
            if (cpf[i] < '0' || cpf[i] > '9')
                return 0;

            digitos[j] = cpf[i];
            j++;
        }
    }

    digitos[j] = '\0';
    strcpy(cpf, digitos);
    return 1;
}

static int mesmoCPF(const char *cpfSalvo, const char *cpfLido)
{
    char copia[15];

    memcpy(copia, cpfSalvo, sizeof(copia));
    copia[14] = '\0';

    return normalizarCPF(copia) && strcmp(copia, cpfLido) == 0;
}

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
    if (!lerTexto(cpfLido, sizeof(cpfLido)) || !normalizarCPF(cpfLido))
    {
        printf("CPF invalido. Use 11 digitos ou o formato 000.000.000-00.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (mesmoCPF(clientes[i].cpf, cpfLido))
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
    if (!lerTexto(cpfLido, sizeof(cpfLido)) || !normalizarCPF(cpfLido))
    {
        printf("CPF invalido. Use 11 digitos ou o formato 000.000.000-00.\n");
        return;
    }

    for (int i = 0; i < total; i++)
    {
        if (mesmoCPF(clientes[i].cpf, cpfLido))
        {
            printf("Cliente encontrado.\n");

            novo = clientes[i];

            printf("Digite o novo nome: ");
            if (!lerTexto(novo.nome, sizeof(novo.nome)))
            {
                printf("Nome invalido.\n");
                return;
            }

            printf("Digite o novo telefone: ");
            if (!lerTexto(novo.telefone, sizeof(novo.telefone)))
            {
                printf("Telefone invalido.\n");
                return;
            }

            printf("Digite o novo email: ");
            if (!lerTexto(novo.email, sizeof(novo.email)))
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
    if (!lerTexto(cpfLido, sizeof(cpfLido)) || !normalizarCPF(cpfLido))
    {
        printf("CPF invalido. Use 11 digitos ou o formato 000.000.000-00.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if (mesmoCPF(clientes[i].cpf, cpfLido))
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
    if (!lerTexto(cpfLido, sizeof(cpfLido)) || !normalizarCPF(cpfLido))
    {
        printf("CPF invalido. Use 11 digitos ou o formato 000.000.000-00.\n");
        return;
    }

    for (int i = 0; i < *total; i++)
    {
        if (mesmoCPF((*clientes)[i].cpf, cpfLido))
        {
            printf("Ja existe um cliente com esse CPF.\n");
            return;
        }
    }

    Cliente novo;
    strcpy(novo.cpf, cpfLido);

    printf("Digite o nome: ");
    if (!lerTexto(novo.nome, sizeof(novo.nome)))
    {
        printf("Nome invalido.\n");
        return;
    }

    printf("Digite o telefone: ");
    if (!lerTexto(novo.telefone, sizeof(novo.telefone)))
    {
        printf("Telefone invalido.\n");
        return;
    }

    printf("Digite o email: ");
    if (!lerTexto(novo.email, sizeof(novo.email)))
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
