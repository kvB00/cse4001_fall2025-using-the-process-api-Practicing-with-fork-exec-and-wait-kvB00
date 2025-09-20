#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int
main(int argc, char *argv[])
{
	close(STDOUT_FILENO);
	open("./q2.ans", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
	// child: redirect standard output to a file 
	fprintf(stdout, "Child prints\n");

    } else {
        // parent goes down this path (original process)
        fprintf(stdout, "Parent prints\n");
    }
    return 0;
}
