#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
       // exec("bin/ls","ls", (char *)NULL);
	execl("/bin/ls","ls", (char *)NULL);
	//execle("/bin/ls","ls", (char *)NULL);
	//execlp("/bin/ls","ls", (char *)NULL);
	//execv("/bin/ls","ls", (char *)NULL);
	//execvp("/bin/ls","ls", (char *)NULL);
	//execvpe("/bin/ls","ls", (char *)NULL);
    } else {
        int wc = wait(NULL);
    }
    return 0;
}
