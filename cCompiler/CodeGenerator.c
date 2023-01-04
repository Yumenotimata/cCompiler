#include "Compiler.h"

void GenerateCode(Node* curNode, Cabinet** curCabinet)
{
	if (curNode == NULL)
	{
		return;
	}

	GenerateCode(curNode->lhs, curCabinet);
	GenerateCode(curNode->rhs, curCabinet);

	printf("%s\n", curNode->kind);

	/*if (ifCalculation(curNode))
	{
		genCalculation(curNode);
		return;
	}*/

	if (curNode->kind == ND_INIT)
	{
		genInitializetion(curNode, curCabinet);
		return;
	}
	if (curNode->kind == ND_ASSIGN)
	{
		genAssign(curNode, curCabinet);
		return;
	}
		
	return;
}