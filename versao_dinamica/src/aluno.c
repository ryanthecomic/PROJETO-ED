#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/aluno.h"
#include "../include/materia_ppc.h"

Aluno* criarAluno(){
    Aluno* novoAluno = malloc(sizeof(Aluno));

    if(novoAluno == NULL){
        printf("Erro ao alocar memória para aluno.\n");
        return NULL;
    }

    novoAluno->Periodo = 0;
    novoAluno->Materias = NULL;

    return novoAluno;
}

Aluno* lerHistorico(){
    FILE *historico = fopen("data/historico.txt", "rt");

    if(historico == NULL){
        printf("Erro ao abrir arquivo de histórico.\n");
        return NULL;
    }

    Aluno *aluno = criarAluno();

    MateriaCursada *ultimaMateria = NULL;

    char linha[MAX_LINHA];
    fgets(linha, MAX_LINHA, historico);
    linha[strcspn(linha, "\n")] = '\0';

    aluno->Periodo = atoi(linha + 8);

    char *save_1;

    while(fgets(linha, MAX_LINHA, historico)){
        linha[strcspn(linha, "\n")] = '\0';
        
        char *codigo = strtok_r(linha, "=", &save_1);

        char *nota = strtok_r(NULL, "=", &save_1);

        if(codigo && nota){
            MateriaCursada *novaMateria = malloc(sizeof(MateriaCursada));

            if(novaMateria == NULL){
                printf("Erro ao alocar memória para matéria cursada.\n");
                return NULL;
            }

            strncpy(novaMateria->Codigo, codigo, MAX_CODIGO);
            novaMateria->Nota = atof(nota);
            novaMateria->Proxima = NULL;

            if(aluno->Materias == NULL){
                aluno->Materias = novaMateria;
            } else {
                ultimaMateria->Proxima = novaMateria;
            }
            ultimaMateria = novaMateria;
        }
    }
    fclose(historico);
    return aluno;
}

void imprimirHistorico(Aluno *aluno){
    MateriaCursada *atual = aluno->Materias;

    printf("\nDisciplina(s) paga(s):\n");
    while(atual != NULL){
        printf("%s: %.1lf\n", atual->Codigo, atual->Nota);
        atual = atual->Proxima;
    }
    printf("\n--- Fim ---\n");
}

void liberarAluno(Aluno *aluno) {
    if (aluno == NULL) return;

    // Libera a lista de matérias cursadas
    MateriaCursada *atual = aluno->Materias;
    while (atual != NULL) {
        MateriaCursada *proxima = atual->Proxima;
        free(atual);
        atual = proxima;
    }

    // Libera a estrutura do aluno
    free(aluno);
}