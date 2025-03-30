#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/grade_oferta.h"

void inicializarOferta(GradeOferta *oferta) {
    for(int dia = 2; dia <= 6; dia++) {
        for(int turno = 1; turno <= 3; turno++) {
            for(int aula = 0; aula <= 6; aula++) {
                oferta->Grade[dia][turno][aula][0] = '\0';
            }
        }
    }
}

void criarEstruturaOferta(GradeOferta *grade){
    FILE *oferta = fopen("data/OFERTA.txt", "rt");

    if(oferta == NULL){
        printf("Erro ao abrir arquivo de oferta.\n");
        return;
    }

    char linha[MAX_LINHA];

    while(fgets(linha, MAX_LINHA, oferta)){
        linha[strcspn(linha, "\n")] = '\0';

        char *save_1, *save_2;

        char *codigo = strtok_r(linha, ",", &save_1);
        printf("%s\n", codigo);

        char *horarios = strtok_r(NULL, ",", &save_1);
        if (horarios){
            if(strchr(horarios, ';')){
                char *horario = strtok_r(horarios, ";", &save_2);
                printf("%s\n", horario);
                while(horario != NULL){
                    int i = 0;
                    int auxDias[2] = {0};
                    int numDias = 0;
                    while(isdigit(horario[i])){
                        auxDias[numDias] = horario[i] - '0';
                        numDias++;
                        i++;
                    }

                    int turnoAtual = 0;

                    if(horario[i] == 'M'){
                        turnoAtual = 1;
                    } else if(horario[i] == 'T'){
                        turnoAtual = 2;
                    } else if(horario[i] == 'N'){
                        turnoAtual = 3;
                    }

                    i++;
                    
                    int auxAulas[6] = {0};
                    int numAulas = 0;
                    while(isdigit(horario[i])){
                        auxAulas[numAulas] = horario[i] - '0';
                        numAulas++;
                        i++;
                    }

                    for(int dia = 0; dia < numDias; dia++){
                        for(int aula = 0; aula < numAulas; aula++){
                            printf("Atribuindo código %s em [%d][%d][%d]\n", codigo, auxDias[dia], turnoAtual, auxAulas[aula]);
                            strncpy(grade->Grade[auxDias[dia]][turnoAtual][auxAulas[aula]], codigo, MAX_CODIGO);
                            printf("Verificando: %s\n", grade->Grade[auxDias[dia]][turnoAtual][auxAulas[aula]]);
                        }
                    }
                    horario = strtok_r(NULL, ";", &save_2);
                }
            } else {
                printf("%s\n", horarios);
                while(horarios != NULL){
                    int i = 0;
                    int auxDias[2] = {0};
                    int numDias = 0;
                    while(isdigit(horarios[i])){
                        printf("%c\n", horarios[i]);
                        auxDias[numDias] = horarios[i] - '0';
                        numDias++;
                        i++;
                    }

                    int turno = 0;

                    if(horarios[i] == 'M'){
                        turno = 1;
                    } else if(horarios[i] == 'T'){
                        turno = 2;
                    } else if(horarios[i] == 'N'){
                        turno = 3;
                    }

                    printf("%c\n", horarios[i]);

                    i++;
                    
                    int auxAulas[6] = {0};
                    int numAulas = 0;
                    while(isdigit(horarios[i])){
                        printf("%c\n", horarios[i]);
                        auxAulas[numAulas] = horarios[i] - '0';
                        numAulas++;
                        i++;
                    }

                    for(int dia = 0; dia < numDias; dia++){
                        for(int aula = 0; aula < numAulas; aula++){
                            printf("Atribuindo código %s em [%d][%d][%d]\n", codigo, auxDias[dia], turno, auxAulas[aula]);
                            strncpy(grade->Grade[auxDias[dia]][turno][auxAulas[aula]], codigo, MAX_CODIGO);
                            printf("Verificando: %s\n", grade->Grade[auxDias[dia]][turno][auxAulas[aula]]);
                        }
                    }

                    horarios = strtok_r(NULL, ",", &save_1);
                }    
            }
        }
    }
        
    fclose(oferta);
    return;
}

void imprimirGradeOferta(GradeOferta *grade) {
    const char *nomesDias[] = {"", "", "SEGUNDA", "TERÇA", "QUARTA", "QUINTA", "SEXTA"};
    const char *nomesTurnos[] = {"", "MANHÃ", "TARDE", "NOITE"};

    printf("\n=== GRADE DE OFERTA ===\n");

    for (int dia = 2; dia <= 6; dia++) {
        printf("\n--- %s ---\n", nomesDias[dia]);
        
        for (int turno = 1; turno <= 3; turno++) {
            printf("\n%s:\n", nomesTurnos[turno]);
            
            for (int aula = 1; aula <= 6; aula++) {
                printf("  Aula %d: %s\n", aula, grade->Grade[dia][turno][aula]);
            }
        }
    }
    printf("\n=== FIM DA GRADE ===\n");
}