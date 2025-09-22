#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>   

int main(int argc, char *argv[]) {

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Child at work (pid:%d)\n", (int) getpid());
        exit(0);   
    } else {
        // parent waits for child to finish
        int wc = wait(NULL);  // block until any child finishes
        if (wc == -1) {
            perror("wait");
            exit(1);
        }
        printf("Parent at work (pid:%d)\n", (int) getpid());
    }

    return 0;
}

