#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <errno.h>

static void err_doit(int, int, const char *, va_list);

void err_ret(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_cont(int error, const char *fmt, ...);
void err_exit(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);

pid_t
pty_fork(int *ptrfdm, char *slave_name, int slave_namesz,
        const struct termios *slave_termios,
        const struct winsize *slave_winsize);

void loop(int ptym, int ignoreeof);

typedef void Sigfunc(int);

Sigfunc *
signal_intr(int signo, Sigfunc *func);
