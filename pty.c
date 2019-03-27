#include "pty.h"
#include <stdio.h>
#include <termios.h>

#define OPTSTR "+d:einv"

static void set_noecho(int);

int main(int argc, char *argv[]) {
    int fdm, c, ignoreeof, interactive, noecho, verbose;
    pid_t pid;
    char *driver;
    char slave_name[20];
    struct termios orig_termios;
    struct winsize size;

    interactive = isatty(STDIN_FILENO);
    ignoreeof = 0;
    noecho = 0;
    verbose = 0;
    driver = NULL;

    opterr = 0;
    while ((c = getopt(argc, argv, OPTSTR)) != EOF) {
        switch (c) {
            case 'e':
                noecho = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                err_quit("unrecognized option: -%c", optopt);
        }
    }

    if (optind >= argc)
        err_quit("usage: pty [ -d driver -einv ] program [ arg ... ]");

    pid = pty_fork(&fdm, slave_name, sizeof(slave_name), NULL, NULL);

    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (noecho)
            set_noecho(STDIN_FILENO);

        if (execvp(argv[optind], &argv[optind]) < 0)
            err_sys("can't execute: %s", argv[optind]);
    }
    if (verbose) {
        fprintf(stderr, "slave name = %s\n", slave_name);
    }

    loop(fdm, ignoreeof);

    return 0;
}

static void
set_noecho(int fd)
{
    struct termios stermios;

    if (tcgetattr(fd, &stermios) < 0)
        err_sys("tcgetattr error");

    stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    
    stermios.c_oflag &= ~(ONLCR);

    if (tcsetattr(fd, TCSANOW, &stermios) < 0)
        err_sys("tcsetattr error");
}
