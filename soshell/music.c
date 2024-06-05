#include "shell.h"
//GERAPASSHARMONIA 1 FILE RANDOM NO DECODEC
// A função gerapassharmonia recebe um nome de arquivo como argumento
/**
 * @brief Gera sequências de notas musicais aleatórias e as grava em um arquivo.
 * 
 * @param file O nome do arquivo onde as sequências de notas serão gravadas.
 * 
 * Esta função gera NUM_PASSWORDS sequências de notas musicais, cada uma com PASSWORD_LENGTH notas.
 * As notas são escolhidas aleatoriamente de um array de notas musicais.
 * Cada sequência de notas é gravada em uma linha separada no arquivo.
 * Se o arquivo não existir, ele será criado. Se o arquivo já existir, ele será truncado.
 * 
 * @return void
 */

void gerapassharmonia(const char *file)
{
    // Declara um array de strings representando as notas musicais
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};

    // Abre o arquivo para escrita, cria o arquivo se ele não existir e trunca o arquivo se ele já existir
    int ficheiro = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Verifica se o arquivo foi aberto com sucesso
    if (ficheiro < 0)
    {
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("open file");
        exit(EXIT_FAILURE);
    }

    // Inicializa o gerador de números aleatórios com a hora atual como semente
    srand(time(NULL));

    // Gera NUM_PASSWORDS sequências de notas
    for (int i = 0; i < NUM_PASSWORDS; i++)
    {
        // Cada sequência tem PASSWORD_LENGTH notas i.e por chars cada string
        for (int j = 0; j < PASSWORD_LENGTH; j++)
        {
            // Escolhe uma nota aleatória do array de notas
            char *nota = notas[rand() % 12];   //de 0 a 11 intervalo de 12 elementos
            // Escreve um caractere aleatório da nota escolhida no arquivo
            write(ficheiro, &nota[rand() % strlen(nota)], 1);//escolhe um qualquer da nota, i.e palavra que foi escolhida e completada
        }
        // Escreve uma nova linha no arquivo, finalization
        write(ficheiro, "\n", 1);
    }

    // Fecha o arquivo
    close(ficheiro);
}


// A função gerapass12 recebe um nome de arquivo e uma senha como argumentos
/**
 * @brief Gera uma sequência de notas musicais a partir de uma senha e grava em um arquivo.
 * 
 * @param file O nome do arquivo onde a sequência de notas será gravada.
 * @param password A senha a partir da qual a sequência de notas será gerada.
 * 
 * Esta função percorre cada caractere da senha e calcula um índice correspondente a uma nota musical.
 * A nota musical correspondente é então escrita no arquivo.
 * Se o arquivo não existir, ele será criado. Se o arquivo já existir, ele será truncado.
 * 
 * @return void
 */

void gerapass12(const char *file, const char *password)
{
    // Declara um array de strings representando as notas musicais
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};

    // Abre o arquivo para escrita, cria o arquivo se ele não existir e trunca o arquivo se ele já existir
    int ficheiro = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Verifica se o arquivo foi aberto com sucesso
    if (ficheiro < 0)
    {
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("open file");
        exit(EXIT_FAILURE);
    }

    // Percorre cada caractere da senha
    for (int i = 0; password[i] != '\0'; i++)
    {
        // Calcula o índice da nota correspondente ao caractere atual da senha
        int index = password[i] - 'a';
        // Verifica se o índice está dentro do intervalo válido
        if (index >= 0 && index < 12)
        {
            // Escreve a nota correspondente no arquivo
            write(ficheiro, notas[index], strlen(notas[index]));
            // Escreve um espaço no arquivo
            write(ficheiro, " ", 1);
        }
    }

    // Fecha o arquivo
    close(ficheiro);
}



// A função descodificar12 recebe um nome de arquivo como argumento
/**
 * @brief Lê um arquivo de notas musicais e decodifica as notas em caracteres alfabéticos.
 * 
 * @param file O nome do arquivo que contém as notas musicais a serem decodificadas.
 * 
 * Esta função lê um arquivo que contém uma sequência de notas musicais, onde cada nota é separada por um espaço ou uma nova linha.
 * Cada nota é decodificada em um caractere alfabético, onde a primeira nota no array corresponde a 'a', a segunda nota corresponde a 'b', e assim por diante, até a última nota que corresponde a 'l'.
 * As notas decodificadas são escritas na saída padrão.
 * 
 * @return void
 */

void descodificar12(const char *file)
{
    // Declara um array de strings representando as notas musicais
    char *notas[] = {"C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"};

    // Abre o arquivo para leitura
    int ficheiro = open(file, O_RDONLY);

    // Verifica se o arquivo foi aberto com sucesso
    if (ficheiro < 0)
    {
        // Se houver um erro, imprime uma mensagem de erro e termina o programa
        perror("open file");
        exit(EXIT_FAILURE);
    }

    // Declara um array para armazenar a nota atual e inicializa o índice
    char nota[4] = {0};
    int index = 0;
    char c;
    ssize_t read_size;

    // Lê o arquivo caractere por caractere
    while ((read_size = read(ficheiro, &c, 1)) > 0)
    {
        // Se o caractere atual não for um espaço ou uma nova linha e o índice for menor que 3
        if (c != ' ' && c != '\n' && index < 3)
        {
            // Adiciona o caractere à nota atual e incrementa o índice
            nota[index++] = c;
            nota[index] = '\0';
        }
        else
        {
            // Decodifica a nota atual e reinicia o índice
            decode_nota(nota, notas);
            index = 0;
        }
    }

    // Se o arquivo terminar sem um espaço ou uma nova linha e houver uma nota para decodificar
    if (read_size == 0 && index > 0)
    {
        // Decodifica a última nota
        decode_nota(nota, notas);
    }

    // Fecha o arquivo
    close(ficheiro);
}

// A função decode_nota recebe uma nota e um array de notas como argumentos
void decode_nota(char *nota, char *notas[])
{
    // Percorre o array de notas
    for (int i = 0; i < 12; i++)
    {
        // Se a nota atual do array é igual à nota a ser decodificada
        if (strcmp(nota, notas[i]) == 0)
        {
            // Calcula o caractere alfabético correspondente à nota
            char c = i + 'a';
            // Escreve o caractere na saída padrão
            write(STDOUT_FILENO, &c, 1);
            // Termina o loop
            break;
        }
    }
    // Escreve uma nova linha na saída padrão
    write(STDOUT_FILENO,"\n", 1);
}

/*
    Uso de codificacao e descodificacao: 
    (->Capacidade e de 12 notas<-) i.e. limite de 12 letras consecutivas da string
    gerapass12 <file.destino> <string>

    ex:
        $>gerapass12 aa.bb abcdefghijkl

        $>descodificar12 aa.bb
    */