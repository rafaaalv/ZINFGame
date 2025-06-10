#include <stdio.h>   // Para FILE, fopen, fwrite, fclose, NULL, perror
#include <stdlib.h>  // Para exit
#include <time.h>    // Para time_t, time, localtime, struct tm
#include <string.h>  // Para strcpy

// Defini��o da struct save
typedef struct save
{
    int index;
    struct tm date;
    char path[30]; // Caminho para o arquivo de status associado a este save
} save;

int main() {
    save saves[3]; // <--- Declara um array para armazenar AS 3 STRUCTS SAVE
    char output_filename[] = "../assets/saves/all_saves_data.bin"; // <--- Nome DO �NICO ARQUIVO BIN�RIO DE SA�DA

    // Obter a data e hora atual da CPU
    time_t rawtime;
    time(&rawtime);
    struct tm *current_info = localtime(&rawtime);

    // Definir os caminhos que ser�o armazenados DENTRO DE CADA STRUCT SAVE
    // Estes s�o os METADADOS que cada save guarda sobre onde seu status est�
    char save_paths_in_struct[3][30] = {
        "../assets/saves/save1.bin", // Este caminho estar� dentro da primeira struct 'save'
        "../assets/saves/save2.bin", // Este caminho estar� dentro da segunda struct 'save'
        "../assets/saves/save3.bin"  // Este caminho estar� dentro da terceira struct 'save'
    };

    // Preencher as 3 structs save que est�o no array 'saves'
    for (int i = 0; i < 3; ++i) {
        saves[i].index = i + 1; // �ndices 1, 2, 3
        saves[i].date = *current_info; // Data e hora atual para todas as structs
        strcpy(saves[i].path, save_paths_in_struct[i]); // Caminhos definidos para cada struct
    }

    // Abrir o �NICO arquivo bin�rio para escrita
    FILE *output_file = fopen(output_filename, "wb"); // "wb" para modo de escrita bin�ria
    if (output_file == NULL) {
        perror("Erro ao abrir o arquivo bin�rio para escrita");
        exit(EXIT_FAILURE); // Sai do programa com erro
    }

    // <--- PONTO CHAVE: ESCREVENDO AS 3 STRUCTS DE UMA VEZ NO �NICO ARQUIVO --->
    // fwrite(ponteiro para dados, tamanho de um item, n�mero de itens, arquivo)
    // Aqui, 'saves' � o ponteiro para o in�cio do array de 3 structs 'save'.
    // 'sizeof(save)' � o tamanho de UMA struct 'save'.
    // '3' � o N�MERO TOTAL de structs 'save' que queremos escrever.
    // Isso resulta na escrita sequencial de saves[0], saves[1] e saves[2] no 'output_file'.
    size_t written_items = fwrite(saves, sizeof(save), 3, output_file);

    if (written_items != 3) {
        perror("Erro ao escrever todas as structs save no arquivo bin�rio");
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    // Fechar o arquivo
    fclose(output_file);

    printf("Arquivo bin�rio '%s' criado com sucesso com os dados das 3 structs save.\n", output_filename);
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
