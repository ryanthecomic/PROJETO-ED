#include <stdio.h>
#include <stdlib.h>

#define DIAS 5       // Dias úteis (Seg-Sex)
#define TOTAL_BLOCOS 22  // Total de blocos por dia (aulas + intervalos)

typedef struct {
    int grade[DIAS][TOTAL_BLOCOS]; // Matriz de horários
} Horario;

// Horários fixos (alternando aulas de 50min e intervalos de 10min)
const char *horarios[TOTAL_BLOCOS] = {
    "07:30-08:20", // Aula 1 (50min)
    "08:20-08:30", // Intervalo (10min)
    "08:30-09:20", // Aula 2
    "09:20-09:30", // Intervalo
    "09:30-10:20", // Aula 3
    "10:20-10:30", // Intervalo
    "10:30-11:20", // Aula 4
    "11:20-11:30", // Intervalo
    "11:30-12:20", // Aula 5
    "12:20-12:30", // Intervalo
    "12:30-13:20", // Aula 6
    "13:20-13:30", // Intervalo
    "13:30-14:20", // Aula 7
    "14:20-14:30", // Intervalo
    "14:30-15:20", // Aula 8
    "15:20-15:30", // Intervalo
    "15:30-16:20", // Aula 9
    "16:20-16:30", // Intervalo
    "16:30-17:20", // Aula 10
    "17:20-17:30", // Intervalo
    "17:30-18:20", // Aula 11
    "18:20-18:30"  // Intervalo
};

void inicializarHorario(Horario *h) {
    for (int dia = 0; dia < DIAS; dia++) {
        for (int bloco = 0; bloco < TOTAL_BLOCOS; bloco++) {
            h->grade[dia][bloco] = 0; // 0 = vazio
        }
    }
}

void adicionarAula(Horario *h, int dia, int bloco, int id_disciplina) {
    if (dia >= 0 && dia < DIAS && bloco >= 0 && bloco < TOTAL_BLOCOS) {
        // Só permite adicionar em blocos de aula (ímpares)
        if (bloco % 2 == 0) {
            h->grade[dia][bloco] = id_disciplina;
        } else {
            printf("Erro: Não pode adicionar aula em bloco de intervalo\n");
        }
    } else {
        printf("Horário inválido! Dia %d, Bloco %d\n", dia, bloco);
    }
}

void imprimirHorario(Horario *h) {
    const char *nomes_dias[] = {"Segunda", "Terça", "Quarta", "Quinta", "Sexta"};

    printf("\n=== HORÁRIO ACADÊMICO ===\n");

    for (int dia = 0; dia < DIAS; dia++) {
        printf("\n%s:\n", nomes_dias[dia]);
        printf("----------------------------\n");

        for (int bloco = 0; bloco < TOTAL_BLOCOS; bloco++) {
            printf("%-11s: ", horarios[bloco]);

            if (bloco % 2 == 1) { // Blocos de intervalo
                printf("Intervalo\n");
            } else if (h->grade[dia][bloco] == 0) {
                printf("Livre\n");
            } else {
                printf("Aula %d\n", h->grade[dia][bloco]);
            }
        }
    }
}

int main() {
    Horario horario;
    inicializarHorario(&horario);

    // Exemplo de preenchimento
    adicionarAula(&horario, 0, 0, 101);  // Seg 07:30-08:20
    adicionarAula(&horario, 0, 4, 102);  // Seg 09:30-10:20
    adicionarAula(&horario, 2, 10, 103); // Qua 12:30-13:20
    adicionarAula(&horario, 4, 20, 104); // Sex 17:30-18:20

    imprimirHorario(&horario);

    return 0;
}