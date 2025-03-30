#ifndef MATERIA_PPC_H
#define MATERIA_PPC_H

#include "tipos.h"

typedef struct TipoMateriaPPC {
    char Tipo[MAX_TIPO];
    struct TipoMateriaPPC *Proxima;
} TipoMateriaPPC;

typedef struct RequisitosMateriaPPC {
    char Codigo[MAX_CODIGO];
    struct RequisitosMateriaPPC *Proxima;
} RequisitosMateriaPPC;

typedef struct MateriaPPC {
    char Codigo[MAX_CODIGO];
    char Nome[MAX_NOME];
    int Periodo;
    int CargaHorariaTotal;
    TipoMateriaPPC *Tipo;
    RequisitosMateriaPPC *Requisitos;
    struct MateriaPPC *Proxima;
} MateriaPPC;

// Protótipos das funções
MateriaPPC* criarMateriaPPC();
void adicionarTipo(MateriaPPC* materia, const char* tipo);
void adicionarRequisito(MateriaPPC *materia, const char *codigo);
MateriaPPC* criarEstruturaPPC();
void liberarMaterias(MateriaPPC* lista);
void imprimirListaMaterias(MateriaPPC* lista);

#endif