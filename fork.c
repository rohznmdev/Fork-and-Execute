#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

// defines the buffsize.
#define BUFFSIZE 4096

/**
 * THe main function for this lab will act as the parent function which controls
 * the child processes.
 *
 */
int main(int argc, char* argv[]) {

    // setting base variable
    int flag = 0;
    // runs until the exit command is pressed.
    while (flag == 0) {
        // setting up variables for how many commands and how many spaces in a command.
        char buf[BUFFSIZE];
        int cnt = 0;
        int spaces = 0;
        int f;
        int exec;
        setbuf(stdout, NULL);
        // asks for a command.
        printf("Please enter a command: ");
        // checking for necessary condition.
        if ((f = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
            // counts the number of spaces in the command.
            for (int x = 0; x < f; x++) {
                if (buf[x] == ' ') {
                    // increments space count.
                    spaces++;
                } // if
            } // for
        } // if
        // defining variables for number of arguments and strings.
        char args[3] = " \n";
        char* argString[300];
        char* token = strtok(buf, args);
        // incrementing tokens.
        while (token != NULL) {
            argString[cnt] = token;
            // increments the count.
            cnt++;
            token = strtok(NULL, args);
        } // while
        // setting the index to null.
        argString[spaces + 1] = NULL;
        // exit command code. will exit the program if the command is exit.
        if (strcmp(argString[0], "exit") == 0) {
            exit(0);
        } // if
        pid_t launchFork;
        // fork code. runs the functions using the fork function.
        if ((launchFork = fork()) < 0) {
            perror("fork");
        } else if (launchFork == 0) {
            exec = execvp(argString[0], &argString[0]);
            // checking for errors.
            if (exec == -1) {
                perror("execute");
            } // if
        } else {
            printf("\n");
            sleep(1);
        } // else if
    } // while
    // exits the program.
    return EXIT_SUCCESS;
} // main
