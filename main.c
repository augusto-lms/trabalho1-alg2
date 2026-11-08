
#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"
#include "menus.h"

int main(void) {

    int salvou;

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

    if (!carregarDados(
        &veiculos, &totalVeiculos, &capacidadeVeiculos,
        &clientes, &totalClientes, &capacidadeClientes,
        &vendas, &totalVendas, &capacidadeVendas
    )) {
        printf("Falha na carga. Os arquivos originais nao serao sobrescritos.\n");
        free(veiculos);
        free(clientes);
        free(vendas);
        return 1;
    }

    menuPrincipal(
        &veiculos, &totalVeiculos, &capacidadeVeiculos,
        &clientes, &totalClientes, &capacidadeClientes,
        &vendas, &totalVendas, &capacidadeVendas
    );

    salvou = salvarDados(
        veiculos, totalVeiculos,
        clientes, totalClientes,
        vendas, totalVendas
    );

    free(veiculos);
    free(clientes);
    free(vendas);

    printf("\nSistema encerrado.\n");

    return salvou ? 0 : 1;
}
