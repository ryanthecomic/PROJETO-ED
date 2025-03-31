#ifndef OFERTA_H
#define OFERTA_H

#include "tipos.h"
#include "materia_ppc.h"

#define DIAS_SEMANA 5   // Segunda a Sexta
#define HORARIOS_DIA 17 // 17 horários ativos

typedef struct {
    char codigo[MAX_CODIGO];
    char horarios[MAX_HORARIO]; // String com todos os horários (ex: "24T34;35T12")
} DisciplinaOfertada;

typedef struct {
    DisciplinaOfertada *disciplinas;
    int quantidade;
    int capacidade;
} OfertaDisciplinas;

typedef struct {
    char codigo_disciplina[MAX_CODIGO]; // "---" para vazio
} SlotGrade;

typedef struct {
    SlotGrade grade[DIAS_SEMANA][HORARIOS_DIA];
} GradeHoraria;

// Funções básicas
OfertaDisciplinas* criarOfertaDisciplinas(int capacidade);
void liberarOfertaDisciplinas(OfertaDisciplinas *oferta);

// Trabalha com horários
void inicializarGrade(GradeHoraria *grade);
void preencherGrade(GradeHoraria *grade, OfertaDisciplinas *oferta);
void mostrarGrade(GradeHoraria *grade);
void adicionarDisciplinaOfertada(OfertaDisciplinas *oferta, MateriaPPC *materia);

#endif