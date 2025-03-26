#include "entrada.h"
#include "sigaa.h"

int main(void) {
  Disciplina disciplinas[MAX_DISCIPLINAS];
  int numDisciplinas = 0;

  numDisciplinas = criarBancoDeDisciplinas(disciplinas, numDisciplinas);   // Criar o banco de disciplinas

  printf("Total de disciplinas criadas: %d\n", numDisciplinas); //DEBUG

  //Executar o RUNSIGAA

  if (runSigaa(disciplinas, numDisciplinas)) {
    printf("Banco de dados de disciplinas foi criado.\n");
  } else {
    printf("Ocorreu um erro na biblioteca <sigaa.h>\n");
  }

  Aluno aluno; // inicializar o aluno
  abrirArquivo("entrada.txt", &aluno); // abrir o arquivo do aluno para ler

  Horario horario; //inicializar o horario do aluno
  inicializarHorario(&horario); // inicializar o horario com valores padrões

// INTERFACE

  int opcao = -1;

  while (opcao != 0)
  {
    printf("\nMenu do Sigaa:\n");
    printf("1 - Mostrar Informacoes do Aluno\n");
    printf("2 - Mostrar Disciplinas\n");
    printf("3 - Mostrar Disciplina Especifica\n");
    printf("4 - Mostrar Horario do Aluno\n");
    printf("5 - Debug: Adicione a disciplina de Programacao a grade\n");
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
    case 4:
      mostrarHorario(horario);
    case 5: // 359 é o ID de programação
      adicionarAoHorario(&horario, 359, 5, 11); // Sexta (5), horário 11 (15:20)
      adicionarAoHorario(&horario, 359, 5, 12); // Sexta (5), horário 12 (16:10)
      adicionarAoHorario(&horario, 359, 5, 14); // Sexta (5), horário 14 (17:10)
      adicionarAoHorario(&horario, 359, 5, 15); // Sexta (5), horário 15 (18:00)
    /*case 6:
      adicionarDisciplinaAoHorario(&horario, disciplinas[1]);*/
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