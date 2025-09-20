#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>   // for wait()

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        // simulate some work
       // sleep(1);  // optional: gives a visible delay
        exit(0);   // child exits cleanly
    } else {
        // parent waits for child to finish
        int wc = wait(NULL);  // block until any child finishes
        if (wc == -1) {
            perror("wait");
            exit(1);
        }
        printf("hello, I am parent of %d (pid:%d)\n", rc, (int) getpid());
    }

    return 0;
}

