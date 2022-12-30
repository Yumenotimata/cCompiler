#ifndef __TOKEN_H
#define __TOKEN_H

#define TK_NUM "TK_NUM"
#define TK_SYMBOL "TK_SYMBOL"
#define TK_STR "TK_STR"

typedef struct Token Token;
struct Token
{
	Token* next;
	char* str;
	char* kind;
	int val;
};

#endif