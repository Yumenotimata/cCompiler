#include "Compiler.h"

bool isSameString(char *string,char *cmpString)
{
	if (!memcmp(string, cmpString, strlen(cmpString)))
	{
		return true;
	}

	return false;

}

bool isVariableType(Token **curToken)
{
	for(int i = 0; i < TYPE_NUMBER; i++)
	{
		if (isSameString((*curToken)->str, typeNameList[i]))
		{
			printf("%s and %s are same string\n", (*curToken)->str, typeNameList[i]);
			return true;
		}
	}
	printf("return false\n");
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

Node* createStrNode(char *str, char* kind)
{
	Node* node = calloc(1, sizeof(Node));
	node->rhs = NULL;
	node->lhs = NULL;
	node->str = str;
	node->kind = kind;
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

Node* createNewTypeNode(Node* lhs, Node* rhs, char* typeName)
{
	Node* node = calloc(1, sizeof(Node));
	node->lhs = lhs;
	node->rhs = rhs;
	node->kind = ND_TYPE;
	node->str = typeName;
	return node;
}

char* getTypeName(Token** curToken)
{
	for (int i = 0; i < TYPE_NUMBER; i++)
	{
		if (isSameString((*curToken)->str, typeNameList[i]))
		{
			printf("return %s\n", typeNameList[i]);
			return typeNameList[i];
		}
		printf("ŠÖ”:getTypeName:looking for:%s\n", (*curToken)->str);
	}
	printf("\nŠÖ”:getTypeName:‘¶Ý‚µ‚È‚¢Œ^‚Å‚·\n");
}

Node* createVariableNode(Token** opToken, Cabinet** curCab)
{
	Node* retNode = calloc(1, sizeof(Node));
	setCabinet(curCab, (*opToken)->str);
	retNode->cabinet = (*curCab);
	retNode->kind = ND_VAL;
	retNode->rhs = NULL;
	retNode->lhs = NULL;
	makeNewCabinet(curCab);

	return retNode;
}