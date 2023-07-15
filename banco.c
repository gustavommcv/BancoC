#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNascimento[20];
    char dataCadastro[20];
} Cliente;

typedef struct {
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal; // Saldo + Limite
} Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizaSaldoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta conta_origem, Conta conta_destino, float valor);

static Conta contas[50];
static int contador_contas = 0;
static int contador_clientes = 0;

int main(void) {

    menu();

    return 0;
}

void menu() {
    int opcao = 0;
    system("cls");
    printf("=====================================================\n");
    printf("========================= ATM =======================\n");
    printf("=====================================================\n");

    printf("Selecione uma opcao abaixo:\n");
    printf("1 - Criar conta\n");
    printf("2 - Efetuar saque\n");
    printf("3 - Efetuar deposito\n");
    printf("4 - Efetuar transferencia\n");
    printf("5 - Listar contas\n");
    printf("6 - Sair do sistema\n");

    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
        criarConta();
        break;
    case 2:
        efetuarSaque();
        break;
    case 3:
        efetuarDeposito();
        break;
    case 4:
        efetuarTransferencia();
        break;
    case 5:
        listarContas();
        break;
    case 6:
        printf("Ate a proxima\n");
        Sleep(2000);
        exit(0);
        break;

    default:
        printf("Opcao invalida!\n");
        Sleep(2000);
        menu();
        break;
    }
}

void infoCliente(Cliente cliente) {
    printf("Codigo: %d\nNome: %s\nData de Nascimento: %s\nCadastro: %s", cliente.codigo, strtok(cliente.nome, "\n"), strtok(cliente.dataNascimento, "\n"), strtok(cliente.dataCadastro, "\n"));
}

void infoConta(Conta conta) {
    printf("Numero da conta: %d\nCliente: %s\nData de Nascimento: %s\nData cadastro: %s\nSaldo Total: %.2f\n", conta.cliente.codigo, strtok(conta.cliente.nome, "\n"), strtok(conta.cliente.dataNascimento, "\n"), strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}

void criarConta() {

}

void efetuarSaque() {

}

void efetuarDeposito() {

}

void efetuarTransferencia() {

}

void listarContas() {

}

float atualizaSaldoTotal(Conta conta) {
    return conta.saldo + conta.limite;
}

Conta buscarContaPorNumero(int numero) {
    Conta c;
    if (contador_contas > 0) {
        for (int i = 0; i < contador_contas; i++) {
            if (contas[i].numero == numero) {
                c = contas[i];
            }
        }
    }
    return c;
}

void sacar(Conta conta, float valor) {
    if (valor > 0 && conta.saldoTotal >= valor) {
        for (int i = 0; i < contador_contas; i++) {
            if (contas[i].numero == conta.numero) {
                if (contas[i].saldo >= valor) {
                    contas[i].saldo = contas[i].saldo - valor;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso\n");
                } else {
                    float restante = contas[i].saldo - valor;
                    contas[i].limite = contas[i].limite - restante;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                    printf("Saque efetuado com sucesso!\n");
                }
            }
        }
        
    } else {
        printf("Saque nao realizado. Tente novamente.\n");
    }
}

void depositar(Conta conta, float valor) {
    if (valor > 0) {
        for(int i = 0; i < contador_contas; i++) {
            if (contas[i].numero == conta.numero) {
                contas[i].saldo = contas[i].saldo + valor;
                contas[i].saldoTotal = atualizaSaldoTotal(contas[i]);
                printf("Deposito efetuado com sucesso!\n");
            }
        }
    } else {
        printf("Erro ao efetuar deposito. Tente novamente.\n");
    }
}

void transferir(Conta conta_origem, Conta conta_destino, float valor) {
    if (valor > 0 && conta_origem.saldoTotal >= valor) {
        for (int co = 0; co < contador_contas; co++) {
            if (contas[co].numero == conta_origem.numero) {
                for (int cd = 0; cd < contador_contas; cd++) {
                    if (contas[co].saldo >= valor) {
                        contas[co].saldo = contas[co].saldo - valor;
                        contas[cd].saldo = contas[cd].saldo + valor;
                        contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                        contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                        printf("Transferencia realizada com sucesso!\n");
                    } else {
                        float restante = contas[co].saldo - valor;
                        contas[co].limite = contas[co].limite + restante;
                        contas[co].saldo = 0.0;
                        contas[cd].saldo = contas[cd].saldo + valor;
                        contas[co].saldoTotal = atualizaSaldoTotal(contas[co]);
                        contas[cd].saldoTotal = atualizaSaldoTotal(contas[cd]);
                        printf("Transferencia realizada com sucesso!\n");
                    }
                }
                
            }
        }
        
    } else {
        printf("Transferencia nao realizada. Tente novamente.\n");
    }
}

