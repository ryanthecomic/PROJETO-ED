#ifndef GRADE_OFERTA_H
#define GRADE_OFERTA_H

#include "tipos.h"

typedef struct {
    char Grade[DIAS + 2][TURNOS + 1][AULAS + 1][MAX_CODIGO];
} GradeOferta;

// Protótipos das funções
void inicializarOferta(GradeOferta *oferta);
void criarEstruturaOferta(GradeOferta *grade);
void imprimirGradeOferta(GradeOferta *grade);

#endif