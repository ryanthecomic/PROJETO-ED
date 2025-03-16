#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NOME 255
#define MAX_PREREQS 99
#define MAX_DISCIPLINAS 99

/*Nesse arquivo temos estruturas de TODAS as disciplinas obrigatórias do curso de CC da UFAL*/

typedef struct {
    int ID;
    char Nome[MAX_NOME];
    int CargaHorariaTotal;
    int PreReqs[MAX_PREREQS];
    int NumPreReqs;
    int NivelSemestre;
} Materia;

// Função para criar uma disciplina no "banco de dados"
Materia criarMateria(int id, const char* nome, int cargaHoraria, int nivelSemestre, int preReqs[], int numPreReqs) {
    Materia m;
    m.ID = id;
    strncpy(m.Nome, nome, MAX_NOME);
    m.CargaHorariaTotal = cargaHoraria;
    m.NivelSemestre = nivelSemestre;
    m.NumPreReqs = numPreReqs;
    for (int i = 0; i < numPreReqs; i++) {
        m.PreReqs[i] = preReqs[i];
    }
    return m;
}

int main() {
    Materia disciplinas[MAX_DISCIPLINAS];
    int numDisciplinas = 0;

    // 1° Semestre -------------------------------------------------------------------------------------------

    int preReqs1[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(359, "Programação 1", 72, 1, preReqs1, 0);

    int preReqs2[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(360, "Lógica para Computação", 72, 1, preReqs2, 0);

    int preReqs3[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(361, "Computação, Sociedade e Ética", 72, 1, preReqs3, 0);

    int preReqs4[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(362, "Matemática Discreta", 72, 1, preReqs4, 0);

    int preReqs5[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(363, "Cálculo Diferencial e Integral", 144, 1, preReqs5, 0);

    // 2° Semestre -------------------------------------------------------------------------------------------

    int preReqs6[] = {359}; // Pré-requisito: Programação 1
    disciplinas[numDisciplinas++] = criarMateria(364, "Estrutura de Dados", 72, 2, preReqs6, 1);

    int preReqs7[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(365, "Banco de Dados", 72, 2, preReqs7, 0);

    int preReqs8[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(366, "Organização e Arquitetura de Computadores", 72, 2, preReqs8, 0);

    int preReqs9[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(367, "Geometria Analítica", 72, 2, preReqs9, 0);

    // 3° Semestre -------------------------------------------------------------------------------------------

    int preReqs11[] = {366}; // Pré-requisito: Organização e Arquitetura de Computadores
    disciplinas[numDisciplinas++] = criarMateria(369, "Redes de Computadores", 72, 3, preReqs11, 1);

    int preReqs12[] = {362, 364}; // Pré-requisito: Matemática Discreta e Estrutura de Dados
    disciplinas[numDisciplinas++] = criarMateria(370, "Teoria dos Grafos", 72, 3, preReqs12, 1);

    int preReqs13[] = {363}; // Pré-requisito: Cálculo Diferencial e Integral
    disciplinas[numDisciplinas++] = criarMateria(371, "Probabilidade e Estatística", 72, 3, preReqs13, 1);

    int preReqs14[] = {367}; // Pré-requisito: Geometria Analítica
    disciplinas[numDisciplinas++] = criarMateria(372, "Álgebra Linear", 72, 3, preReqs14, 1);

    // 4° Semestre -------------------------------------------------------------------------------------------

    int preReqs16[] = {364, 365, 368}; // Pré-requisito: Estrutura de Dados, Banco de Dados e Redes de Computadores
    disciplinas[numDisciplinas++] = criarMateria(374, "Programação 2", 72, 4, preReqs16, 3);

    int preReqs17[] = {364, 365, 368}; // Pré-requisito: Estrutura de Dados, Banco de Dados e Redes de Computadores
    disciplinas[numDisciplinas++] = criarMateria(375, "Programação 3", 72, 4, preReqs17, 3);

    int preReqs18[] = {364, 369}; // Pré-requisito: Estrutura de Dados e Teoria dos Grafos
    disciplinas[numDisciplinas++] = criarMateria(376, "Projeto e Análise de Algoritmos", 72, 4, preReqs18, 2);

    int preReqs19[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(377, "Teoria da Computação", 72, 4, preReqs19, 1);

    // 5° Semestre -------------------------------------------------------------------------------------------

    int preReqs21[] = {366}; // Pré-requisito: Organização e Arquitetura de Computadores
    disciplinas[numDisciplinas++] = criarMateria(379, "Sistemas Operacionais", 72, 5, preReqs21, 1);

    int preReqs22[] = {364, 376}; // Pré-requisito: Estrutura de Dados e Teoria da Computação
    disciplinas[numDisciplinas++] = criarMateria(380, "Compiladores", 72, 5, preReqs22, 2);

    int preReqs23[] = {360, 364}; // Pré-requisito: Lógica para Computação e Estrutura de Dados
    disciplinas[numDisciplinas++] = criarMateria(381, "Inteligência Artificial", 72, 5, preReqs23, 2);

    int preReqs24[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(382, "Computação Gráfica", 72, 5, preReqs24, 1);

    // Extensão (Prática de Extensão em Ciência da Computação 2)
    int preReqs26[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(384, "Prática de Extensão em Ciência da Computação 2", 75, 5, preReqs26, 0);

    // 6° Semestre -------------------------------------------------------------------------------------------

    int preReqs27[] = {359, 360, 361, 362, 363, 364, 365, 366, 367, 369, 
        370, 371, 372, 374, 375, 376, 377, 379, 380, 381, 382}; 
        // Pré-requisito: Obrigatórias do  1° ao 5° período
    disciplinas[numDisciplinas++] = criarMateria(385, "Projeto e Desenvolvimento de Sistemas", 288, 6, preReqs27, 21);

    // Extensão (Prática de Extensão em Ciência da Computação 3)
    int preReqs29[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(387, "Prática de Extensão em Ciência da Computação 3", 75, 6, preReqs29, 0);

    // 7° Semestre -------------------------------------------------------------------------------------------

    int preReqs30[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(388, "Metodologia de Pesquisa e Trabalho Individual", 72, 7, preReqs30, 0);

    int preReqs31[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(389, "Noções de Direito", 72, 7, preReqs31, 0);

    // Extensão (Prática de Extensão em Ciência da Computação 4)
    int preReqs35[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(393, "Prática de Extensão em Ciência da Computação 4", 75, 7, preReqs35, 0);

    // 8° Semestre -------------------------------------------------------------------------------------------

    // Extensão (Prática de Extensão em Ciência da Computação 5)
    int preReqs41[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(399, "Prática de Extensão em Ciência da Computação 5", 75, 8, preReqs41, 0);

    //  -------------------------------------------------------------------------------------------

    // Acessando os dados:

    for (int i = 0; i < numDisciplinas; i++) {
        printf("ID: %d\n", disciplinas[i].ID);
        printf("Nome: %s\n", disciplinas[i].Nome);
        printf("Carga Horária Total: %d\n", disciplinas[i].CargaHorariaTotal);
        printf("Nivel/Semestre: %d\n", disciplinas[i].NivelSemestre);
        printf("Numero de Pre-requisitos: %d\n", disciplinas[i].NumPreReqs);
        if (disciplinas[i].NumPreReqs > 0) {
            printf("Pre-requisitos: ");
            for (int j = 0; j < disciplinas[i].NumPreReqs; j++) {
                printf("%d ", disciplinas[i].PreReqs[j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}