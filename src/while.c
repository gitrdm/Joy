/*
    module  : while.c
    version : 1.4
    date    : 09/04/23
*/
#ifndef WHILE_C
#define WHILE_C

/**
OK 2700  while  :  [B] [D]  ->  ...
While executing B yields true executes D.
*/
PRIVATE void while_(pEnv env)
{
    TWOPARAMS("while");
    TWOQUOTES("while");
    SAVESTACK;
    do {
        env->stck = SAVED3;
        exeterm(env, nodevalue(SAVED2).lis); /* TEST */
        CHECKSTACK("while");
        if (!nodevalue(env->stck).num)
            break;
        env->stck = SAVED3;
        exeterm(env, nodevalue(SAVED1).lis); /* DO */
        SAVED3 = env->stck;
    } while (1);
    env->stck = SAVED3;
    POP(env->dump);
}
#endif
