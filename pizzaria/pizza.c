#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pizza.h"
#include "ingrediente.h"

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

        if (id == -1) {
            adicionarMais = 0;
        }

        if (id < 1 || id > totalIngredientes) {
            printf("Ingrediente invalido.\n");
        }

        nova.ingredientes[nova.qtdIngredientes++] = listaIngredientes[id - 1];
    }

    cardapio[totalPizzas++] = nova;
    printf("Pizza adicionada com sucesso!\n");
}

void listarPizzas(){
    for (int i = 0; i < totalPizzas; i++){
        printf("ID: %d\nNome: %s\nTamanho: %c\nPreco: %.2f\n", cardapio[i].id, cardapio[i].nome, cardapio[i].tamanho, cardapio[i].preco);
        printf("Ingredientes:\n");
        for (int j = 0; j < cardapio[i].qtdIngredientes; j++){
            printf("- %s\n", cardapio[i].ingredientes[j].nome);
        }
        printf("\n");
    }
}

void editarPizza(){
    int id;
    printf("Digite o ID da pizza a editar: ");
    scanf("%d", &id);

    if (id < 1 || id > totalPizzas){
        printf("Pizza nao encontrada.\n");
        return;
    }

    Pizza *p = &cardapio[id - 1];

    printf("Novo nome da pizza: ");
    scanf(" %[^\n]", p->nome);
    printf("Novo tamanho da pizza (P/M/G): ");
    scanf(" %c", &p->tamanho);
    printf("Novo preco base da pizza: ");
    scanf("%f", &p->preco);

    int opcao;
    do{
        printf("\nIngredientes atuais da pizza:\n");
        for (int i = 0; i < p->qtdIngredientes; i++){
            printf("%d - %s\n", i + 1, p->ingredientes[i].nome);
        }

        printf("\nOpcoes:\n");
        printf("1. Adicionar ingrediente\n");
        printf("2. Remover ingrediente\n");
        printf("3. Finalizar edicao de ingredientes\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1){
            if (p->qtdIngredientes >= MAX_INGREDIENTES){
                printf("Limite de ingredientes atingido.\n");
            }
            else{
                listarIngredientes();
                printf("Digite o ID do ingrediente a adicionar: ");
                int ingId;
                scanf("%d", &ingId);

                if (ingId < 1 || ingId > totalIngredientes){
                    printf("Ingrediente invalido.\n");
                }
                else{
                    p->ingredientes[p->qtdIngredientes++] = listaIngredientes[ingId - 1];
                    printf("Ingrediente adicionado.\n");
                }
            }
        }
        else if (opcao == 2){
            if (p->qtdIngredientes == 0){
                printf("Nenhum ingrediente para remover.\n");
            }
            else{
                printf("Digite o número do ingrediente a remover: ");
                int ingNum;
                scanf("%d", &ingNum);

                if (ingNum < 1 || ingNum > p->qtdIngredientes){
                    printf("Número de ingrediente invalido.\n");
                }
                else{
                    for (int i = ingNum - 1; i < p->qtdIngredientes - 1; i++){
                        p->ingredientes[i] = p->ingredientes[i + 1];
                    }
                    p->qtdIngredientes--;
                    printf("Ingrediente removido.\n");
                }
            }
        }
    } while (opcao != 3);

    printf("Edição da pizza concluída!\n");
}

void removerPizza(){
    int id;
    printf("Digite o ID da pizza a remover: ");
    scanf("%d", &id);

    if (id < 1 || id > totalPizzas){
        printf("Pizza nao encontrada.\n");
        return;
    }

    for (int i = id - 1; i < totalPizzas - 1; i++){
        cardapio[i] = cardapio[i + 1]; // atuualiza ID
    }

    totalPizzas--;
    printf("Pizza removida com sucesso!\n");
}

void exportarPizzas(const char *filename){
    FILE *file = fopen(filename, "wb");

    if (!file){
        perror("Erro ao abrir arquivo para exportacao");
        return;
    }

    fwrite(&totalPizzas, sizeof(int), 1, file);

    for (int i = 0; i < totalPizzas; i++){
        fwrite(&cardapio[i], sizeof(Pizza), 1, file);
    }

    fclose(file);
}

void importarPizzas(const char *filename){
    FILE *file = fopen(filename, "rb");

    if (!file){
        perror("Erro ao abrir arquivo para importacao");
        return;
    }

    fread(&totalPizzas, sizeof(int), 1, file);

    for (int i = 0; i < totalPizzas && i < MAX_PIZZAS; i++){
        fread(&cardapio[i], sizeof(Pizza), 1, file);

        cardapio[i].id = i + 1;

        cardapio[i].qtdIngredientes = sizeof(cardapio[i].ingredientes) / sizeof(Ingrediente);

        if (cardapio[i].qtdIngredientes > MAX_INGREDIENTES){
            cardapio[i].qtdIngredientes = MAX_INGREDIENTES;
        }

        for (int j = 0; j < cardapio[i].qtdIngredientes; j++){
            if (strlen(cardapio[i].ingredientes[j].nome) == 0)
            {
                strcpy(cardapio[i].ingredientes[j].nome, "Ingrediente desconhecido");
            }
        }

        for (int j = 0; j < cardapio[i].qtdIngredientes; j++){
            if (cardapio[i].ingredientes[j].preco <= 0.0f)
            {
                cardapio[i].ingredientes[j].preco = 0.01f;
            }
        }

        for (int j = 0; j < cardapio[i].qtdIngredientes; j++){
            cardapio[i].ingredientes[j].id = j + 1;
        }
    }

    fclose(file);
}