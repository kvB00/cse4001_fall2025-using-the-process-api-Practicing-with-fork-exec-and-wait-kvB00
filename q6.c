#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define Num_C 3

int main(void) {
    pid_t pids[Num_C];

    // Fork multiple children
    for (int i = 0; i < Num_C; i++) {
        pid_t rc = fork();
        if (rc < 0) {
            perror("fork");
            exit(1);
        } else if (rc == 0) {
            // Child process
            printf("Child %d at work (pid:%d)\n", i, (int)getpid());
            // Exit with a code that encodes which child it was
            _exit(40 + i);  
        } else {
            // Parent: remember child's PID
            pids[i] = rc;
        }
    }

    // Parent waits for each specific child (order here is deterministic by index)
    for (int i = 0; i < Num_C; i++) {
        int status = 0;
        pid_t w = waitpid(pids[i], &status, 0);  
        if (w == -1) {
            perror("waitpid");
            exit(1);
        }

       /* if (WIFEXITED(status)) {
            printf("Child %d (pid:%d) exited with status %d\n",
                   i, (int)w, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child %d (pid:%d) terminated by signal %d\n",
                   i, (int)w, WTERMSIG(status));
        }*/
    }

    printf("Parent at work (pid:%d) — all children finished\n", (int)getpid());
    return 0;
}


