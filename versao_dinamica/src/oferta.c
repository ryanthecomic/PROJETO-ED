#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "../include/oferta.h"

// Tabela de pesos das letras
int peso_letra(char letra) {
    switch(tolower(letra)) {
    case 'q': return 1; case 'w': return 6; case 'e': return 7;
    case 'r': return 6; case 't': return 5; case 'y': return 2;
    case 'u': return 3; case 'i': return 8; case 'o': return 9;
    case 'p': return 4; case 'a': return 2; case 's': return 5;
    case 'd': return 8; case 'f': return 7; case 'g': return 4;
    case 'h': return 1; case 'j': return 4; case 'k': return 7;
    case 'l': return 8; case 'z': return 3; case 'x': return 4;
    case 'c': return 9; case 'v': return 8; case 'b': return 3;
    case 'n': return 2; case 'm': return 5;
        // Caracteres acentuados (infelizmente usando valores ASCII estendidos)
    case 0xE1: return 3; // á
    case 0xE3: return 4; // ã
    case 0xE7: return 5; // ç
    case 0xE9: return 2; // é
    case 0xED: return 3; // í
    case 0xF3: return 6; // ó
    case 0xF5: return 7; // õ
    case 0xF4: return 6; // ô
    case 0xE2: return 1; // â
    case 0xEA: return 2; // ê
    default: return 0;
    }
}

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
            strcpy(grade->grade[dia][horario].codigo_disciplina, "---");
        }
    }
}

void preencherGrade(GradeHoraria *grade, OfertaDisciplinas *oferta) {
    if (!grade || !oferta) return;

    // Limpa a grade primeiro
    inicializarGrade(grade);

    for (int i = 0; i < oferta->quantidade; i++) {
        char horarios_copia[MAX_HORARIO];
        strcpy(horarios_copia, oferta->disciplinas[i].horarios);

        char *token = strtok(horarios_copia, ";");
        while (token != NULL) {
            int dia, periodo;
            parseHorario(token, &dia, &periodo);

            // Verifica limites
            if (dia >= 0 && dia < DIAS_SEMANA && periodo >= 0 && periodo < HORARIOS_DIA) {
                // Se já tem disciplina, marca como conflito
                if (strcmp(grade->grade[dia][periodo].codigo_disciplina, "---") != 0) {
                    strcat(grade->grade[dia][periodo].codigo_disciplina, "+");
                } else {
                    strcpy(grade->grade[dia][periodo].codigo_disciplina,
                          oferta->disciplinas[i].codigo);
                }
            }
            token = strtok(NULL, ";");
        }
    }
}

void mostrarGrade(GradeHoraria *grade) {
    if (!grade) return;

    const char *dias[] = {"Seg", "Ter", "Qua", "Qui", "Sex"};
    int hora_atual = 7, minuto_atual = 30;

    printf("\n=== GRADE HORÁRIA ===\n");
    printf("Hora   ");
    for (int i = 0; i < DIAS_SEMANA; i++) printf("%-6s", dias[i]);
    printf("\n");

    for (int horario = 0; horario < HORARIOS_DIA; horario++) {
        printf("%02d:%02d  ", hora_atual, minuto_atual);

        for (int dia = 0; dia < DIAS_SEMANA; dia++) {
            printf("%-6s", grade->grade[dia][horario].codigo_disciplina);
        }

        minuto_atual += 50;
        if (minuto_atual >= 60) {
            minuto_atual -= 60;
            hora_atual++;
        }
        printf("\n");
    }
}

//todo: adiciona a disciplina para a oferta
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
    oferta->disciplinas[oferta->quantidade].periodo = materia->Periodo;
    oferta->disciplinas[oferta->quantidade].carga_horaria = materia->CargaHorariaTotal;
    oferta->quantidade++;
}

//todo: calcula o peso baseado no nome
int calcularPesoNome(const char *nome) {
    int peso = 0;
    for(int i = 0; nome[i] != '\0'; i++) {
        peso += peso_letra(nome[i]);
    }
    return peso;
}

