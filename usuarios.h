#ifndef USUARIOS_H
#define USUARIOS_H


#define MAX_USUARIOS 100


typedef struct {
    int  id;
    char nome[80];
    char cpf[15];
    char telefone[15];
} Usuario;


void cadastrarUsuario();
void listarUsuarios();
void buscarUsuario();
void removerUsuario();

#endif