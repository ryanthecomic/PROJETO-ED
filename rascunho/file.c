#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NOMEDISCIPLINAS 100
#define MAX_PREREQS 31
#define MAX_DISCIPLINAS 63

typedef struct {
    int ID;
    char Nome[MAX_NOMEDISCIPLINAS];
    int CargaHorariaTotal;
    int PreReqs[MAX_PREREQS];
    int NumPreReqs;
    int NivelSemestre;
} Disciplina;

Disciplina criarMateria(int id, const char* nome, int cargaHoraria, int nivelSemestre, int preReqs[], int numPreReqs) {
    Disciplina m;
    m.ID = id;
    strncpy(m.Nome, nome, MAX_NOMEDISCIPLINAS);
    m.CargaHorariaTotal = cargaHoraria;
    m.NivelSemestre = nivelSemestre;
    m.NumPreReqs = numPreReqs;
    for (int i = 0; i < numPreReqs; i++) {
        m.PreReqs[i] = preReqs[i];
    }
    return m;
}

// Função para exibir as disciplinas
void printarDisciplinas(Disciplina disciplinas[], int numDisciplinas) {
    for (int i = 0; i < numDisciplinas; i++) {
        printf("ID: %d\n", disciplinas[i].ID);
        printf("Nome: %s\n", disciplinas[i].Nome);
        printf("Carga Horaria Total: %d\n", disciplinas[i].CargaHorariaTotal);
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
}

Disciplina criarBancoDeDisciplinas(Disciplina disciplinas[], int *numDisciplinas)
{
        // 1° Semestre

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

    //2° Semestre

    int preReqs6[] = {359}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(364, "Estrutura de Dados", 72, 2, preReqs6, 0);

    int preReqs7[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(365, "Banco de Dados", 72, 2, preReqs7, 0);

    int preReqs8[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(366, "Organização e Arquitetura de Computadores", 72, 2, preReqs8, 0);

    int preReqs9[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(367, "Geometria Analítica", 72, 2, preReqs9, 0);

    int preReqs10[] = {}; // Eletiva
    disciplinas[numDisciplinas++] = criarMateria(368, "Eletiva", 72, 2, preReqs10, 0);

    // 3° Semestre

    int preReqs11[] = {359}; // Pré-requisito: Organização e Arquitetura de Computadores
    disciplinas[numDisciplinas++] = criarMateria(369, "Redes de Computadores", 72, 3, preReqs11, 1);

    int preReqs12[] = {362, 364}; // Pré-requisito: Matemática Discreta
    disciplinas[numDisciplinas++] = criarMateria(370, "Teoria dos Grafos", 72, 3, preReqs12, 1);

    int preReqs13[] = {363}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(371, "Probabilidade e Estatística", 72, 3, preReqs13, 0);

    int preReqs14[] = {367}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(372, "Álgebra Linear", 72, 3, preReqs14, 0);

    int preReqs15[] = {}; // Eletiva
    disciplinas[numDisciplinas++] = criarMateria(373, "Eletiva", 72, 3, preReqs15, 0);

    // 4° Semestre
    int preReqs16[] = {364, 365, 368}; // Pré-requisito: Programação 1
    disciplinas[numDisciplinas++] = criarMateria(374, "Programação 2", 72, 4, preReqs16, 1);

    int preReqs17[] = {364, 365, 368}; // Pré-requisito: Programação 2
    disciplinas[numDisciplinas++] = criarMateria(375, "Programação 3", 72, 4, preReqs17, 1);

    int preReqs18[] = {364, 369}; // Pré-requisito: Estrutura de Dados
    disciplinas[numDisciplinas++] = criarMateria(376, "Projeto e Análise de Algoritmos", 72, 4, preReqs18, 1);

    int preReqs19[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(377, "Teoria da Computação", 72, 4, preReqs19, 1);

    int preReqs20[] = {}; // Eletiva
    disciplinas[numDisciplinas++] = criarMateria(378, "Eletiva", 72, 4, preReqs20, 0);

    // 5° Semestre
    int preReqs21[] = {366}; // Pré-requisito: Organização e Arquitetura de Computadores
    disciplinas[numDisciplinas++] = criarMateria(379, "Sistemas Operacionais", 72, 5, preReqs21, 1);

    int preReqs22[] = {364, 376}; // Pré-requisito: Programação 3
    disciplinas[numDisciplinas++] = criarMateria(380, "Compiladores", 72, 5, preReqs22, 1);

    int preReqs23[] = {360, 364}; // Pré-requisito: Teoria dos Grafos
    disciplinas[numDisciplinas++] = criarMateria(381, "Inteligência Artificial", 72, 5, preReqs23, 1);

    int preReqs24[] = {}; // Sem pré-requesitos
    disciplinas[numDisciplinas++] = criarMateria(382, "Computação Gráfica", 72, 5, preReqs24, 1);

    int preReqs25[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(383, "Eletiva", 72, 5, preReqs25, 0);

    // Extensão (Prática de Extensão em Ciência da Computação 2)
    int preReqs26[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(384, "Prática de Extensão em Ciência da Computação 2", 75, 5, preReqs26, 0);

    // 6° Semestre
    int preReqs27[] = {359, 360, 361, 362, 363, 364, 365, 366, 367, 369,
    370, 371, 372, 374, 375, 3376, 377, 379, 380, 381, 382}; // Pré-requisito: Obrigatórias do  1° ao 5° período
    disciplinas[numDisciplinas++] = criarMateria(385, "Projeto e Desenvolvimento de Sistemas", 288, 6, preReqs27, 1);

    int preReqs28[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(386, "Eletiva", 72, 6, preReqs28, 0);

    // Extensão (Prática de Extensão em Ciência da Computação 3)
    int preReqs29[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(387, "Prática de Extensão em Ciência da Computação 3", 75, 6, preReqs29, 0);

    // 7° Semestre
    int preReqs30[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(388, "Metodologia de Pesquisa e Trabalho Individual", 72, 7, preReqs30, 0);

    int preReqs31[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(389, "Noções de Direito", 72, 7, preReqs31, 0);

    int preReqs32[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(390, "Eletiva", 72, 7, preReqs32, 0);

    int preReqs33[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(391, "Eletiva", 72, 7, preReqs33, 0);

    int preReqs34[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(392, "Eletiva", 72, 7, preReqs34, 0);

    // Extensão (Prática de Extensão em Ciência da Computação 4)
    int preReqs35[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(393, "Prática de Extensão em Ciência da Computação 4", 75, 7, preReqs35, 0);

    // 8° Semestre
    int preReqs36[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(394, "Eletiva", 72, 8, preReqs36, 0);

    int preReqs37[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(395, "Eletiva", 72, 8, preReqs37, 0);

    int preReqs38[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(396, "Eletiva", 72, 8, preReqs38, 0);

    int preReqs39[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(397, "Eletiva", 72, 8, preReqs39, 0);

    int preReqs40[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(398, "Eletiva", 72, 8, preReqs40, 0);

    // Extensão (Prática de Extensão em Ciência da Computação 5)
    int preReqs41[] = {}; // Sem pré-requisitos
    disciplinas[numDisciplinas++] = criarMateria(399, "Prática de Extensão em Ciência da Computação 5", 75, 8, preReqs41, 0);

    return *disciplinas;
}

int runSigaa(Disciplina *disciplinas) {
    if (disciplinas == NULL)
    {
        return 0;
    }else
    {
        return 1;
    }

    // Template para ler os dados:
   /*for (int i = 0; i < numDisciplinas; i++) {
        printf("ID: %d\n", disciplinas[i].ID);
        printf("Nome: %s\n", disciplinas[i].Nome);
        printf("Carga Horaria Total: %d\n", disciplinas[i].CargaHorariaTotal);
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
    }*/

    return 0;
}
