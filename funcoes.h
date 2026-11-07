#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"

void cadastrarVeiculo(Veiculo **veiculos, int *total, int *capacidade);
void consultarVeiculo(const Veiculo *veiculos, int total);
void alterarVeiculo(Veiculo *veiculos, int total);
void removerVeiculo(Veiculo *veiculos, int *total);
void listarVeiculos(const Veiculo *veiculos, int total);

void cadastrarCliente(Cliente **clientes, int *total, int *capacidade);
void consultarCliente(const Cliente *clientes, int total);
void alterarCliente(Cliente *clientes, int total);
void removerCliente(Cliente *clientes, int *total);
void listarClientes(const Cliente *clientes, int total);

void carregarDados(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
);

void salvarDados(
    const Veiculo *veiculos, int totalVeiculos,
    const Cliente *clientes, int totalClientes,
    const Venda *vendas, int totalVendas
);

#endif
