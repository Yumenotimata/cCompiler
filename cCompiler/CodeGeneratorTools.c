#include "Compiler.h"

void genCalculation(Node* curNode)
{
	if (curNode->lhs->kind != ND_NUM)
	{
		printf("	pop rax\n");
		if (curNode->rhs->kind != ND_NUM)
		{

		}
	}
}
	
	bool ifCalculation(Node * curNode)
	{
		if (curNode->kind == ND_KAKE || curNode->kind == ND_WARI|| curNode->kind == ND_ADD|| curNode->kind == ND_SUB)
		{
			return true;
		}

		return false;
	}