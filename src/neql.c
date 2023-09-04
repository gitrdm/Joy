/*
    module  : neql.c
    version : 1.4
    date    : 09/04/23
*/
#ifndef NEQL_C
#define NEQL_C

#include "compare.h"

/**
OK 2260  !=\0neql  :  X Y  ->  B
Either both X and Y are numeric or both are strings or symbols.
Tests whether X not equal to Y.  Also supports float.
*/
COMPREL(neql_, "!=", BOOLEAN_NEWNODE, !=, i != j)


#endif
