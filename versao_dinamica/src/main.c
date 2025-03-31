#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/materia_ppc.h"
#include "../include/aluno.h"
#include "../include/oferta.h"

int main() {
    MateriaPPC *listaMaterias = criarEstruturaPPC();
    Aluno *aluno = lerHistorico();

    // Inicializa oferta e grade
    OfertaDisciplinas *oferta = criarOfertaDisciplinas(50);
    GradeHoraria grade;
    inicializarGrade(&grade);

    // Adiciona matérias do PPC à oferta
    for (MateriaPPC *m = listaMaterias; m != NULL; m = m->Proxima) {
        adicionarDisciplinaOfertada(oferta, m);
    }

    preencherGrade(&grade, oferta);

    int option = -1;
    while (true) {
        printf("\nMENU SIGAA:\n"
               "1 - Mostrar histórico do aluno\n"
               "2 - Mostrar todas as matérias do PPC\n"
               "3 - Mostrar grade horária\n"
               "4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            imprimirHistorico(aluno);
            break;
        case 2:
            imprimirListaMaterias(listaMaterias);
            break;
        case 3:
            mostrarGrade(&grade);
            break;
        case 4:
            liberarMaterias(listaMaterias);
            liberarAluno(aluno);
            liberarOfertaDisciplinas(oferta);
            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }
}