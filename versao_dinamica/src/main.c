#include <stdio.h>
#include <stdlib.h>
#include "../include/materia_ppc.h"
#include "../include/grade_oferta.h"

int main() {
    MateriaPPC* listaMaterias = criarEstruturaPPC();
    GradeOferta grade;

    inicializarOferta(&grade);
    criarEstruturaOferta(&grade);
    imprimirGradeOferta(&grade);
    
    liberarMaterias(listaMaterias);

    return 0;
}