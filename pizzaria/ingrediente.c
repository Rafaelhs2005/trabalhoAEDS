#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingrediente.h"

Ingrediente listaIngredientes[MAX_INGREDIENTES];
int totalIngredientes = 0;

void adicionarIngrediente() {
    if (totalIngredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido.\n");
        return;
    }
    
    Ingrediente novo;
    novo.id = totalIngredientes + 1;
    printf("Nome do ingrediente: ");
    scanf(" %[^\n]", novo.nome);
    printf("Preco do ingrediente: ");
    scanf("%f", &novo.preco);

    listaIngredientes[totalIngredientes++] = novo;
    printf("Ingrediente adicionado com sucesso!\n");
}