//todo: calcula a carga horaria total da oferta
int calcularCargaHorariaTotal(OfertaDisciplinas *oferta) {
    int carga_total = 0;
    for(int i = 0; i < oferta->quantidade; i++) {
        carga_total += oferta->disciplinas[i].carga_horaria;
    }
    return carga_total;
}

//todo: converte a string do horario em um valor usável para o sistema
void parseHorario(const char *horario_str, int *dia, int *periodo) {
    //if (!horario_str || strlen(horario_str) < 2) return;

    // Dia da semana (1-5 -> 0-4)
    *dia = horario_str[0] - '1';
    if (*dia < 0 || *dia > 4) *dia = 0; // padrão para segunda

    // Turno (M, T, N)
    char turno = toupper(horario_str[1]); // pega o segundo caractere (M/T/N) e converte para maiúsculo

    // Período dentro do turno
    int periodo_turno = 0;
    if (strlen(horario_str) > 2) {
        periodo_turno = horario_str[2] - '1';
        if (periodo_turno < 0) periodo_turno = 0;
    }

    // Mapeia para o período global
    switch (turno) {
        case 'M': // Manhã (7:30-12:30)
            *periodo = periodo_turno; // 0-5
            break;
        case 'T': // Tarde (13:20-18:20)
            *periodo = 6 + periodo_turno; // 6-11
            break;
        case 'N': // Noite (19:10-22:00)
            *periodo = 12 + periodo_turno; // 12-16
            break;
        default:
            *periodo = 0; // Padrão para primeiro período da manhã
    }
}

int alunoJaCursou(const char *codigo, Aluno *aluno) {
    MateriaCursada *cursada = aluno->Materias;
    while(cursada != NULL) {
        if(strcmp(cursada->Codigo, codigo) == 0 && cursada->Nota >= 7.0) {
            return 1; // Aluno já cursou e aprovou
        }
        cursada = cursada->Proxima;
    }
    return 0; // Aluno não cursou ou não aprovou
}

int verificarPreRequisitos(const char *codigo, Aluno *aluno, MateriaPPC *ppc) {
    // Primeiro verifica se o aluno já cursou esta disciplina
    if(alunoJaCursou(codigo, aluno)) {
        return 0; // Não pode cursar novamente
    }

    // Encontra a matéria no PPC
    MateriaPPC *materia = NULL;
    for(MateriaPPC *m = ppc; m != NULL; m = m->Proxima) {
        if(strcmp(m->Codigo, codigo) == 0) {
            materia = m;
            break;
        }
    }
    if(!materia) return 0;

    // Verifica se tem requisitos
    if(!materia->Requisitos || strcmp(materia->Requisitos->Codigo, "Nenhum") == 0) {
        return 1; // Não tem pré-requisitos
    }

    // Verifica se o aluno cumpriu todos os requisitos
    RequisitosMateriaPPC *req = materia->Requisitos;
    while(req != NULL) {
        int cumpriu = 0;
        MateriaCursada *cursada = aluno->Materias;
        while(cursada != NULL) {
            if(strcmp(cursada->Codigo, req->Codigo) == 0 && cursada->Nota >= 7.0) {
                cumpriu = 1;
                break;
            }
            cursada = cursada->Proxima;
        }
        if(!cumpriu) return 0;
        req = req->Proxima;
    }
    return 1;
}

int verificarChoqueHorario(GradeHoraria *grade, const char *horarios) {
    // Fazemos uma cópia para não modificar a string original
    char horarios_copia[MAX_HORARIO];
    strcpy(horarios_copia, horarios);

    char *token = strtok(horarios_copia, ";");
    while(token != NULL) {
        int dia, periodo;
        parseHorario(token, &dia, &periodo);

        if(dia >= 0 && dia < DIAS_SEMANA && periodo >= 0 && periodo < HORARIOS_DIA) {
            if(strcmp(grade->grade[dia][periodo].codigo_disciplina, "---") != 0) {
                return 1; // Choque detectado
            }
        }
        token = strtok(NULL, ";");
    }
    return 0;
}

