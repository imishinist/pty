#include "pty.h"

Sigfunc *
signal_intr(int signo, Sigfunc *func)
{
    struct sigaction act, oact;

    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERUPT
    act.sa_flags |= SA_INTERUPT
#endif
    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return oact.sa_handler;
}
