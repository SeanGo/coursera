#ifndef __calg4_h_include__
#define __calg4_h_include__

#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <memory.h>
#include <sys/time.h>

//--------------------------------------------------------
// data teype define
#ifndef BOOL
typedef int BOOL;
#define TRUE  1
#define FALSE 0
#endif //BOOL


//--------------------------------------------------------
// macro define
#ifndef MAX_PATH
#define MAX_PATH 260
#endif //MAX_PATH

#define MALLOC(type, n) ((type*)malloc((n) * sizeof(type)))



#include "str.h"
#include "uf.h"



#endif //__calg4_h_include__
