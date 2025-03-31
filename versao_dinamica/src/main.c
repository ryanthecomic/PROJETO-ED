#include <stdio.h>
#include <stdlib.h>
#include "../include/materia_ppc.h"

int main() {
    MateriaPPC *listaMaterias = criarEstruturaPPC();

    imprimirListaMaterias(listaMaterias);
    
    liberarMaterias(listaMaterias);

    return 0;
}