// todo: função de aconselhamento
void gerarOfertaPersonalizada(const char *nome_completo, MateriaPPC *ppc, Aluno *aluno, OfertaDisciplinas *oferta) {
    // Separa os nomes
    char nome_copia[100];
    strcpy(nome_copia, nome_completo);

    char nomes[10][50];
    int num_nomes = 0;
    char *token = strtok(nome_copia, " ");

    while(token != NULL && num_nomes < 10) {
        strcpy(nomes[num_nomes++], token);
        token = strtok(NULL, " ");
    }

    // Calcula parâmetros baseados no nome
    int peso_primeiro = calcularPesoNome(nomes[0]);
    int max_disciplinas = (peso_primeiro % 3 == 0) ? 10 : (peso_primeiro % 3 == 1) ? 8 : 6;

    printf("\n");
    printf("- O máximo de discplinas que o aluno planeja para o semestre é de %d\n", max_disciplinas);

    int peso_segundo = (num_nomes > 1) ? calcularPesoNome(nomes[1]) : calcularPesoNome(nomes[0]);
    int estrategia_conclusao = peso_segundo % 3;

    switch(estrategia_conclusao) {
      case 0:
        printf("- O aluno deseja concluir o curso no menor tempo possível\n");
        break;
      case 1:
        printf("- O aluno deseja concluir o curso no maior tempo possível\n");
        break;
      case 2:
        printf("- O aluno deseja concluir o curso no tempo médio possível\n");
        break;
    }

    int peso_terceiro = (num_nomes > 2) ? calcularPesoNome(nomes[2]) : calcularPesoNome(nomes[0]);
    int estrategia_enfase = peso_terceiro % 3;
/*
        switch(estrategia_enfase) {
      case 0:
        printf("- O aluno deseja a ênfase desejada pelo aluno\n");
        break;
      case 1:
        printf("- O aluno deseja a ênfase que diminui o tempo de conclusão do curso pelo aluno\n");
        break;
      case 2:
        printf("- O aluno não deseja nenhuma ênfase\n");
        break;
    }*/

    int peso_quarto = (num_nomes > 3) ? calcularPesoNome(nomes[3]) : calcularPesoNome(nomes[0]);
    int estrategia_distribuicao = peso_quarto % 3;

    switch(estrategia_distribuicao) {
      case 0:
      	printf("- O aluno deseja que as disciplinas deve ocupar o menos números de dias possiveis(Não funcional)\n");
      	break;
      case 1:
      	printf("- O aluno deseja que as disciplinas devem pertencer a um mesmo turno (Não funcional)\n");
      	break;
      case 2:
      	printf("- O aluno nao deve extrapola o limite de 3 disciplinas no máximo por dia, mas deve ir todos os dias a UFAL\n");
      	break;
      }

      printf("\n");

    // todo: Gera oferta personalizada
    GradeHoraria grade_temp;
    inicializarGrade(&grade_temp);

    int carga_total = 0;
    int disciplinas_adicionadas = 0;

    // Ordena as matérias por período (dependendo da estratégia de conclusão)
    MateriaPPC *ordenadas[100];
    int count = 0;
    for(MateriaPPC *m = ppc; m != NULL; m = m->Proxima) {
        ordenadas[count++] = m;
    }

    // todo: ordena as disciplinas no bubble sort mesmo, de acordo com o periodo, se quiser acabar cedo, faz na ordem
    // padrão, se não, faz as disciplinas mais extensas primeiro
    for(int i = 0; i < count-1; i++) {
        for(int j = i+1; j < count; j++) {
            if((estrategia_conclusao == 0 && ordenadas[i]->CargaHorariaTotal > ordenadas[j]->CargaHorariaTotal) ||
               (estrategia_conclusao == 1 && ordenadas[i]->CargaHorariaTotal < ordenadas[j]->CargaHorariaTotal)) {
                MateriaPPC *temp = ordenadas[i];
                ordenadas[i] = ordenadas[j];
                ordenadas[j] = temp;
            }
        }
    }

    // Adiciona disciplinas a oferta seguindo as regras
    for(int i = 0; i < count && disciplinas_adicionadas < max_disciplinas; i++) {
        MateriaPPC *m = ordenadas[i];

        // Verifica se aluno já cursou esta disciplina
   		if(alunoJaCursou(m->Codigo, aluno)) continue;

        // Verifica pré-requisitos
        if(!verificarPreRequisitos(m->Codigo, aluno, ppc)) continue;

        // Verifica choque de horário
        if(verificarChoqueHorario(&grade_temp, m->Horarios->Horario)) continue;

        // Verifica carga horária
        if(carga_total + m->CargaHorariaTotal > MAX_CARGA) continue;

     	// todo: se o peso 4 requerer que o aluno tenha disciplinas todos os dias
    	if(estrategia_distribuicao == 2){

   		int dias_com_aula = 0;
		bool dias_preenchidos[DIAS_SEMANA] = {false};

		for (int i = 0; i < oferta->quantidade; i++) {
    	char horarios_copia[MAX_HORARIO];
    	strcpy(horarios_copia, oferta->disciplinas[i].horarios);

    	char *token = strtok(horarios_copia, ";");
    	while (token != NULL) {
        	int dia, periodo;
        	parseHorario(token, &dia, &periodo);
        	if (dia >= 0 && dia < DIAS_SEMANA) {
            dias_preenchidos[dia] = true;
        }
        	token = strtok(NULL, ";");
   		}
	}

	// Adiciona disciplinas extras para dias vazios, se necessário
	for (int dia = 0; dia < DIAS_SEMANA && disciplinas_adicionadas < max_disciplinas; dia++) {
    if (!dias_preenchidos[dia]) {
        // Busca uma disciplina que tenha aula neste dia específico
        for (int i = 0; i < count && disciplinas_adicionadas < max_disciplinas; i++) {
            MateriaPPC *m = ordenadas[i];

            if (alunoJaCursou(m->Codigo, aluno)) continue;
            if (!verificarPreRequisitos(m->Codigo, aluno, ppc)) continue;

            // Verifica se a disciplina tem aula no dia vazio
            bool tem_aula_no_dia = false;
            HorariosMateriaPPC *horario = m->Horarios;
            while (horario != NULL) {
                int d, p;
                parseHorario(horario->Horario, &d, &p);
                if (d == dia) {
                    tem_aula_no_dia = true;
                    break;
                }
                horario = horario->Proxima;
            }

            if (tem_aula_no_dia && !verificarChoqueHorario(&grade_temp, m->Horarios->Horario)) {
                DisciplinaOfertada nova;
                strcpy(nova.codigo, m->Codigo);
                strcpy(nova.horarios, m->Horarios->Horario);
                nova.periodo = m->Periodo;
                nova.carga_horaria = m->CargaHorariaTotal;

                oferta->disciplinas[oferta->quantidade++] = nova;
                disciplinas_adicionadas++;
                preencherGrade(&grade_temp, oferta);
                break;
            	}
        	}
    	}
	}
	// PESO 4
}

        // Adiciona à oferta
        DisciplinaOfertada nova;
        strcpy(nova.codigo, m->Codigo);
        strcpy(nova.horarios, m->Horarios->Horario);
        nova.periodo = m->Periodo;
        nova.carga_horaria = m->CargaHorariaTotal;

        oferta->disciplinas[oferta->quantidade++] = nova;
        carga_total += m->CargaHorariaTotal;
        disciplinas_adicionadas++;

        // Atualiza grade temporária
        preencherGrade(&grade_temp, oferta);
    }

    // Garante pelo menos 1 disciplina, se um aluno n tiver matriculado em nenhuma disciplina, corre risco de jubilar
    if(oferta->quantidade == 0 && count > 0) {
        // Adiciona a primeira disciplina possível
        for(int i = 0; i < count; i++) {
            MateriaPPC *m = ordenadas[i];
            if(verificarPreRequisitos(m->Codigo, aluno, ppc)) {
                DisciplinaOfertada nova;
                strcpy(nova.codigo, m->Codigo);
                strcpy(nova.horarios, m->Horarios->Horario);
                nova.periodo = m->Periodo;
                nova.carga_horaria = m->CargaHorariaTotal;

                oferta->disciplinas[oferta->quantidade++] = nova;
                break;
            }
        }
    }

}