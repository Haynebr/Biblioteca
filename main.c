#include <stdio.h>
#include <stdlib.h>
#include "livros.h"
#include "usuarios.h"
#include "emprestimos.h"


void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}


void menuLivros() {
    int opcao;
    do {
        limparTela();
        printf("=============================\n");
        printf("        MENU LIVROS          \n");
        printf("=============================\n");
        printf("1. Cadastrar livro\n");
        printf("2. Listar livros\n");
        printf("3. Buscar livro\n");
        printf("4. Remover livro\n");
        printf("0. Voltar\n");
        printf("-----------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarLivro();       pausar(); break;
            case 2: listarLivros();         pausar(); break;
            case 3: buscarLivro();          pausar(); break;
            case 4: removerLivro();         pausar(); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); pausar();
        }
    } while (opcao != 0);
}

void menuUsuarios() {
    int opcao;
    do {
        limparTela();
        printf("=============================\n");
        printf("       MENU USUARIOS         \n");
        printf("=============================\n");
        printf("1. Cadastrar usuario\n");
        printf("2. Listar usuarios\n");
        printf("3. Buscar usuario\n");
        printf("4. Remover usuario\n");
        printf("0. Voltar\n");
        printf("-----------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarUsuario();     pausar(); break;
            case 2: listarUsuarios();       pausar(); break;
            case 3: buscarUsuario();        pausar(); break;
            case 4: removerUsuario();       pausar(); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); pausar();
        }
    } while (opcao != 0);
}

void menuEmprestimos() {
    int opcao;
    do {
        limparTela();
        printf("=============================\n");
        printf("      MENU EMPRESTIMOS       \n");
        printf("=============================\n");
        printf("1. Realizar emprestimo\n");
        printf("2. Registrar devolucao\n");
        printf("3. Listar emprestimos ativos\n");
        printf("4. Ver historico completo\n");
        printf("0. Voltar\n");
        printf("-----------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: realizarEmprestimo();       pausar(); break;
            case 2: registrarDevolucao();       pausar(); break;
            case 3: listarEmprestimosAtivos();  pausar(); break;
            case 4: listarHistorico();          pausar(); break;
            case 0: break;
            default: printf("Opcao invalida.\n"); pausar();
        }
    } while (opcao != 0);
}


int main() {
    int opcao;

    do {
        limparTela();
        printf("=============================\n");
        printf("    SISTEMA DE BIBLIOTECA    \n");
        printf("=============================\n");
        printf("1. Gerenciar Livros\n");
        printf("2. Gerenciar Usuarios\n");
        printf("3. Emprestimos\n");
        printf("0. Sair\n");
        printf("-----------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: menuLivros();      break;
            case 2: menuUsuarios();    break;
            case 3: menuEmprestimos(); break;
            case 0: printf("Encerrando o sistema...\n"); break;
            default: printf("Opcao invalida.\n"); pausar();
        }
    } while (opcao != 0);

    return 0;
}