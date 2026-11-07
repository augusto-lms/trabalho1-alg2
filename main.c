
#include <stdio.h>
#include <stdlib.h>
#include "menus.h"

void carregarDados(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
);

void salvarDados(
    Veiculo *veiculos, int totalVeiculos,
    Cliente *clientes, int totalClientes,
    Venda *vendas, int totalVendas
);

int main() {

    Veiculo *veiculos = NULL;
    Cliente *clientes = NULL;
    Venda *vendas = NULL;

    int totalVeiculos = 0;
    int totalClientes = 0;
    int totalVendas = 0;

    int capacidadeVeiculos = INCREMENTO;
    int capacidadeClientes = INCREMENTO;
    int capacidadeVendas = INCREMENTO;

    veiculos = malloc(capacidadeVeiculos * sizeof(Veiculo));
    clientes = malloc(capacidadeClientes * sizeof(Cliente));
    vendas = malloc(capacidadeVendas * sizeof(Venda));

    if (veiculos == NULL || clientes == NULL || vendas == NULL) {
        printf("Erro ao alocar memoria!\n");

        free(veiculos);
        free(clientes);
        free(vendas);

        return 1;
    }

    carregarDados(
        &veiculos, &totalVeiculos, &capacidadeVeiculos,
        &clientes, &totalClientes, &capacidadeClientes,
        &vendas, &totalVendas, &capacidadeVendas
    );

    menuPrincipal(
        &veiculos, &totalVeiculos, &capacidadeVeiculos,
        &clientes, &totalClientes, &capacidadeClientes,
        &vendas, &totalVendas, &capacidadeVendas
    );

    salvarDados(
        veiculos, totalVeiculos,
        clientes, totalClientes,
        vendas, totalVendas
    );

    free(veiculos);
    free(clientes);
    free(vendas);

    printf("\nSistema encerrado.\n");

    return 0;
}