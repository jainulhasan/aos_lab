#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "  %s <pid>               (kill <pid>)\n", argv[0]);
        fprintf(stderr, "  %s -<signo> <pid>      (kill -<signo> <pid>)\n", argv[0]);
        fprintf(stderr, "  %s <pid1> <pid2> ...   (kill <pid1> <pid2> ...)\n", argv[0]);
        fprintf(stderr, "  %s -<signo> <pid1> <pid2> ... (kill -<signo> <pid1> <pid2> ...)\n", argv[0]);
        return 1;
    }

    // Determine the signal number and PIDs based on command-line arguments
    int signo = SIGTERM; // Default signal is SIGTERM
    int arg_start = 1;   // Index of the first argument

    if (argv[1][0] == '-') {
        // If the first argument starts with a '-', it's a signal option
        if (strcmp(argv[1], "-k") == 0) {
            // If the signal option is "-k", we treat it as a custom signal
            signo = SIGKILL; // Change the signal to SIGKILL
            arg_start = 2;   // Start from the next argument
        } else {
            // If it's not "-k", extract the signal number
            signo = atoi(argv[1] + 1); // Extract the signal number
            arg_start = 2;             // Start from the next argument
        }
    }

    // Iterate through the PIDs and send the signal to each process
    for (int i = arg_start; i < argc; i++) {
        int pid = atoi(argv[i]);
        if (kill(pid, signo) == 0) {
            printf("Sent signal %d to process %d\n", signo, pid);
        } else {
            perror("Error sending signal");
        }
    }

    return 0;
}
