#ifndef OFERTA_H
#define OFERTA_H

#include "tipos.h"
#include "materia_ppc.h"
#include "aluno.h"
#include "oferta.h"

#define DIAS_SEMANA 5
#define HORARIOS_DIA 17
#define MAX_CARGA 570
#define MIN_CARGA 240

typedef struct {
    char codigo[MAX_CODIGO];
    char horarios[MAX_HORARIO];
    int periodo;
    int carga_horaria;
} DisciplinaOfertada;

typedef struct {
    DisciplinaOfertada *disciplinas;
    int quantidade;
    int capacidade;
} OfertaDisciplinas;

typedef struct {
    char codigo_disciplina[MAX_CODIGO];
} SlotGrade;

typedef struct {
    SlotGrade grade[DIAS_SEMANA][HORARIOS_DIA];
} GradeHoraria;

// Funções básicas
OfertaDisciplinas* criarOfertaDisciplinas(int capacidade);
void liberarOfertaDisciplinas(OfertaDisciplinas *oferta);
void inicializarGrade(GradeHoraria *grade);
void preencherGrade(GradeHoraria *grade, OfertaDisciplinas *oferta);
void mostrarGrade(GradeHoraria *grade);
int calcularCargaHorariaTotal(OfertaDisciplinas *oferta);

// Funções de manipulação
void adicionarDisciplinaOfertada(OfertaDisciplinas *oferta, MateriaPPC *materia);
void parseHorario(const char *horario_str, int *dia, int *periodo);

// Funções de processamento
void gerarOfertaPersonalizada(const char *nome_completo, MateriaPPC *ppc, Aluno *aluno, OfertaDisciplinas *oferta);
int verificarPreRequisitos(const char *codigo, Aluno *aluno, MateriaPPC *ppc);
int verificarChoqueHorario(GradeHoraria *grade, const char *horarios);
int alunoJaCursou(const char *codigo, Aluno *aluno);

#endif