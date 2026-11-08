#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"

/* Retornam 1 quando a leitura e valida e 0 quando e invalida. */
int lerTexto(char *texto, int tamanho);
int lerInteiro(int *numero);
int lerReal(float *numero);
int normalizarCPF(char *cpf);

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

int carregarDados(
    Veiculo **veiculos, int *totalVeiculos, int *capacidadeVeiculos,
    Cliente **clientes, int *totalClientes, int *capacidadeClientes,
    Venda **vendas, int *totalVendas, int *capacidadeVendas
);

int salvarDados(
    const Veiculo *veiculos, int totalVeiculos,
    const Cliente *clientes, int totalClientes,
    const Venda *vendas, int totalVendas
);

#endif
