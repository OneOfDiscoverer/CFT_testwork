#ifndef _MAIN_H
#define _MAIN_H

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "linux/limits.h"
#include "fcntl.h"
#include "sys/stat.h"
#include "string.h"
#include "time.h"
#include "sys/wait.h"

#define REL_PATH_APP    "/SortUtility/main.out"
#define TESTDIR         "/TestUtility"
#define TESTFILE_1      "testdata1.bin"
#define TESTFILE_2      "testdata2.bin"
#define FINFILE         "findata.bin"
#define MSECMULTIPLIER  1000000

/* Содержимое для исходных файлов */
typedef struct StatData {
    long id;
    int count;
    float cost;
    unsigned int primary:1;
    unsigned int mode:3;
} StatData;

const StatData case_1_in_a[2] =
{   
    {.id = 90889, .count = 13, .cost = 3.567, .primary = 0, .mode=3 },
    {.id = 90089, .count = 1, .cost = 88.90, .primary = 1, .mode=0 }
};
const StatData case_1_in_b[2] =
{
    {.id = 90089, .count = 13, .cost = 0.011, .primary = 0, .mode=2 },
    {.id = 90189, .count = 1000, .cost = 1.00003, .primary = 1, .mode=2}
};
/* Ожидаемый результат обработки */
const StatData case_1_out[3] =
{
    {.id = 90189, .count = 1000, .cost = 1.00003, .primary = 1, .mode = 2 },
    {.id = 90889, .count = 13, .cost = 3.567, .primary = 0, .mode = 3 },
    {.id = 90089, .count = 14, .cost = 88.911, .primary = 0, .mode = 2 }
};
#endif