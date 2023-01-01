#include "Compiler.h"

void genCalculation(Node* curNode)
{
	if (curNode->lhs->kind != ND_NUM)
	{
		printf("	pop rax\n");
	}
	else
	{
		printf("	mov rax,%d\n", curNode->lhs->val);
	}

	if (curNode->kind == ND_KAKE)
	{
		if (curNode->rhs->kind != ND_NUM)
		{
			printf("	pop rdi\n");
		}
		else
		{
			printf("	mov rdi,%d\n", curNode->rhs->val);
		}

		printf("	mul rax,rdi\n");
		printf("	push rax\n");
		return;
	}
	if (curNode->kind == ND_WARI)
	{
		if (curNode->rhs->kind != ND_NUM)
		{
			printf("	pop rdi\n");
		}
		else
		{
			printf("	mov rdi,%d\n", curNode->rhs->val);
		}

		printf("	div rax,rdi\n");
		printf("	push rax\n");
		return;
	}
	if (curNode->kind == ND_ADD)
	{
		if (curNode->rhs->kind != ND_NUM)
		{
			printf("	pop rdi\n");
			printf("	add rdi,rax\n");
			printf("	push rdi\n");
		}
		else
		{
			printf("	mov rdi,%d\n", curNode->rhs->val);
			printf("	add rax,rdi\n");
			printf("	push rax\n");
		}
		return;
	}
	if (curNode->kind == ND_SUB)
	{
		if (curNode->rhs->kind != ND_NUM)
		{
			printf("	pop rdi\n");
			printf("	sub rdi,rax\n");
			printf("	push rdi\n");
		}
		else
		{
			printf("	mov rdi,%d\n", curNode->rhs->val);
			printf("	sub rax,rdi\n");
			printf("	push rax\n");
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