#ifndef LIVROS_H
#define LIVROS_H


#define MAX_LIVROS 100


typedef struct {
    int    id;
    char   titulo[100];
    char   autor[80];
    int    ano;
    int    qtd_disponivel;
} Livro;

void cadastrarLivro();
void listarLivros();
void buscarLivro();
void removerLivro();

#endif