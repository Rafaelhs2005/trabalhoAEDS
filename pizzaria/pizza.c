#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"

Pizza cardapio[MAX_PIZZAS];
int totalPizzas = 0;

void adicionarPizza() {
    if (totalPizzas >= MAX_PIZZAS) {
        printf("Limite de pizzas atingido.\n");
        return;
    }

    Pizza nova;
    nova.id = totalPizzas + 1;
    nova.qtdIngredientes = 0;

    printf("Nome da pizza: ");
    scanf(" %[^\n]", nova.nome);
    printf("Tamanho da pizza (P/M/G): ");
    scanf(" %c", &nova.tamanho);
    printf("Preco base da pizza: ");
    scanf("%f", &nova.preco);

    int adicionarMais = 1;
    while (adicionarMais && nova.qtdIngredientes < MAX_INGREDIENTES) {
        listarIngredientes();
        printf("Digite o ID do ingrediente a adicionar (-1 para parar): ");
        int id;
        scanf("%d", &id);

        if (id == -1) break;

        if (id < 1 || id > totalIngredientes) {
            printf("Ingrediente invalido.\n");
            continue;
        }

        nova.ingredientes[nova.qtdIngredientes++] = listaIngredientes[id - 1];
    }

    cardapio[totalPizzas++] = nova;
    printf("Pizza adicionada com sucesso!\n");
}