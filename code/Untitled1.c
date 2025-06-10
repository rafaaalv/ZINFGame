#include <stdio.h>   // Para FILE, fopen, fwrite, fclose, NULL, perror
#include <stdlib.h>  // Para exit
#include <time.h>    // Para time_t, time, localtime, struct tm
#include <string.h>  // Para strcpy

// Definição da struct save
typedef struct save
{
    int index;
    struct tm date;
    char path[30]; // Caminho para o arquivo de status associado a este save
} save;

int main() {
    save saves[3]; // <--- Declara um array para armazenar AS 3 STRUCTS SAVE
    char output_filename[] = "../assets/saves/all_saves_data.bin"; // <--- Nome DO ÚNICO ARQUIVO BINÁRIO DE SAÍDA

    // Obter a data e hora atual da CPU
    time_t rawtime;
    time(&rawtime);
    struct tm *current_info = localtime(&rawtime);

    // Definir os caminhos que serão armazenados DENTRO DE CADA STRUCT SAVE
    // Estes são os METADADOS que cada save guarda sobre onde seu status está
    char save_paths_in_struct[3][30] = {
        "../assets/saves/save1.bin", // Este caminho estará dentro da primeira struct 'save'
        "../assets/saves/save2.bin", // Este caminho estará dentro da segunda struct 'save'
        "../assets/saves/save3.bin"  // Este caminho estará dentro da terceira struct 'save'
    };

    // Preencher as 3 structs save que estão no array 'saves'
    for (int i = 0; i < 3; ++i) {
        saves[i].index = i + 1; // Índices 1, 2, 3
        saves[i].date = *current_info; // Data e hora atual para todas as structs
        strcpy(saves[i].path, save_paths_in_struct[i]); // Caminhos definidos para cada struct
    }

    // Abrir o ÚNICO arquivo binário para escrita
    FILE *output_file = fopen(output_filename, "wb"); // "wb" para modo de escrita binária
    if (output_file == NULL) {
        perror("Erro ao abrir o arquivo binário para escrita");
        exit(EXIT_FAILURE); // Sai do programa com erro
    }

    // <--- PONTO CHAVE: ESCREVENDO AS 3 STRUCTS DE UMA VEZ NO ÚNICO ARQUIVO --->
    // fwrite(ponteiro para dados, tamanho de um item, número de itens, arquivo)
    // Aqui, 'saves' é o ponteiro para o início do array de 3 structs 'save'.
    // 'sizeof(save)' é o tamanho de UMA struct 'save'.
    // '3' é o NÚMERO TOTAL de structs 'save' que queremos escrever.
    // Isso resulta na escrita sequencial de saves[0], saves[1] e saves[2] no 'output_file'.
    size_t written_items = fwrite(saves, sizeof(save), 3, output_file);

    if (written_items != 3) {
        perror("Erro ao escrever todas as structs save no arquivo binário");
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    // Fechar o arquivo
    fclose(output_file);

    printf("Arquivo binário '%s' criado com sucesso com os dados das 3 structs save.\n", output_filename);
    printf("Dados escritos (index, data, path):\n");
    for (int i = 0; i < 3; ++i) {
        printf("  Save %d: Index=%d, Date=%02d/%02d/%d %02d:%02d:%02d, Path=%s\n",
               saves[i].index,
               saves[i].index,
               saves[i].date.tm_mday, saves[i].date.tm_mon + 1, saves[i].date.tm_year + 1900,
               saves[i].date.tm_hour, saves[i].date.tm_min, saves[i].date.tm_sec,
               saves[i].path);
    }

    return 0;
}
