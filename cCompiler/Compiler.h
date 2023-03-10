#ifndef __COMPILER_H
#define __COMPILER_H

#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"
#include "Tokenizer.h"
#include "TokenizeTools.h"
#include "Cabinet.h"
#include "Parser.h"
#include "ParseTools.h"
#include "CodeGenerator.h"
#include "CodeGeneratorTools.h"
#include "TypeList.h"

#define TEXT_SIZE 1024
#define MAX_SYMBOL_SIZE 5
#define RHS rhs

/*
* R[h@@i\¶@hGhj*
* \¶@@i®j*
* ®@@Á¸|ú»|ãü|§ä\¶
* Á¸@@æih+hæbh[hæj*
* æ@@vfih*hvfbh/hvfj*
* vf@@lbhih®hjh
* ú»@@^¼ Ï¼
* ^¼@@"int"|"char"
* ãü@@Ï¼@hhÁ¸
* §ä\¶@@if¶
* if¶@@"if" '('ð®')' '{'\¶'}' ("else"'{'\¶'}')?
*/

#endif
