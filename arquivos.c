#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>
#include "estruturas.h"
#include "funcoes.h"

#define ARQ_VEICULOS "veiculos.bin"
#define ARQ_CLIENTES "clientes.bin"


static int lerQuantidade(FILE *arquivo, size_t tamanhoRegistro, int *quantidade)
{
    long tamanhoArquivo;

    if (fread(quantidade, sizeof(int), 1, arquivo) != 1 ||
        *quantidade < 0 || *quantidade > INT_MAX - INCREMENTO)
        return 0;

    if (fseek(arquivo, 0, SEEK_END) != 0)
        return 0;

    tamanhoArquivo = ftell(arquivo);
    if (tamanhoArquivo < (long)sizeof(int))
        return 0;

    tamanhoArquivo -= sizeof(int);
    if ((unsigned long)tamanhoArquivo / tamanhoRegistro != (size_t)*quantidade ||
        (unsigned long)tamanhoArquivo % tamanhoRegistro != 0)
        return 0;

    if ((size_t)(*quantidade + INCREMENTO) > SIZE_MAX / tamanhoRegistro)
        return 0;

    return fseek(arquivo, sizeof(int), SEEK_SET) == 0;
}

static int carregarVeiculos(Veiculo **dados, int *total, int *capacidade)
{
    FILE *arquivo = fopen(ARQ_VEICULOS, "rb");
    int quantidade;
    int leituraOk;
    Veiculo *temporario;

    if (arquivo == NULL)
    {
        if (errno == ENOENT)
            return 1; 

        printf("Erro ao abrir veiculos.bin para leitura.\n");
        return 0;
    }

    if (!lerQuantidade(arquivo, sizeof(Veiculo), &quantidade))
    {
        printf("Arquivo veiculos.bin invalido ou incompleto.\n");
        fclose(arquivo);
        return 0;
    }

    temporario = malloc((size_t)(quantidade + INCREMENTO) * sizeof(Veiculo));
    if (temporario == NULL)
    {
        printf("Erro ao alocar memoria para veiculos.\n");
        fclose(arquivo);
        return 0;
    }

    leituraOk = fread(temporario, sizeof(Veiculo), quantidade, arquivo) == (size_t)quantidade;
    if (fclose(arquivo) != 0)
        leituraOk = 0;

    if (!leituraOk)
    {
        printf("Erro ao ler veiculos.bin.\n");
        free(temporario);
        return 0;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (memchr(temporario[i].modelo, '\0', sizeof(temporario[i].modelo)) == NULL ||
            temporario[i].modelo[0] == '\0' ||
            temporario[i].ano < 1886 || temporario[i].ano > 2027 ||
            !isfinite(temporario[i].preco) || temporario[i].preco < 0)
        {
            printf("Registro invalido em veiculos.bin.\n");
            free(temporario);
            return 0;
        }

        for (int j = 0; j < i; j++)
        {
            if (temporario[i].codigo == temporario[j].codigo)
            {
                printf("Registro duplicado em veiculos.bin.\n");
                free(temporario);
                return 0;
            }
        }
    }

    free(*dados);
    *dados = temporario;
    *total = quantidade;
    *capacidade = quantidade + INCREMENTO;
    printf("%d veiculos carregado(s).\n", quantidade);
    return 1;
}

static int carregarClientes(Cliente **dados, int *total, int *capacidade)
{
    FILE *arquivo = fopen(ARQ_CLIENTES, "rb");
    int quantidade;
    int leituraOk;
    Cliente *temporario;

    if (arquivo == NULL)
    {
        if (errno == ENOENT)
            return 1; 

        printf("Erro ao abrir clientes.bin para leitura.\n");
        return 0;
    }

    if (!lerQuantidade(arquivo, sizeof(Cliente), &quantidade))
    {
        printf("Arquivo clientes.bin invalido ou incompleto.\n");
        fclose(arquivo);
        return 0;
    }

    temporario = malloc((size_t)(quantidade + INCREMENTO) * sizeof(Cliente));
    if (temporario == NULL)
    {
        printf("Erro ao alocar memoria para clientes.\n");
        fclose(arquivo);
        return 0;
    }

    leituraOk = fread(temporario, sizeof(Cliente), quantidade, arquivo) == (size_t)quantidade;
    if (fclose(arquivo) != 0)
        leituraOk = 0;

    if (!leituraOk)
    {
        printf("Erro ao ler clientes.bin.\n");
        free(temporario);
        return 0;
    }

    for (int i = 0; i < quantidade; i++)
    {
        if (memchr(temporario[i].cpf, '\0', sizeof(temporario[i].cpf)) == NULL ||
            memchr(temporario[i].nome, '\0', sizeof(temporario[i].nome)) == NULL ||
            memchr(temporario[i].telefone, '\0', sizeof(temporario[i].telefone)) == NULL ||
            memchr(temporario[i].email, '\0', sizeof(temporario[i].email)) == NULL ||
            temporario[i].nome[0] == '\0' || temporario[i].telefone[0] == '\0' ||
            temporario[i].email[0] == '\0' || !normalizarCPF(temporario[i].cpf))
        {
            printf("Registro invalido em clientes.bin.\n");
            free(temporario);
            return 0;
        }

        for (int j = 0; j < i; j++)
        {
            if (strcmp(temporario[i].cpf, temporario[j].cpf) == 0)
            {
                printf("Registro duplicado em clientes.bin.\n");
                free(temporario);
                return 0;
            }
        }
    }

    free(*dados);
    *dados = temporario;
    *total = quantidade;
    *capacidade = quantidade + INCREMENTO;
    printf("%d clientes carregado(s).\n", quantidade);
    return 1;
}

