#include "shell.h"

void gerapassharmonia(const char *file)
{
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};
    int ficheiro = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR); // abre-> cria se nao existe-> trunca se existir vai para 0-> read and write

    if (ficheiro < 0)
    {
        perror("open file");
        exit(EXIT_FAILURE);
    }
    // gerador de semente a qual vai determinar a formacao de sequencia
    // semeentes iguais, sequencias iguais
    // time NULL retornara a«o tempo atual desde a criacao de UNIX 00:00:00 1970
    // este muda a cada segundo assegurando uma sequencia diferente
    /*SEGURANCA DE SEMENETE PARA O RAND, escolhas sempre diferentes*/
    srand(time(NULL));

    for (int i = 0; i < NUM_PASSWORDS; i++)
    {
        for (int j = 0; j < PASSWORD_LENGTH; j++)
        {
            char *nota = notas[rand() % 12];                  // escolhe de 0 a 11 uma do array de notas disponiveis
            write(ficheiro, &nota[rand() % strlen(nota)], 1); // sentro do array da nota escolhida, um do char sera escolhido para escrever o char, por um indice random entre 0 e o tamanho
        }
        write(ficheiro, "\n", 1);
    }

    close(ficheiro);
}

void gerapass12(const char *file, const char *password)
{
    // mapeamento
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};
    int ficheiro = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (ficheiro < 0)
    {
        perror("open file");
        exit(EXIT_FAILURE);
    }

    // para cada char da pass espeto la uma nota
    for (int i = 0; i < strlen(password); i++)
    {
        /*aqui, nota tera um vla entre 0 11, busco um val das notas, com o indice resultante de charecter ASCII % 12, que me dara um valor entre 0 , 11*/
        //ex: nota 'a', tem ASCII = 97, com o resto %12 = 1, logo mapeado a notas[1], mapeamento determinidstico
        char *nota = notas[password[i] % 12];

        write(ficheiro, nota, strlen(nota));
    }

    close(ficheiro);
}

void descodificar12(const char *file)
{
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};
    int ficheiro = open(file, O_RDONLY);

    if (ficheiro < 0)
    {
        perror("open file");
        exit(EXIT_FAILURE);
    }

    char nota[3]; // declaro array de nota, poderei por la cada nota mussical lida
    while (read(ficheiro, nota, 1) > 0)
    {                   // quanto conseguir ler 2 char do ficheiron para nota||read retorna o numero de chars lidos, verificacao ai
        nota[2] = '\0'; // apos ler 2 cgh ar adiciono o terminador nulo, este termina a string, pois a funcao strcmp espra terminadores nulos
        for (int i = 0; i < 12; i++)
        { // percorrer o mapeamento de notas
            if (strcmp(nota, notas[i]) == 0)
            { // comparo A nota codificada com o mapeamento, indice a indice, se igual foi descodificado
                // O I E A REFERENCIA DE DESCODEC, OIS SERA O INDICE

                /*declaro um char c, onde o indice somado com 'a', obtemos o elemento de ASCII correpondente, derivado o indice*/
                char c = i + 'a'; // decodifica a nota para um caractere
                write(STDOUT_FILENO, &c, 1);
                printf("\n");
                break;
            }
        }
    }

    close(ficheiro);
}