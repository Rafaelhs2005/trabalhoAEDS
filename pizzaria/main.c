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
        printf("6. Editar Pizza\n");
        printf("7. Remover Pizza\n");
        printf("8. Listar Pizzas\n");
        printf("9. Vender Pizza\n");
        printf("10. Exportar Dados\n");
        printf("11. Importar Dados\n");
        printf("12. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarIngrediente(); break;
            case 2: listarIngredientes(); break;
            case 3: editarIngrediente(); break;
            case 4: removerIngrediente(); break;
            case 5: adicionarPizza(); break;
            case 6: editarPizza(); break;
            case 7: removerPizza(); break;
            case 8: listarPizzas(); break;
            case 9: venderPizza(); break;
            case 10:
                exportarIngredientes("ingredientes.txt");
                exportarPizzas("pizzas.txt");
                break;
            case 11:
                importarIngredientes("ingredientes.txt");
                importarPizzas("pizzas.txt");
                break;
            case 12: printf("Saindo... Volte sempre!\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 12);
}

int main() {
    menu();
    return 0;
}
