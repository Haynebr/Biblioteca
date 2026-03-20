#include <stdio.h>
#include <string.h>
#include "emprestimos.h"

#define ARQUIVO_EMPRESTIMOS "emprestimos.bin"
#define ARQUIVO_LIVROS      "livros.bin"

// Retorna o proximo ID disponivel para emprestimo
static int proximoIdEmprestimo() {
    FILE *fp = fopen(ARQUIVO_EMPRESTIMOS, "rb");
    if (fp == NULL) return 1; // arquivo ainda nao existe, comeca do 1

    Emprestimo emp;
    int maior_id = 0;
    while (fread(&emp, sizeof(Emprestimo), 1, fp)) {
        if (emp.id > maior_id)
            maior_id = emp.id;
    }
    fclose(fp);
    return maior_id + 1;
}

// Abre o livros.bin e reescreve a quantidade disponivel do livro informado
// variacao = -1 no emprestimo, +1 na devolucao
static void atualizarQtdLivro(int id_livro, int variacao) {
    FILE *fp = fopen(ARQUIVO_LIVROS, "rb+"); // rb+ = ler e escrever ao mesmo tempo
    if (fp == NULL) return;

    Livro livro;
    while (fread(&livro, sizeof(Livro), 1, fp)) {
        if (livro.id == id_livro) {
            livro.qtd_disponivel += variacao;
            fseek(fp, -(long)sizeof(Livro), SEEK_CUR); // volta um registro para reescrever
            fwrite(&livro, sizeof(Livro), 1, fp);
            break;
        }
    }
    fclose(fp);
}

// Registra um novo emprestimo e diminui o estoque do livro
void realizarEmprestimo() {
    Emprestimo novo;
    novo.id    = proximoIdEmprestimo();
    novo.ativo = 1; // 1 = emprestado, ainda nao devolvido

    printf("\n--- Realizar Emprestimo ---\n");
    printf("ID do livro: ");
    scanf("%d", &novo.id_livro);

    printf("ID do usuario: ");
    scanf("%d", &novo.id_usuario);

    printf("Data do emprestimo (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo.data_emprestimo);

    printf("Data prevista de devolucao (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo.data_devolucao);

    // Grava o emprestimo no arquivo
    FILE *fp = fopen(ARQUIVO_EMPRESTIMOS, "ab");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo de emprestimos.\n");
        return;
    }
    fwrite(&novo, sizeof(Emprestimo), 1, fp);
    fclose(fp);

    atualizarQtdLivro(novo.id_livro, -1); // diminui 1 do estoque do livro
    printf("Emprestimo realizado com sucesso! ID: %d\n", novo.id);
}

// Marca o emprestimo como devolvido e devolve 1 ao estoque do livro
void registrarDevolucao() {
    int id;
    printf("\n--- Registrar Devolucao ---\n");
    printf("ID do emprestimo: ");
    scanf("%d", &id);

    FILE *fp = fopen(ARQUIVO_EMPRESTIMOS, "rb+"); // rb+ para ler e reescrever
    if (fp == NULL) {
        printf("Nenhum emprestimo encontrado.\n");
        return;
    }

    Emprestimo emp;
    int encontrou = 0;
    while (fread(&emp, sizeof(Emprestimo), 1, fp)) {
        if (emp.id == id && emp.ativo == 1) {
            emp.ativo = 0; // marca como devolvido
            fseek(fp, -(long)sizeof(Emprestimo), SEEK_CUR); // volta para reescrever
            fwrite(&emp, sizeof(Emprestimo), 1, fp);
            atualizarQtdLivro(emp.id_livro, +1); // devolve 1 ao estoque
            encontrou = 1;
            break;
        }
    }
    fclose(fp);

    if (encontrou)
        printf("Devolucao registrada com sucesso.\n");
    else
        printf("Emprestimo ativo com ID %d nao encontrado.\n", id);
}

// Lista apenas os emprestimos com ativo == 1
void listarEmprestimosAtivos() {
    FILE *fp = fopen(ARQUIVO_EMPRESTIMOS, "rb");
    if (fp == NULL) {
        printf("Nenhum emprestimo registrado ainda.\n");
        return;
    }

    Emprestimo emp;
    int encontrou = 0;

    printf("\n--- Emprestimos Ativos ---\n");
    printf("%-5s %-10s %-10s %-14s %-14s\n",
           "ID", "Livro", "Usuario", "Emprestimo", "Devolucao");
    printf("---------------------------------------------------------------\n");

    while (fread(&emp, sizeof(Emprestimo), 1, fp)) {
        if (emp.ativo == 1) { // so mostra os nao devolvidos
            printf("%-5d %-10d %-10d %-14s %-14s\n",
                   emp.id, emp.id_livro, emp.id_usuario,
                   emp.data_emprestimo, emp.data_devolucao);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum emprestimo ativo no momento.\n");

    fclose(fp);
}

// Lista todos os emprestimos com coluna de status
void listarHistorico() {
    FILE *fp = fopen(ARQUIVO_EMPRESTIMOS, "rb");
    if (fp == NULL) {
        printf("Nenhum emprestimo registrado ainda.\n");
        return;
    }

    Emprestimo emp;
    int encontrou = 0;

    printf("\n--- Historico de Emprestimos ---\n");
    printf("%-5s %-10s %-10s %-14s %-14s %-10s\n",
           "ID", "Livro", "Usuario", "Emprestimo", "Devolucao", "Status");
    printf("-------------------------------------------------------------------\n");

    while (fread(&emp, sizeof(Emprestimo), 1, fp)) {
        printf("%-5d %-10d %-10d %-14s %-14s %-10s\n",
               emp.id, emp.id_livro, emp.id_usuario,
               emp.data_emprestimo, emp.data_devolucao,
               emp.ativo ? "Ativo" : "Devolvido"); // operador ternario para o status
        encontrou = 1;
    }

    if (!encontrou)
        printf("Nenhum emprestimo encontrado.\n");

    fclose(fp);
}