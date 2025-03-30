#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/materia_ppc.h"

MateriaPPC* criarMateriaPPC() {
    MateriaPPC* novaMateria = malloc(sizeof(MateriaPPC));

    if(novaMateria == NULL) {
        printf("Erro ao alocar memória para nova matéria.\n");
        return NULL;
    }
    novaMateria->Tipo = NULL;
    novaMateria->Requisitos = NULL;
    novaMateria->Proxima = NULL;

    return novaMateria;
}

void adicionarTipo(MateriaPPC* materia, const char* tipo) {
    TipoMateriaPPC* novoTipo = malloc(sizeof(TipoMateriaPPC));

    if(novoTipo == NULL) {
        printf("Erro ao alocar memória para novo tipo.\n");
        return;
    }

    strncpy(novoTipo->Tipo, tipo, MAX_TIPO);
    novoTipo->Tipo[strcspn(novoTipo->Tipo, "\n")] = '\0';
    novoTipo->Proxima = NULL;

    if(materia->Tipo == NULL) {
        materia->Tipo = novoTipo;
    } else {
        TipoMateriaPPC *atual = materia->Tipo;
        
        while(atual->Proxima != NULL) {
            atual = atual->Proxima;
        }
        atual->Proxima = novoTipo;
    }
}

void adicionarRequisito(MateriaPPC *materia, const char *codigo) {
    RequisitosMateriaPPC *novoRequisito = malloc(sizeof(RequisitosMateriaPPC));

    if(novoRequisito == NULL) {
        printf("Erro ao alocar memória para novo requisito.\n");
        return;
    }

    strncpy(novoRequisito->Codigo, codigo, MAX_CODIGO);
    novoRequisito->Codigo[strcspn(novoRequisito->Codigo, "\n")] = '\0';
    novoRequisito->Proxima = NULL;

    if(materia->Requisitos == NULL) {
        materia->Requisitos = novoRequisito;
    } else {
        RequisitosMateriaPPC *atual = materia->Requisitos;

        while(atual->Proxima != NULL) {
            atual = atual->Proxima;
        }
        atual->Proxima = novoRequisito;
    }
}

MateriaPPC* criarEstruturaPPC(){
    FILE *ppc = fopen("data/PPC2019.txt", "rt");

    if(ppc == NULL){
        printf("Erro ao abrir o arquivo do PPC\n");
        return NULL;
    }

    char linha[MAX_LINHA];

    MateriaPPC* listaMaterias = NULL;
    MateriaPPC* ultimaMateria = NULL;

    while(fgets(linha, MAX_LINHA, ppc)){
        linha[strcspn(linha, "\n")] = '\0';

        MateriaPPC* novaMateria = criarMateriaPPC();

        if(novaMateria == NULL){
            printf("Erro aqui.\n");
            continue;
        }

        char *save_1, *save_2, *save_3;

        char *token = strtok_r(linha, ",", &save_1); //codigo
        if(token){
            strncpy(novaMateria->Codigo, token, MAX_CODIGO);
            novaMateria->Codigo[strcspn(novaMateria->Codigo, "\n")] = '\0';
        }

        token = strtok_r(NULL, ",", &save_1); // nome
        if(token){
            strncpy(novaMateria->Nome, token, MAX_NOME);
            novaMateria->Nome[strcspn(novaMateria->Nome, "\n")] = '\0';
        }

        token = strtok_r(NULL, ",", &save_1); // nivel
        if(token){
            novaMateria->Periodo = atoi(token);
        }

        token = strtok_r(NULL, ",", &save_1); // cargahoraria
        if(token) {
            novaMateria->CargaHorariaTotal = atoi(token);
        }

        token = strtok_r(NULL, ",", &save_1);  // tipo
        if(token){
            if(strchr(token, ';')){
                char* tipo = strtok_r(token, ";", &save_2);
                while(tipo != NULL){
                    adicionarTipo(novaMateria, tipo);
                    tipo = strtok_r(NULL, ";", &save_2);
                }
            } else {
                adicionarTipo(novaMateria, token);
            }
        }

        token = strtok_r(NULL, ",", &save_1); // prereqs
        if(token){
            if(strchr(token, ';')){
                char* preRequisitos = strtok_r(token, ";", &save_3);
                while(preRequisitos != NULL){
                    adicionarRequisito(novaMateria, preRequisitos);
                    preRequisitos = strtok_r(NULL, ";", &save_3);
                }
            } else {
                adicionarRequisito(novaMateria, token);
            }
        }

        if(listaMaterias == NULL){
            listaMaterias = novaMateria;
        } else {
            ultimaMateria->Proxima = novaMateria;
        }
        ultimaMateria = novaMateria;
    }

    fclose(ppc);

    return listaMaterias;
}

void liberarMaterias(MateriaPPC* lista) {
    while(lista != NULL) {
        MateriaPPC *proxima = lista->Proxima;

        TipoMateriaPPC *tipoAtual = lista->Tipo;
        while(tipoAtual != NULL) {
            TipoMateriaPPC* proximoTipo = tipoAtual->Proxima;
            free(tipoAtual);
            tipoAtual = proximoTipo;
        }

        RequisitosMateriaPPC *requisitoAtual = lista->Requisitos;
        while(requisitoAtual != NULL) {
            RequisitosMateriaPPC *proximoRequisito = requisitoAtual->Proxima;
            free(requisitoAtual);
            requisitoAtual = proximoRequisito;
        }

        free(lista);
        lista = proxima;
    }
}

void imprimirListaMaterias(MateriaPPC* lista) {
    MateriaPPC* atual = lista;
    
    while (atual != NULL) {
        printf("\n--- Matéria ---\n");
        printf("Código: %s\n", atual->Codigo);
        printf("Nome: %s\n", atual->Nome);
        printf("Período: %d\n", atual->Periodo);
        printf("Carga Horária: %d horas\n", atual->CargaHorariaTotal);
        
        printf("Tipo(s): ");
        TipoMateriaPPC* tipoAtual = atual->Tipo;
        while (tipoAtual != NULL) {
            printf("%s", tipoAtual->Tipo);
            tipoAtual = tipoAtual->Proxima;
            if (tipoAtual != NULL) printf(" | ");
        }
        printf("\n");
        
        printf("Requisito(s): ");
        RequisitosMateriaPPC* reqAtual = atual->Requisitos;
        while (reqAtual != NULL) {
            printf("%s", reqAtual->Codigo);
            reqAtual = reqAtual->Proxima;
            if (reqAtual != NULL) printf(" | ");
        }
        printf("\n");
        
        atual = atual->Proxima;
    }
    
    printf("\n--- Fim da lista ---\n");
}