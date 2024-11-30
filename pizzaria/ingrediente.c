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

void listarIngredientes() {
    for (int i = 0; i < totalIngredientes; i++) {
        printf("%d - %s\n", listaIngredientes[i].id, listaIngredientes[i].nome);
    }
}

void editarIngrediente(void) {
    int id;
    printf("Digite o ID do ingrediente a editar: ");
    scanf("%d", &id);

    if (id < 1 || id > totalIngredientes) {
        printf("Ingrediente nao encontrado.\n");
        return;
    }

    Ingrediente *ing = &listaIngredientes[id - 1];

    printf("Novo nome do ingrediente: ");
    scanf(" %[^\n]", ing->nome);
    printf("Novo preco do ingrediente: ");
    scanf("%f", &ing->preco);

    printf("Ingrediente editado com sucesso!\n");
}

void removerIngrediente(void) {
    int id;
    printf("Digite o ID do ingrediente a remover: ");
    scanf("%d", &id);

    if (id < 1 || id > totalIngredientes) {
        printf("Ingrediente nao encontrado.\n");
        return;
    }

    for (int i = id - 1; i < totalIngredientes - 1; i++) {
        listaIngredientes[i] = listaIngredientes[i + 1];
        listaIngredientes[i].id = i + 1; //atualiza o ID
    }
    
    totalIngredientes--;
    printf("Ingrediente removido com sucesso!\n");
}

void exportarIngredientes(const char *filename) {
    FILE *file = fopen(filename, "wb");
    
    if (!file) {
        perror("Erro ao abrir arquivo para exportacao");
        return;
    }
    
    fwrite(&totalIngredientes, sizeof(int), 1, file);
    
    for (int i = 0; i < totalIngredientes; i++) {
        fwrite(&listaIngredientes[i], sizeof(Ingrediente), 1, file);
    }
    
    fclose(file);
}

void importarIngredientes(const char *filename) {
    FILE *file = fopen(filename, "rb");
    
    if (!file) {
        perror("Erro ao abrir arquivo para importacao");
        return;
    }
    
    fread(&totalIngredientes, sizeof(int), 1, file);
    
    for (int i = 0; i < totalIngredientes && i < MAX_INGREDIENTES; i++) {
    fread(&listaIngredientes[i], sizeof(Ingrediente), 1, file);
    
    listaIngredientes[i].id = i + 1;

    if (strlen(listaIngredientes[i].nome) == 0) {
        strcpy(listaIngredientes[i].nome, "Ingrediente desconhecido");
    }
    
    if (listaIngredientes[i].preco <= 0.0f) {
        listaIngredientes[i].preco = 0.01f; // preço mínimo
    }
}

     fclose(file);
}