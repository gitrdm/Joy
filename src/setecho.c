/*
    module  : setecho.c
    version : 1.4
    date    : 09/04/23
*/
#ifndef SETECHO_C
#define SETECHO_C

/**
OK 3000  setecho  :  I  ->
Sets value of echo flag for listing.
I = 0: no echo, 1: echo, 2: with tab, 3: and linenumber.
*/
USETOP(setecho_, "setecho", NUMERICTYPE, env->echoflag = nodevalue(env->stck).num)


#endif
