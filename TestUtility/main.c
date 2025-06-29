#include "main.h"

void StoreDump(char* path, const StatData toWriteDump[], long size) {
    int fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    for (long i = 0; i < size; i++) { 
        write(fd, &toWriteDump[i], sizeof(StatData));
    }
    close(fd);
}

int CompareDump(char* path) {
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

    char buffer[size]; 
    read(fd, buffer, size);
    close(fd);

    if (!memcmp(buffer, case_1_out, size)) {
        return 1;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    char path[PATH_MAX];
    char mainAppPath[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    char* progName = strrchr(argv[0], '/')+1;
    *strstr(path, progName) = 0;
    strcpy(mainAppPath, path);
    *strstr(mainAppPath, TESTDIR) = 0;

    char commandPath[PATH_MAX] = {};
    strcpy(commandPath, mainAppPath);
    strcat(commandPath, REL_PATH_APP);

    char arg1[PATH_MAX];
    strcpy(arg1, path);
    strcat(arg1, TESTFILE_1);
    StoreDump(arg1, case_1_in_a, 2);

    char arg2[PATH_MAX];
    strcpy(arg2, path);
    strcat(arg2, TESTFILE_2);
    StoreDump(arg2, case_1_in_b, 2);

    char arg3[PATH_MAX];
    strcpy(arg3, path);
    strcat(arg3, FINFILE);

    int stderr_pipe[2];
    pid_t pid;
    if (pipe(stderr_pipe) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    clock_t start = clock();
    
    if (pid == 0) {
        close(stderr_pipe[0]);
        
        dup2(stderr_pipe[1], STDERR_FILENO);
        close(stderr_pipe[1]);

        int retval = execl(commandPath, commandPath, arg1, arg2, arg3, NULL);
        
        perror("exec failed");
        exit(EXIT_FAILURE);
    } else { 

        close(stderr_pipe[1]);
        
        char buffer[256];
        ssize_t bytes_read;
        
        while ((bytes_read = read(stderr_pipe[0], buffer, sizeof(buffer)-1)) > 0) {
            buffer[bytes_read] = '\0';
            printf("error from tested app: %s \n", buffer);
        }

        close(stderr_pipe[0]);  

        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            printf("tested app returned: %d\n", WEXITSTATUS(status));
        }
        clock_t stop = clock();

        double cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;
        printf((CompareDump(arg3) == 1) ? "Test passed %.0f ms\n" : "Test failure \n", cpu_time*MSECMULTIPLIER);
        remove(arg1);
        remove(arg2);
        remove(arg3);
    }

    return 0;
}