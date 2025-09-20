#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int x = 100;
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Value of child (pid:%d)\n", (int) getpid());
    } else {
        // parent goes down this path (original process)
        printf(" The parent of %d (pid:%d)\n",
	       rc, (int) getpid());
    }
    return 0;
}
