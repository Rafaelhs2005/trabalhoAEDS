#ifndef PIZZA_H
#define PIZZA_H

#include "ingrediente.h"

#define MAX_PIZZAS 100

typedef struct {
    int id;
    char nome[MAX_NOME];
    char tamanho; // P, M ou G
    float preco;
    int qtdIngredientes;
    Ingrediente ingredientes[MAX_INGREDIENTES];
} Pizza;

void adicionarPizza();
void listarPizzas();
void editarPizza();
void removerPizza();
void exportarPizzas(const char *filename);
void importarPizzas(const char *filename);

#endif
