#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <-kill|-<signo>> <pid1> [<pid2> ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int signo = SIGTERM; // Default signal is SIGTERM

    // Check for optional signal specification
    if (argv[1][0] == '-') {
        if (argv[1][1] == 'k') {
            signo = SIGKILL; // Use SIGKILL if specified with -kill
        } else {
            // Extract the signal number from the argument
            signo = atoi(argv[1] + 1);
        }

        // Shift the arguments to skip the signal specification
        argc--;
        argv++;
    }

    // Iterate through the remaining arguments (PIDs)
    for (int i = 2; i < argc; i++) {
        int pid = atoi(argv[i]);

        if (kill(pid, signo) == 0) {
            printf("Sent signal %d to process with PID %d\n", signo, pid);
        } else {
            perror("Error sending signal");
        }
    }

    return 0;
}
