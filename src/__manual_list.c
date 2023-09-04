/*
    module  : __manual_list.c
    version : 1.4
    date    : 09/04/23
*/
#ifndef __MANUAL_LIST_C
#define __MANUAL_LIST_C

/**
OK 2960  __manual_list  :  ->  L
Pushes a list L of lists (one per operator) of three documentation strings.
*/
PRIVATE void __manual_list_(pEnv env)
{
    int i;

    for (i = 0; opername(i); i++)
        ; /* find end */
    --i; /* overshot */
    env->dump1 = LIST_NEWNODE(0, env->dump1);
    env->dump2 = LIST_NEWNODE(0, env->dump2);
    while (i) {
        DMP1 = STRING_NEWNODE(optable[i].messg2, 0);
        DMP1 = STRING_NEWNODE(optable[i].messg1, DMP1);
        DMP1 = STRING_NEWNODE(optable[i].name, DMP1);
        DMP2 = LIST_NEWNODE(DMP1, DMP2);
        --i;
    }
    env->stck = LIST_NEWNODE(DMP2, env->stck);
    POP(env->dump2);
    POP(env->dump1);
}
#endif
