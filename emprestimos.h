#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H

#include "livros.h"
#include "usuarios.h"

#define MAX_EMPRESTIMOS 200

typedef struct {
    int  id;
    int  id_livro;
    int  id_usuario;
    char data_emprestimo[12];  
    char data_devolucao[12];   
    int  ativo;               
} Emprestimo;


void realizarEmprestimo();
void registrarDevolucao();
void listarEmprestimosAtivos();
void listarHistorico();

#endif