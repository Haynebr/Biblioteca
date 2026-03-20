#include <stdio.h>
#include <string.h>
#include "livros.h"    

#define ARQUIVO_LIVROS "livros.bin"   


static int proximoIdLivro() {
    FILE *fp = fopen(ARQUIVO_LIVROS, "rb");
    if (fp == NULL) return 1;  

    Livro livro;
    int maior_id = 0;
    while (fread(&livro, sizeof(Livro), 1, fp)) {
        if (livro.id > maior_id)
            maior_id = livro.id;
    }
    fclose(fp);
    return maior_id + 1;
}


void cadastrarLivro() {
    Livro novo;

    novo.id = proximoIdLivro();

    printf("\n--- Cadastrar Livro ---\n");
    printf("Titulo: ");
    scanf(" %[^\n]", novo.titulo);   

    printf("Autor: ");
    scanf(" %[^\n]", novo.autor);

    printf("Ano: ");
    scanf("%d", &novo.ano);

    printf("Quantidade disponivel: ");
    scanf("%d", &novo.qtd_disponivel);

    
    FILE *fp = fopen(ARQUIVO_LIVROS, "ab");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de livros.\n");
        return;
    }

    fwrite(&novo, sizeof(Livro), 1, fp);
    fclose(fp);

    printf("Livro cadastrado com sucesso! ID: %d\n", novo.id);
}


void listarLivros() {
    FILE *fp = fopen(ARQUIVO_LIVROS, "rb");
    if (fp == NULL) {
        printf("Nenhum livro cadastrado ainda.\n");
        return;
    }

    Livro livro;
    int encontrou = 0;

    printf("\n--- Lista de Livros ---\n");
    printf("%-5s %-40s %-30s %-6s %-10s\n",
           "ID", "Titulo", "Autor", "Ano", "Disponivel");
    printf("---------------------------------------------------------------------\n");

    while (fread(&livro, sizeof(Livro), 1, fp)) {
        printf("%-5d %-40s %-30s %-6d %-10d\n",
               livro.id, livro.titulo, livro.autor,
               livro.ano, livro.qtd_disponivel);
        encontrou = 1;
    }

    if (!encontrou)
        printf("Nenhum livro encontrado.\n");

    fclose(fp);
}


void buscarLivro() {
    char termo[100];
    printf("\n--- Buscar Livro ---\n");
    printf("Digite o titulo (ou parte dele): ");
    scanf(" %[^\n]", termo);

    FILE *fp = fopen(ARQUIVO_LIVROS, "rb");
    if (fp == NULL) {
        printf("Nenhum livro cadastrado ainda.\n");
        return;
    }

    Livro livro;
    int encontrou = 0;

    while (fread(&livro, sizeof(Livro), 1, fp)) {
        if (strstr(livro.titulo, termo) != NULL) {
            printf("\nID: %d\n", livro.id);
            printf("Titulo: %s\n", livro.titulo);
            printf("Autor: %s\n", livro.autor);
            printf("Ano: %d\n", livro.ano);
            printf("Disponivel: %d\n", livro.qtd_disponivel);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum livro encontrado com esse titulo.\n");

    fclose(fp);
}


void removerLivro() {
    int id;
    printf("\n--- Remover Livro ---\n");
    printf("Digite o ID do livro a remover: ");
    scanf("%d", &id);

    FILE *fp      = fopen(ARQUIVO_LIVROS, "rb");
    FILE *fp_temp = fopen("livros_temp.bin", "wb");

    if (fp == NULL || fp_temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Livro livro;
    int encontrou = 0;


    while (fread(&livro, sizeof(Livro), 1, fp)) {
        if (livro.id != id) {
            fwrite(&livro, sizeof(Livro), 1, fp_temp);
        } else {
            encontrou = 1;
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove(ARQUIVO_LIVROS);
    rename("livros_temp.bin", ARQUIVO_LIVROS);

    if (encontrou)
        printf("Livro removido com sucesso.\n");
    else
        printf("Livro com ID %d nao encontrado.\n", id);
}