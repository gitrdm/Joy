/*
    module  : fget.c
    version : 1.6
    date    : 09/04/23
*/
#ifndef FGET_C
#define FGET_C

/**
OK 3180  fget  :  S  ->  S F
[EXT] Reads a factor from stream S and pushes it onto stack.
*/
PRIVATE void fget_(pEnv env)
{
    FILE *fp;
    int stdin_dup;

    ONEPARAM("fget");
    FILE("fget");
    fp = nodevalue(env->stck).fil;
    if ((stdin_dup = dup(0)) != -1)
        dup2(fileno(fp), 0);
    getsym(env);
    readfactor(env);
    if (stdin_dup != -1) {
        dup2(stdin_dup, 0);
        close(stdin_dup);
    }
}
#endif
