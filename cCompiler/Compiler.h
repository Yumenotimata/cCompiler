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

/*
* コード　＝　（構文　”；”）*
* 構文　＝　（式）*
* 式　＝　加減|初期化|代入
* 加減　＝　乗除（”+”乗除｜”ー”乗除）*
* 乗除　＝　数要素（”*”数要素｜”/”数要素）*
* 数要素　＝　数値｜”（”式”）”
* 初期化　＝　型名 変数名
* 型名　＝　"int"|"char"
* 代入　＝　変数名　”＝”式
*/

#endif
