#include "main.h"

void StoreDump(char* path, StatBuffer* toWriteDupm) {
    int fd = open(path, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    StatData **toSortArray = toWriteDupm->ptr; 
    for (long i = 0; i < toWriteDupm->size; i++) { 
        write(fd, toSortArray[i], sizeof(StatData));
    }
    close(fd);
}

StatBuffer* CreateStatBuffer(long size) {
    StatBuffer *buf = malloc(sizeof(StatBuffer));
    StatData* ptr = malloc(size);
    buf->ptr = ptr;
    buf->size = size/sizeof(StatData);
    return buf;
}

StatBuffer* LoadDump(char* path) {
    int fd = open(path, O_RDONLY);
    struct stat fileInfo; 

    if (fstat(fd, &fileInfo) != 0) {
        return 0;
    }

    size_t size = fileInfo.st_size;

    if (size % sizeof(StatData) != 0 || size == 0) {
        fprintf(stderr, "file %s wrong size\n", path);
        exit(EXIT_FAILURE);
    } 

    StatBuffer *buf = CreateStatBuffer(size);
    read(fd, buf->ptr, size);
    close(fd);

    return buf;
}

HashTable* JoinDump(StatBuffer* firstArray, StatBuffer* secondArray) {
    HashTable *hashTable = create_table(MAX_IDs);
    StatBuffer *arrayPointer = firstArray;
    while (1) {
        for(int i = 0; i < arrayPointer->size; i++) {
            StatData *value;
            if (!get(hashTable, arrayPointer->ptr[i].id, &value)) {
                insert(hashTable, arrayPointer->ptr[i].id, arrayPointer->ptr[i]);
            } else {
                StatData attachValue = arrayPointer->ptr[i];
                value->cost += attachValue.cost;
                value->count += attachValue.count;
                value->primary &= attachValue.primary;
                value->mode = (value->mode > attachValue.primary) ? value->mode : attachValue.mode; 
            }
            
        }
        if (arrayPointer != firstArray) {
            break;
        }
        free(arrayPointer);
        arrayPointer = secondArray;
    }
    return hashTable;
}

int compare(const void *first, const void *second) {
    StatData *firstData = *(StatData**)first;
    StatData *secondData = *(StatData**)second;
    return (firstData->cost > secondData->cost) ? 1 : -1;
}

StatBuffer* SortDump(HashTable* ht) {
    StatBuffer *buf = CreateStatBuffer(ht->count * sizeof(StatData*));
    StatData **toSortArray = buf->ptr; 
    long count = 0;
    for (int i = 0; i < ht->size; i++) {
        StatData *value;
        if (get(ht, i, &toSortArray[count])) {
            count++;
        }
    }
    buf->size = count;
    qsort(toSortArray, count, sizeof(StatData*), compare);
    return buf;
}

void PrintFirstRows(StatBuffer* statBuffer) {
    StatData **buf = statBuffer->ptr;
    const long len = (statBuffer->size > COUNT_PRINT_ROWS) ? COUNT_PRINT_ROWS : statBuffer->size;
    for(int i = 0; i < len; i++) {
        StatData *val = buf[i];
        unsigned int modeMode = val->mode;
        char binaryOutput[sizeof(modeMode)*__CHAR_BIT__ + 1];
        for (int i = 0; i < sizeof(modeMode)*__CHAR_BIT__; i++) {
            binaryOutput[i] = ((modeMode >> (sizeof(modeMode)*__CHAR_BIT__ - i - 1)) & 1) + 0x30;
        }
        binaryOutput[sizeof(modeMode)*__CHAR_BIT__] = 0;
        strchr(binaryOutput, '1') + 1; 
        printf("id: %6x count: %6d cost %10.3e primary: %1c mode: %s \n", val->id, val->count, val->cost, (val->primary) ? 'y': 'n', strchr(binaryOutput, '1'));
    }
}

int main(int argc, char* argv[]) {
    StatBuffer *firstFile, *secondFile;
    if (argc < 4) {
        fprintf(stderr, "To low count of args, [path to file 1][path to file 2][path to result file]\n");
        exit(EXIT_FAILURE);
    }
    firstFile = LoadDump(argv[1]);
    secondFile = LoadDump(argv[2]);
    if (!firstFile || !secondFile) {
        fprintf(stderr, "file's corrupted\n");
        exit(EXIT_FAILURE);
    }
    HashTable *ht = JoinDump(firstFile, secondFile);
    StatBuffer *sortedDump = SortDump(ht);
    PrintFirstRows(sortedDump);
    char finPath[PATH_MAX] = {"./"};
    (strstr(argv[3], "./") != NULL) ? strcat(finPath, argv[3]) : strcpy(finPath, argv[3]);
    StoreDump(finPath, sortedDump);
    return 0;
}
