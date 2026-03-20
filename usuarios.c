#include <stdio.h>
#include <string.h>
#include "usuarios.h"

#define ARQUIVO_USUARIOS "usuarios.bin"


static int proximoIdUsuario() {
    FILE *fp = fopen(ARQUIVO_USUARIOS, "rb");
    if (fp == NULL) return 1;

    Usuario usuario;
    int maior_id = 0;
    while (fread(&usuario, sizeof(Usuario), 1, fp)) {
        if (usuario.id > maior_id)
            maior_id = usuario.id;
    }
    fclose(fp);
    return maior_id + 1;
}


void cadastrarUsuario() {
    Usuario novo;

    novo.id = proximoIdUsuario();

    printf("\n--- Cadastrar Usuario ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome);

    printf("CPF: ");
    scanf(" %[^\n]", novo.cpf);

    printf("Telefone: ");
    scanf(" %[^\n]", novo.telefone);

    FILE *fp = fopen(ARQUIVO_USUARIOS, "ab");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    fwrite(&novo, sizeof(Usuario), 1, fp);
    fclose(fp);

    printf("Usuario cadastrado com sucesso! ID: %d\n", novo.id);
}

void listarUsuarios() {
    FILE *fp = fopen(ARQUIVO_USUARIOS, "rb");
    if (fp == NULL) {
        printf("Nenhum usuario cadastrado ainda.\n");
        return;
    }

    Usuario usuario;
    int encontrou = 0;

    printf("\n--- Lista de Usuarios ---\n");
    printf("%-5s %-30s %-15s %-15s\n", "ID", "Nome", "CPF", "Telefone");
    printf("-------------------------------------------------------------\n");

    while (fread(&usuario, sizeof(Usuario), 1, fp)) {
        printf("%-5d %-30s %-15s %-15s\n",
               usuario.id, usuario.nome,
               usuario.cpf, usuario.telefone);
        encontrou = 1;
    }

    if (!encontrou)
        printf("Nenhum usuario encontrado.\n");

    fclose(fp);
}


void buscarUsuario() {
    char termo[80];
    printf("\n--- Buscar Usuario ---\n");
    printf("Digite o nome (ou parte dele): ");
    scanf(" %[^\n]", termo);

    FILE *fp = fopen(ARQUIVO_USUARIOS, "rb");
    if (fp == NULL) {
        printf("Nenhum usuario cadastrado ainda.\n");
        return;
    }

    Usuario usuario;
    int encontrou = 0;

    while (fread(&usuario, sizeof(Usuario), 1, fp)) {
        if (strstr(usuario.nome, termo) != NULL) {
            printf("\nID: %d\n", usuario.id);
            printf("Nome: %s\n", usuario.nome);
            printf("CPF: %s\n", usuario.cpf);
            printf("Telefone: %s\n", usuario.telefone);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum usuario encontrado com esse nome.\n");

    fclose(fp);
}


void removerUsuario() {
    int id;
    printf("\n--- Remover Usuario ---\n");
    printf("Digite o ID do usuario a remover: ");
    scanf("%d", &id);

    FILE *fp      = fopen(ARQUIVO_USUARIOS, "rb");
    FILE *fp_temp = fopen("usuarios_temp.bin", "wb");

    if (fp == NULL || fp_temp == NULL) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Usuario usuario;
    int encontrou = 0;

    while (fread(&usuario, sizeof(Usuario), 1, fp)) {
        if (usuario.id != id) {
            fwrite(&usuario, sizeof(Usuario), 1, fp_temp);
        } else {
            encontrou = 1;
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove(ARQUIVO_USUARIOS);
    rename("usuarios_temp.bin", ARQUIVO_USUARIOS);

    if (encontrou)
        printf("Usuario removido com sucesso.\n");
    else
        printf("Usuario com ID %d nao encontrado.\n", id);
}