#include "Compiler.h"

void GenerateCode(Node* curNode, Cabinet** curCabinet)
{
	if (curNode == NULL)
	{
		return;
	}

	GenerateCode(curNode->lhs, curCabinet);
	GenerateCode(curNode->rhs, curCabinet);

	if (ifCalculation(curNode))
	{
		genCalculation(curNode);
		return;
	}
		
	return;
}