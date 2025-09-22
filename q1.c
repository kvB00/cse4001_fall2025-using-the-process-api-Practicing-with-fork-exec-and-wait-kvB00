#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	int x = 100;
	printf("Value before fork: x = %d (pid:%d)\n", x, (int) getpid());

    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("Child initially sees x value of %d (pid:%d)\n", x, (int) getpid());
	x = 200;
	printf("Child now sees x value of %d (pid:%d)\n", x, (int) getpid());
    } else {
        printf("Parent initially sees x value of %d (pid:%d)\n", x, (int) getpid());
	x = 300;
        printf("Parent now sees x value of %d (pid:%d)\n", x, (int) getpid());
    }
    return 0;
}
