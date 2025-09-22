# Assignment: Practicing the Process API
Practicing with fork, exec, wait. 

### Overview

In this assignment, you will practice using the Process API to create processes and run programs under Linux. The goal is to gain hands-on experience with system calls related to process management. Specifically, you will practice using the unix process API functions 'fork()', 'exec()', 'wait()', and 'exit()'. 

⚠️ Note: This is not an OS/161 assignment. You will complete it directly on Linux. 

Use the Linux in your CSE4001 container. If you are using macOS, you may use the Terminal (you may need to install development tools with C/C++ compilers). 

**Reference Reading**: Arpaci-Dusseau, *Operating Systems: Three Easy Pieces*, Chapter 5 (Process API Basics)
 👉 [Chapter 5 PDF](http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf)

---

### **Steps to Complete the Assignment**

1. **Accept the GitHub Classroom Invitation**
    [GitHub Link](https://classroom.github.com/a/FZh4BrQG)
2. **Set up your Repository**
   - Clone the assignment repository.
3. **Study the Reference Materials**
   - Read **Chapter 5**.
   - Download and explore the sample programs from the textbook repository:
      [OSTEP CPU API Code](https://github.com/remzi-arpacidusseau/ostep-code/tree/master/cpu-api).
4. **Write Your Programs**
   - Adapt the provided example code to answer the assignment questions.
   - Each program should be clear, well-commented, and compile/run correctly.
   - Add your solution source code to the repository.

5. **Prepare Your Report**
   - Answer the questions in the README.md file. You must edit the README.md file and not create another file with the answers. 
   - For each question:
     - Include your **code**.
     - Provide your **answer/explanation**.
6. **Submit Your Work via GitHub**
   - Push both your **program code** to your assignment repository.
   - This push will serve as your submission.
   - Make sure all files, answers, and screenshots are uploaded and rendered properly.








---
### Questions
1. Write a program that calls `fork()`. Before calling `fork()`, have the main process access a variable (e.g., x) and set its value to something (e.g., 100). What value is the variable in the child process? What happens to the variable when both the child and parent change the value of x?


```cpp
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
 
```
_When both parent and child change the value of x, they end up with a different output than the other. They are both initially 100, but when x changes to 200 in the child, x then shows a value of 200, while the parent ends up with a value for x of 300 after a new integer definition has been defined after the fork._

OUTPUT:
```cpp
Value before fork: x = 100 (pid:67417)
Parent initially sees x value of 100 (pid:67417)
Parent now sees x value of 300 (pid:67417)
Child initially sees x value of 100 (pid:67418)
Child now sees x value of 200 (pid:67418)
```


2. Write a program that opens a file (with the `open()` system call) and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor returned by `open()`? What happens when they are writing to the file concurrently, i.e., at the same time?

```cpp
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
```
_The reason is..._

OUTPUT:
```cpp

```

3. Write another program using `fork()`.The child process should print “hello”; the parent process should print “goodbye”. You should try to ensure that the child process always prints first; can you do this without calling `wait()` in the parent?

```cpp
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
        printf("Hello!\n");
    } else {
        sleep(1);// Delay to let child execute first
        printf("Goodbye!\n");
    }
    return 0;
}
```
_Here, the sleep() function makes the parent sleep for 1 second, in which the child will have finished its tasks; Thus, there is a way to make the parent wait until the child has completed its tasks without using wait(), although the wait() function is a better option for precision and efficiency._

OUTPUT:
```cpp
Hello!
Goodbye!
```

4. Write a program that calls `fork()` and then calls some form of `exec()` to run the program `/bin/ls`. See if you can try all of the variants of `exec()`, including (on Linux) `execl()`, `execle()`, `execlp()`, `execv()`, `execvp()`, and `execvpe()`. Why do you think there are so many variants of the same basic call?

```cpp
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
```

OUTPUT:
```cpp
ex4.c		p3		q1		q3		q5.c		README.md
p1		p3.c		q1.c		q3.c		q6
p1.c		p4		q2		q4		q6.c
p2		p4.c		q2.ans		q4.c		q7
p2.c		p4.output	q2.c		q5		q7.c
```

5. Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?

```cpp
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
```
_If you use wait() in the child..._

OUTPUT:
```cpp
Child at work (pid:67476)
Parent at work (pid:67475)
```

6. Write a slight modification of the previous program, this time using `waitpid()` instead of `wait()`. When would `waitpid()` be useful?

```cpp
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
```
_It would be useful to use waitpid() when..._

OUTPUT:
```cpp
Child 0 at work (pid:67491)
Child 1 at work (pid:67492)
Child 2 at work (pid:67493)
Parent at work (pid:67490) — all children finished
```

7. Write a program that creates a child process, and then in the child closes standard output (`STDOUT FILENO`). What happens if the child calls `printf()` to print some output after closing the descriptor?

```cpp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

 int main(int argc, char *argv[]) {
         int rc = fork();
        if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
        } else if (rc == 0) {
                close(STDOUT_FILENO);
                printf("Child");

        } else {
                int rc_wait = wait(NULL);
                printf("Parent");
        }
        return 0;
 }
```
_If the child calls printf() to print something after the file has been closed, nothing will print._

OUTPUT:
```cpp
Parent%
```

