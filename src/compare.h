/*
    module  : compare.h
    version : 1.18
    date    : 04/11/24
*/
#ifndef COMPARE_H
#define COMPARE_H

int is_null(pEnv env, Index node)
{
    switch (nodetype(node)) {
    case USR_:
        return !nodevalue(node).ent;
    case ANON_FUNCT_:
        return !nodevalue(node).proc;
    case BOOLEAN_:
    case CHAR_:
    case INTEGER_:
        return !nodevalue(node).num;
    case SET_:
        return !nodevalue(node).set;
    case STRING_:
        return !*nodevalue(node).str;
    case LIST_:
        return !nodevalue(node).lis;
    case FLOAT_:
        return !nodevalue(node).dbl;
    case FILE_:
        return !nodevalue(node).fil;
    }
    return 0;
}

int Compare(pEnv env, Index first, Index second)
{
    FILE *fp1, *fp2;
    int type1, type2;
    char *name1, *name2;
    double dbl1 = 0, dbl2 = 0;
    int64_t num1 = 0, num2 = 0;

    if (is_null(env, first) && is_null(env, second))	/* nothing is unique */
	return 0;
    type1 = nodetype(first);
    type2 = nodetype(second);
    switch (type1) {
    case USR_:
	name1 = vec_at(env->symtab, nodevalue(first).ent).name;
	switch (type2) {
	case USR_:
	    name2 = vec_at(env->symtab, nodevalue(second).ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	    name2 = nickname(operindex(env, nodevalue(second).proc));
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	    return 1; /* unequal */
	case STRING_:
	    name2 = nodevalue(second).str;
	    goto cmpstr;
	}
	break;
    case ANON_FUNCT_:
	name1 = nickname(operindex(env, nodevalue(first).proc));
	switch (type2) {
	case USR_:
	    name2 = vec_at(env->symtab, nodevalue(second).ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	    name2 = nickname(operindex(env, nodevalue(second).proc));
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	    return 1; /* unequal */
	case STRING_:
	    name2 = nodevalue(second).str;
	    goto cmpstr;
	}
	break;
    case BOOLEAN_:
	num1 = nodevalue(first).num;
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = nodevalue(second).num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = nodevalue(second).dbl;
	    goto cmpdbl;
	default:
	    return 1; /* unequal */
	}
	break;
    case CHAR_:
	num1 = nodevalue(first).num;
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = nodevalue(second).num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = nodevalue(second).dbl;
	    goto cmpdbl;
	default:
	    return 1; /* unequal */
	}
	break;
    case INTEGER_:
	num1 = nodevalue(first).num;
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	    num2 = nodevalue(second).num;
	    goto cmpnum;
	case FLOAT_:
	    dbl1 = num1;
	    dbl2 = nodevalue(second).dbl;
	    goto cmpdbl;
	default:
	    return 1; /* unequal */
	}
	break;
    case SET_:
	num1 = nodevalue(first).set;
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case FLOAT_:
	    num2 = nodevalue(second).num;
	    goto cmpnum;
	default:
	    return 1; /* unequal */
	}
	break;
    case STRING_:
	name1 = nodevalue(first).str;
	switch (type2) {
	case USR_:
	    name2 = vec_at(env->symtab, nodevalue(second).ent).name;
	    goto cmpstr;
	case ANON_FUNCT_:
	    name2 = nickname(operindex(env, nodevalue(second).proc));
	    goto cmpstr;
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	case SET_:
	case LIST_:
	case FLOAT_:
	case FILE_:
	    return 1; /* unequal */
	case STRING_:
	    name2 = nodevalue(second).str;
	    goto cmpstr;
	}
	break;
    case LIST_:
	return 1; /* unequal */
    case FLOAT_:
	dbl1 = nodevalue(first).dbl;
	switch (type2) {
	case BOOLEAN_:
	case CHAR_:
	case INTEGER_:
	    dbl2 = nodevalue(second).num;
	    goto cmpdbl;
	case SET_:
	    num1 = nodevalue(first).num;
	    num2 = nodevalue(second).num;
	    goto cmpnum;
	case FLOAT_:
	    dbl2 = nodevalue(second).dbl;
	    goto cmpdbl;
	default:
	    return 1; /* unequal */
	}
	break;
    case FILE_:
	fp1 = nodevalue(first).fil;
	switch (type2) {
	case FILE_:
	    fp2 = nodevalue(second).fil;
	    return fp1 < fp2 ? -1 : fp1 > fp2;
	default:
	    return 1; /* unequal */
	}
	break;
    }
cmpnum:
    return num1 < num2 ? -1 : num1 > num2;
cmpdbl:
    return dbl1 < dbl2 ? -1 : dbl1 > dbl2;
cmpstr:
    num1 = strcmp(name1, name2);
    return num1 < 0 ? -1 : num1 > 0;
}
#endif
