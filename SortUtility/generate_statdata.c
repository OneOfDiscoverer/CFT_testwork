#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct {
    long id;
    int count;
    float cost;
    unsigned int primary:1;
    unsigned int mode:3;
} StatData;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("To low count of args, [filename.bin]\n");
        return 1;
    }

    const char *filename = argv[1];

    srand((unsigned int) time(NULL));

    int rows_count = 100 + rand() % (10000 - 100 + 1);

    FILE *fd = fopen(filename, "wb");
    if (!fd) {
        perror("Failed to open file");
        return 1;
    }

    for (int i = 0; i < rows_count; ++i) {
        StatData data;
        data.id = 1000 + i;
        data.count = rand() % 100000;
        data.cost = (float)(rand() % 100000) / 100.0f;
        data.primary = rand() % 2;
        data.mode = rand() % 8;

        fwrite(&data, sizeof(StatData), 1, fd);
    }

    fclose(fd);

    printf("Generated %d records in %s\n", rows_count, filename);
    return 0;
}
