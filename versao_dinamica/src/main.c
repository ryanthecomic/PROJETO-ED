#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/materia_ppc.h"
#include "../include/aluno.h"
#include "../include/oferta.h"

int main() {
    MateriaPPC *listaMaterias = criarEstruturaPPC();
    Aluno *aluno = lerHistorico();

    //char nome_aluno[100] = "Roberta Martins Silva";
    char nome_aluno[100] = "Rian Antonio da Silva Gaiao";

    OfertaDisciplinas *oferta = criarOfertaDisciplinas(20);
    GradeHoraria grade;
    inicializarGrade(&grade);

    // Menu interativo
    int option = -1;
    while(true) {
        printf("\n=== SISTEMA DE ACONSELHAMENTO DE MATRÍCULA ===\n");
        printf("Aluno: %s\n", nome_aluno);
        printf("1 - Mostrar grade horária do aluno\n");
        printf("2 - Mostrar disciplinas sugeridas\n");
        printf("3 - Mostrar histórico\n");
        printf("4 - Adicionar disciplinas ofertadas\n");
        printf("5 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &option);

        switch(option) {
        case 1:
            mostrarGrade(&grade);
            break;
        case 2:
            printf("\nDisciplinas sugeridas:\n");
            for(int i = 0; i < oferta->quantidade; i++) {
                printf("- %s (Carga: %dh)\n", oferta->disciplinas[i].codigo,
                       oferta->disciplinas[i].carga_horaria);
            }
            printf("Carga horária total: %dh\n",
                   calcularCargaHorariaTotal(oferta));
            break;
        case 3:
            imprimirHistorico(aluno);
            break;
        case 4: {
                // Limpa a oferta atual
                liberarOfertaDisciplinas(oferta);
                oferta = criarOfertaDisciplinas(20);

                // Gera nova oferta
                gerarOfertaPersonalizada(nome_aluno, listaMaterias, aluno, oferta);

                // Atualiza grade
                preencherGrade(&grade, oferta);

                printf("Oferta gerada com sucesso!\n");
                break;
        }

            preencherGrade(&grade, oferta);

            break;
        case 5:
            liberarMaterias(listaMaterias);
            liberarAluno(aluno);
            liberarOfertaDisciplinas(oferta);
            exit(0);
        default:
            printf("Opção inválida!\n");
        }
    }
}