int carregarDados(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
)
{
    (void)vendas;
    (void)totalVendas;
    (void)capacidadeVendas;

    if (!carregarVeiculos(veiculos, totalVeiculos, capacidadeVeiculos))
        return 0;

    return carregarClientes(clientes, totalClientes, capacidadeClientes);
}

static int substituirArquivo(const char *nome, const char *novo, const char *backup)
{
    FILE *arquivo;
    int tinhaOriginal = 0;

    arquivo = fopen(backup, "rb");
    if (arquivo != NULL)
    {
        fclose(arquivo);
        printf("Existe um backup pendente: %s. Confira-o antes de salvar.\n", backup);
        return 0;
    }
    if (errno != ENOENT)
        return 0;

    if (rename(nome, backup) == 0)
        tinhaOriginal = 1;
    else if (errno != ENOENT)
        return 0;

    if (rename(novo, nome) != 0)
    {
        if (tinhaOriginal && rename(backup, nome) != 0)
            printf("O original foi preservado em %s.\n", backup);
        return 0;
    }

    if (tinhaOriginal && remove(backup) != 0)
        printf("Dados salvos, mas nao foi possivel apagar %s.\n", backup);

    return 1;
}

static int salvarVeiculos(const Veiculo *dados, int total)
{
    FILE *arquivo = fopen("veiculos.tmp", "wb");
    int gravacaoOk;

    if (arquivo == NULL)
        return 0;

    gravacaoOk = fwrite(&total, sizeof(int), 1, arquivo) == 1;
    if (gravacaoOk)
        gravacaoOk = fwrite(dados, sizeof(Veiculo), total, arquivo) == (size_t)total;

    if (fclose(arquivo) != 0)
        gravacaoOk = 0;

    if (!gravacaoOk)
    {
        remove("veiculos.tmp");
        return 0;
    }

    if (!substituirArquivo("veiculos.bin", "veiculos.tmp", "veiculos.bak"))
    {
        printf("A nova copia esta em veiculos.tmp.\n");
        return 0;
    }

    printf("%d veiculos salvo(s).\n", total);
    return 1;
}

static int salvarClientes(const Cliente *dados, int total)
{
    FILE *arquivo = fopen("clientes.tmp", "wb");
    int gravacaoOk;

    if (arquivo == NULL)
        return 0;

    gravacaoOk = fwrite(&total, sizeof(int), 1, arquivo) == 1;
    if (gravacaoOk)
        gravacaoOk = fwrite(dados, sizeof(Cliente), total, arquivo) == (size_t)total;

    if (fclose(arquivo) != 0)
        gravacaoOk = 0;

    if (!gravacaoOk)
    {
        remove("clientes.tmp");
        return 0;
    }

    if (!substituirArquivo("clientes.bin", "clientes.tmp", "clientes.bak"))
    {
        printf("A nova copia esta em clientes.tmp.\n");
        return 0;
    }

    printf("%d clientes salvo(s).\n", total);
    return 1;
}

int salvarDados(
    const Veiculo *veiculos, int totalVeiculos,
    const Cliente *clientes, int totalClientes,
    const Venda *vendas, int totalVendas
)
{
    int veiculosOk;
    int clientesOk;

    (void)vendas;
    (void)totalVendas;

    veiculosOk = salvarVeiculos(veiculos, totalVeiculos);
    clientesOk = salvarClientes(clientes, totalClientes);

    if (!veiculosOk)
        printf("Erro ao salvar os veiculos.\n");
    if (!clientesOk)
        printf("Erro ao salvar os clientes.\n");

    return veiculosOk && clientesOk;
}
