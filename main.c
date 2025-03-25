#include "entrada.h"
#include "sigaa.h"

int main(void) {
  Disciplina disciplinas[MAX_DISCIPLINAS];
  int numDisciplinas = 0;

  // Criar o banco de disciplinas
  numDisciplinas = criarBancoDeDisciplinas(disciplinas, numDisciplinas);

  printf("Total de disciplinas criadas: %d\n", numDisciplinas);

  //printarDisciplinas(disciplinas, numDisciplinas);

  //Executar o SIGAA

  if (runSigaa(disciplinas, numDisciplinas)) {
    printf("Banco de dados de disciplinas foi criado.\n");
  } else {
    printf("Ocorreu um erro na biblioteca <sigaa.h>\n");
  }

  Aluno aluno;
  abrirArquivo("entrada.txt", &aluno);

  int opcao = -1;

  while (opcao != 0)
  {
    printf("\nMenu do Sigaa:\n");
    printf("1 - Mostrar Informacoes do Aluno\n");
    printf("2 - Mostrar Disciplinas\n");
    printf("3 - Mostrar Disciplina Especifica\n");
    printf("0 - Sair\n");
    printf("\nEscolha uma opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 2:
      printarDisciplinas(disciplinas, numDisciplinas);
      break;
    case 1:
      printLista(&aluno);
      break;
    case 3:
      int qual;
      printf("\nDigite o código da disciplina: ");
      scanf("%d", &qual);
      printarDisciplinaEspecifica(disciplinas, numDisciplinas, qual);
      break;
    case 0:
      printf("Saindo...\n");
      //free(&aluno);
      break;
    default:
      printf("Opcao invalida! Tente novamente.\n");
      break;
    }
  }

  return 0;

}