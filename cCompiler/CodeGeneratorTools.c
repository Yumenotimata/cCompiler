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

	if (curNode->rhs->kind != ND_NUM)
	{
		printf("	pop rdi\n");
	}
	else
	{
		printf("	mov rdi,%d\n", curNode->rhs->val);
	}

	//—¼•Ó‚ª”‚Å‚Í‚È‚¢‚Æ‚«‚Ì—áŠOˆ—
	if (curNode->lhs->kind != ND_NUM && curNode->rhs->kind != ND_NUM)
	{
		if (curNode->kind == ND_KAKE)
		{
			printf("	mul rdi,rax\n");
			printf("	push rdi\n");
			return;
		}
		if (curNode->kind == ND_WARI)
		{
			printf("	div rdi,rax\n");
			printf("	push rdi\n");
			return;
		}
		if (curNode->kind == ND_ADD)
		{
			printf("	add rdi,rax\n");
			printf("	push rdi\n");
			return;
		}
		if (curNode->kind == ND_SUB)
		{
			printf("	sub rdi,rax\n");
			printf("	push rdi\n");
			return;
		}
	}
	else//’Êíˆ—
	{
		if (curNode->kind == ND_KAKE)
		{
			printf("	mul rax,rdi\n");
			printf("	push rax\n");
			return;
		}
		if (curNode->kind == ND_WARI)
		{
			printf("	div rax,rdi\n");
			printf("	push rax\n");
			return;
		}
		if (curNode->kind == ND_ADD)
		{
			printf("	add rax,rdi\n");
			printf("	push rax\n");
			return;
		}
		if (curNode->kind == ND_SUB)
		{
			printf("	sub rax,rdi\n");
			printf("	push rax\n");
			return;
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

	void genInitializetion(Node* curNode, Cabinet** curCabinet)
	{
		printf("‰Šú‰»\n");
		printf("	mov [rbp-%d],0", curNode->rhs->cabinet->offset * 8);
		return;
	}

	void genAssign(Node* curNode, Cabinet** curCabinet)
	{
		printf("	pop rax\n");
		Cabinet* cabBuffer = *curCabinet;
		handleCabinet(curCabinet, curNode->lhs->str);
		printf("	mov [rbp-%d],rax\n",(*curCabinet)->offset * 8);
		*curCabinet = cabBuffer;
		return ;
	}