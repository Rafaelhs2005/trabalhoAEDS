#ifndef INGREDIENTE_H
#define INGREDIENTE_H

#define MAX_NOME 50
#define MAX_INGREDIENTES 50

typedef struct {
    int id;
    char nome[MAX_NOME];
    float preco;
} Ingrediente;

extern Ingrediente listaIngredientes[MAX_INGREDIENTES];
extern int totalIngredientes;

void adicionarIngrediente();
void listarIngredientes();
void editarIngrediente();
void removerIngrediente();
void exportarIngredientes(const char *filename);
void importarIngredientes(const char *filename);

#endif
