#include <stdio.h>
#include "ingrediente.h"
#include "pizza.h"

void menu() {
    int opcao;
    do {
        printf("\n--- Sistema de Gerenciamento de Pizzaria ---\n");
        printf("1. Adicionar Ingrediente\n");
        printf("2. Listar Ingredientes\n");
        printf("3. Editar Ingrediente\n");
        printf("4. Remover Ingrediente\n");
        printf("5. Adicionar Pizza\n");
        printf("6. Listar Pizzas\n");
        printf("7. Exportar Dados\n");
        printf("8. Importar Dados\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarIngrediente(); break;
            case 2: listarIngredientes(); break;
            case 3: editarIngrediente(); break;
            case 4: removerIngrediente(); break;
            case 5: adicionarPizza(); break;
            case 6: listarPizzas(); break;
            case 7:
                exportarIngredientes("ingredientes.dat");
                exportarPizzas("pizzas.dat");
                break;
            case 8:
                importarIngredientes("ingredientes.dat");
                importarPizzas("pizzas.dat");
                break;
            case 9: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 9);
}

int main() {
    menu();
    return 0;
}

