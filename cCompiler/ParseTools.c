#include "Compiler.h"

bool isSameString(char *string,char *cmpString)
{
	if (!memcmp(string, cmpString, strlen(cmpString)))
	{
		return true;
	}

	return false;

}

Node* createNumNode(int val)
{
	Node* node = calloc(1, sizeof(Node));
	node->rhs = NULL;
	node->lhs = NULL;
	node->val = val;
	node->kind = ND_NUM;
	return node;
}

Node* createNewNode(Node* lhs, Node* rhs, char* kind)
{
	Node* node = calloc(1, sizeof(Node));
	node->lhs = lhs;
	node->rhs = rhs;
	node->kind = kind;
	return node;
}