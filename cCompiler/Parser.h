#ifndef __PARSE_H
#define __PARSE_H

#include "Compiler.h"

#define ND_NUM "ND_NUM"
#define ND_KAKE "ND_KAKE"
#define ND_ADD "ND_ADD"
#define ND_SUB "ND_SUB"
#define ND_WARI "ND_WARI"
#define ND_TYPE "ND_TYPE"
#define ND_VAL "ND_VAL"
#define ND_INIT "ND_INIT"
#define ND_ASSIGN "ND_ASSIGN"

typedef struct Node Node;
struct Node
{
	Node* rhs;
	Node* lhs;
	char* kind;
	char* str;
	int val;
	Cabinet* cabinet;
};

Node* parse(Token** curToken,Cabinet **curCabinet);
Node* mul(Token** curToken, Cabinet** curCabinet,Node* curNode);
Node* add(Token** curToken, Cabinet** curCabinet, Node* curNode);
Node* primary(Token** curToken, Cabinet** curCabinet, Node* curNode);
Node* initializetion(Token** curToken, Cabinet** curCabinet, Node* curNode);
Node* assign(Token** curToken, Cabinet** curCabinet, Node* curNode);
#endif 