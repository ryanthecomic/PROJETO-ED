#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/oferta.h"

OfertaDisciplinas* criarOfertaDisciplinas(int capacidade) {
    OfertaDisciplinas *oferta = malloc(sizeof(OfertaDisciplinas));
    if (!oferta) return NULL;

    oferta->disciplinas = malloc(capacidade * sizeof(DisciplinaOfertada));
    if (!oferta->disciplinas) {
        free(oferta);
        return NULL;
    }

    oferta->quantidade = 0;
    oferta->capacidade = capacidade;
    return oferta;
}

void liberarOfertaDisciplinas(OfertaDisciplinas *oferta) {
    if (oferta) {
        free(oferta->disciplinas);
        free(oferta);
    }
}

void inicializarGrade(GradeHoraria *grade) {
    for (int dia = 0; dia < DIAS_SEMANA; dia++) {
        for (int horario = 0; horario < HORARIOS_DIA; horario++) {
            strcpy(grade->grade[dia][horario].codigo_disciplina, "------ ");
        }
    }
}

void adicionarDisciplinaOfertada(OfertaDisciplinas *oferta, MateriaPPC *materia) {
    if (!oferta || !materia || oferta->quantidade >= oferta->capacidade) return;

    // Concatena todos os horários em uma string
    char horarios_combinados[MAX_HORARIO] = "";
    HorariosMateriaPPC *horario_atual = materia->Horarios;

    while (horario_atual) {
        if (horarios_combinados[0] != '\0') {
            strcat(horarios_combinados, ";");
        }
        strcat(horarios_combinados, horario_atual->Horario);
        horario_atual = horario_atual->Proxima;
    }

    // Adiciona à oferta
    strcpy(oferta->disciplinas[oferta->quantidade].codigo, materia->Codigo);
    strcpy(oferta->disciplinas[oferta->quantidade].horarios, horarios_combinados);
    oferta->quantidade++;
}

void parseHorario(const char *horario_str, int *dia, int *periodo) {
    // Formato: "24T34" -> dia 2 (terça), periodo 3
    *dia = horario_str[0] - '0' - 1;     // 0-4 (Seg=0)
    *periodo = horario_str[2] - '0' - 1;  // 0-16
}

void preencherGrade(GradeHoraria *grade, OfertaDisciplinas *oferta) {
    for (int i = 0; i < oferta->quantidade; i++) {
        char *horario_token = strtok(oferta->disciplinas[i].horarios, ";");

        while (horario_token) {
            int dia, periodo;
            parseHorario(horario_token, &dia, &periodo);

            if (dia >= 0 && dia < DIAS_SEMANA && periodo >= 0 && periodo < HORARIOS_DIA) {
                strcpy(grade->grade[dia][periodo].codigo_disciplina,
                      oferta->disciplinas[i].codigo);
            }

            horario_token = strtok(NULL, ";");
        }
    }
}

void mostrarGrade(GradeHoraria *grade) {
    const char *dias[] = {"Seg\t", "Ter", "Qua\t", "Qui", "Sex\t"};
    int hora_atual = 7, minuto_atual = 30;

    printf("\n=== GRADE HORÁRIA ===\n");
    printf("Hora   ");
    for (int i = 0; i < DIAS_SEMANA; i++) printf("%-6s", dias[i]);
    printf("\n");

    for (int horario = 0; horario < HORARIOS_DIA; horario++) {
        printf("%02d:%02d  ", hora_atual, minuto_atual);

        for (int dia = 0; dia < DIAS_SEMANA; dia++) {
            printf("%-6s ", grade->grade[dia][horario].codigo_disciplina);
        }

        minuto_atual += 50;
        if (minuto_atual >= 60) {
            minuto_atual -= 60;
            hora_atual++;
        }
        printf("\n");
    }
}