#include <stdio.h>
#include <stdlib.h>
#include "../include/materia_ppc.h"
#include "../include/aluno.h"

int main() {
    MateriaPPC *listaMaterias = criarEstruturaPPC();

    Aluno *aluno = lerHistorico();

    imprimirHistorico(aluno);

    //imprimirListaMaterias(listaMaterias);
    
    liberarMaterias(listaMaterias);

    liberarAluno(aluno);  // Adicione esta linha

    return 0;
}