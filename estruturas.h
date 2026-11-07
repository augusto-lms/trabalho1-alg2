#define INCREMENTO 5

typedef struct {
    int codigo;
    char modelo[50];
    int ano;
    float preco;
} Veiculo;

typedef struct {
    char cpf[15];
    char nome[100];
    char telefone[20];
    char email[100];
} Cliente;

typedef struct {
    int codigo;
    int codigoVeiculo;
    char cpfCliente[15];
    char data[11];
    float valor;
} Venda;