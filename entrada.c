#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NOME 255

// Estrutura de uma disciplina a ser armazenada
typedef struct DisciplinasHistorico{
    int ID;
    double Nota;
    struct DisciplinasHistorico* Proximo;
} DisciplinaHistorico;

 // Estrutura do histórico de um aluno
typedef struct {
    char Nome[MAX_NOME];
    DisciplinaHistorico* Aprovadas;
    int QtdAprovadas;
    int Semestre;
}Aluno;

// Função que preenche a estrutura de histórico com base na entrada .txt, todo: comentar a função por completo
void abrirArquivo(const char* nomeArquivo, Aluno* aluno){
    FILE* arquivo;

    arquivo = fopen(nomeArquivo, "rt");

    if(arquivo == NULL){
        printf("Erro ao criar arquivo!\n");
        return;
    }

    fgets(aluno->Nome, sizeof(aluno->Nome), arquivo);
    aluno->Nome[strcspn(aluno->Nome, "\n")] = '\0';
    
    aluno->QtdAprovadas = 0;
    aluno->Aprovadas = NULL;

    char linha[100];
    fgets(linha, sizeof(linha), arquivo);
    linha[strcspn(linha, "\n")] = '\0';

    char* token = strtok(linha,",");

    while(token != NULL){
        int id;
        double nota;
        sscanf(token, "%d=%lf", &id, &nota);

        if(nota >= 7.0){
            DisciplinaHistorico* disciplina = malloc(sizeof(DisciplinaHistorico));
            disciplina->ID = id;
            disciplina->Nota = nota;
            disciplina->Proximo = NULL;

            if(aluno->Aprovadas == NULL){
                aluno->Aprovadas = disciplina;
            } else {
                DisciplinaHistorico* aux = aluno->Aprovadas;

                while(aux->Proximo != NULL){
                    aux = aux->Proximo;
                }
                aux->Proximo = disciplina;
            }
            aluno->QtdAprovadas++;
        }
        token = strtok(NULL, ",");
    }
// todo: ler o período do estudante.
    fclose(arquivo);

    return;
}

void printLista(Aluno* aluno){
    printf("Aluno: %s\n", aluno->Nome);
    printf("Disciplinas aprovadas:\n");

    DisciplinaHistorico* aux = aluno->Aprovadas;

    while(aux != NULL){
        printf("ID: %d, Nota: %.2lf\n", aux->ID, aux->Nota);
        aux = aux->Proximo;
    }

    return;
}
int main(){
    Aluno aluno;
    abrirArquivo("entrada.txt", &aluno);
    printLista(&aluno);
    return 0;
}