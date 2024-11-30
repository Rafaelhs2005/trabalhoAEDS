#include "pizza.h"
#include "ingrediente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    } else if (id < 1 || id > totalIngredientes) {
      printf("Ingrediente invalido.\n");
    } else {
      nova.ingredientes[nova.qtdIngredientes++] = listaIngredientes[id - 1];
    }
  }

  cardapio[totalPizzas++] = nova;
  printf("Pizza adicionada com sucesso!\n");
}

void listarPizzas() {
  for (int i = 0; i < totalPizzas; i++) {
    printf("ID: %d\nNome: %s\nTamanho: %c\nPreco: %.2f\n", cardapio[i].id,
           cardapio[i].nome, cardapio[i].tamanho, cardapio[i].preco);
    printf("Ingredientes:\n");
    for (int j = 0; j < cardapio[i].qtdIngredientes; j++) {
      printf("- %s\n", cardapio[i].ingredientes[j].nome);
    }
    printf("\n");
  }
}

void editarPizza() {
  int id;
  printf("Digite o ID da pizza a editar: ");
  scanf("%d", &id);

  if (id < 1 || id > totalPizzas) {
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
  do {
    printf("\nIngredientes atuais da pizza:\n");
    for (int i = 0; i < p->qtdIngredientes; i++) {
      printf("%d - %s\n", i + 1, p->ingredientes[i].nome);
    }

    printf("\nOpcoes:\n");
    printf("1. Adicionar ingrediente\n");
    printf("2. Remover ingrediente\n");
    printf("3. Finalizar edicao de ingredientes\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      if (p->qtdIngredientes >= MAX_INGREDIENTES) {
        printf("Limite de ingredientes atingido.\n");
      } else {
        listarIngredientes();
        printf("Digite o ID do ingrediente a adicionar: ");
        int ingId;
        scanf("%d", &ingId);

        if (ingId < 1 || ingId > totalIngredientes) {
          printf("Ingrediente invalido.\n");
        } else {
          p->ingredientes[p->qtdIngredientes++] = listaIngredientes[ingId - 1];
          printf("Ingrediente adicionado.\n");
        }
      }
    } else if (opcao == 2) {
      if (p->qtdIngredientes == 0) {
        printf("Nenhum ingrediente para remover.\n");
      } else {
        printf("Digite o número do ingrediente a remover: ");
        int ingNum;
        scanf("%d", &ingNum);

        if (ingNum < 1 || ingNum > p->qtdIngredientes) {
          printf("Número de ingrediente invalido.\n");
        } else {
          for (int i = ingNum - 1; i < p->qtdIngredientes - 1; i++) {
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

void removerPizza() {
  int id;
  printf("Digite o ID da pizza a remover: ");
  scanf("%d", &id);

  if (id < 1 || id > totalPizzas) {
    printf("Pizza nao encontrada.\n");
    return;
  }

  for (int i = id - 1; i < totalPizzas - 1; i++) {
    cardapio[i] = cardapio[i + 1]; 
  }

  totalPizzas--;
  printf("Pizza removida com sucesso!\n");
}

void exportarPizzas(const char *filename) {
  FILE *file = fopen(filename, "w"); 

  if (!file) {
    perror("Erro ao abrir arquivo para exportacao");
    return;
  }

  fprintf(file, "%d\n", totalPizzas);

  for (int i = 0; i < totalPizzas; i++) {
    fprintf(file, "%d,%s,%c,%.2f,%d\n", cardapio[i].id, cardapio[i].nome,
            cardapio[i].tamanho, cardapio[i].preco,
            cardapio[i].qtdIngredientes);

    for (int j = 0; j < cardapio[i].qtdIngredientes; j++) {
      fprintf(file, "%s,%.2f\n", cardapio[i].ingredientes[j].nome,
              cardapio[i].ingredientes[j].preco);
    }
  }

  fclose(file);
  printf("Pizzas exportadas com sucesso!\n");
}

void importarPizzas(const char *filename) {
  FILE *file = fopen(filename, "r");

  if (!file) {
    perror("Erro ao abrir arquivo para importacao");
    return;
  }

  fscanf(file, "%d\n", &totalPizzas);

  for (int i = 0; i < totalPizzas && i < MAX_PIZZAS; i++) {
    fscanf(file, "%d,%[^,],%c,%f,%d\n", &cardapio[i].id, cardapio[i].nome,
           &cardapio[i].tamanho, &cardapio[i].preco,
           &cardapio[i].qtdIngredientes);

    for (int j = 0; j < cardapio[i].qtdIngredientes && j < MAX_INGREDIENTES;
         j++) {
      fscanf(file, "%[^,],%f\n", cardapio[i].ingredientes[j].nome,
             &cardapio[i].ingredientes[j].preco);

      cardapio[i].ingredientes[j].id = j + 1;
    }
  }

  fclose(file);
  printf("Pizzas importadas com sucesso!\n");
}

void venderPizza() {
    int idPizza;
    printf("Selecione uma pizza do cardápio (digite o ID da pizza):\n");
    listarPizzas();  
    scanf("%d", &idPizza);

    if (idPizza < 1 || idPizza > totalPizzas) {
        printf("Pizza não encontrada.\n");
        return;
    }

    Pizza *pizzaSelecionada = &cardapio[idPizza - 1];
    printf("Você selecionou a pizza: %s\n", pizzaSelecionada->nome);
    printf("Preço base da pizza: %.2f\n", pizzaSelecionada->preco);

    float precoFinal = pizzaSelecionada->preco;

    int adicionarMais = 1;
    while (adicionarMais) {
        printf("\nDeseja adicionar mais ingredientes?\n");
        printf("1. Sim\n");
        printf("2. Não\n");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 1) {
            listarIngredientes();  
            printf("Digite o ID do ingrediente adicional que deseja adicionar: ");
            int idIngrediente;
            scanf("%d", &idIngrediente);


            if (idIngrediente < 1 || idIngrediente > totalIngredientes) {
                printf("Ingrediente inválido.\n");
            } else {

                Ingrediente ingredienteSelecionado = listaIngredientes[idIngrediente - 1];
                precoFinal += ingredienteSelecionado.preco;
                printf("Ingrediente %s adicionado com sucesso! Preço adicional: %.2f\n", ingredienteSelecionado.nome, ingredienteSelecionado.preco);
            }
        } else if (opcao == 2) {
            adicionarMais = 0;  
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    printf("\nPreço final da pizza: %.2f\n", precoFinal);
    printf("Venda registrada com sucesso!\n");
}