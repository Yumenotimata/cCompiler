#include "Compiler.h"

void genCalculation_s(Node* curNode,Cabinet **curCabinet)
{
	if (curNode == NULL)
	{
		return;
	}

	genCalculation_s(curNode->rhs,curCabinet);
	genCalculation_s(curNode->lhs,curCabinet);

	if (ifCalculation(curNode))
	{
		genCalculation(curNode,curCabinet);
		return;
	}

	return;
}

void genCalculation_s_s(Node* curNode, Cabinet** curCabinet)
{
	if (curNode == NULL)
	{
		return;
	}
	if (curNode->kind == ND_VAL)
	{
		Cabinet* cabBuffer = *curCabinet;
		handleCabinet(curCabinet, curNode->str);
		printf("	push [rbp-%d]\n", (*curCabinet)->offset * 8);
		*curCabinet = cabBuffer;
		return;
	}
	if (curNode->kind == ND_NUM)
	{
		printf("	push %d\n", curNode->val);
		return;
	}

	genCalculation_s_s(curNode->lhs,curCabinet);
	genCalculation_s_s(curNode->rhs,curCabinet);

	printf("genCalculation_s_s:%s\n", curNode->kind);

	printf("	pop rdi\n");
	printf("	pop rax\n");

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

void genCalculation(Node* curNode,Cabinet **curCabinet)
{
	if (curNode->lhs->kind == ND_VAL)
	{
		Cabinet* cabBuffer = *curCabinet;
		handleCabinet(curCabinet, curNode->lhs->str);
		printf("	mov rax,[rbp-%d]\n", (*curCabinet)->offset * 8);
		*curCabinet = cabBuffer;
	}
	else if (curNode->lhs->kind != ND_NUM)
	{
		printf("	pop rax\n");
	}
	else
	{

		printf("	mov rax,%d\n", curNode->lhs->val);
	}

	if (curNode->rhs->kind == ND_VAL)
	{
		printf("kind is%s\n", curNode->rhs->str);
		Cabinet* cabBuffer = *curCabinet;
		handleCabinet(curCabinet, curNode->rhs->str);
		printf("	mov rdi,[rbp-%d]\n", (*curCabinet)->offset * 8);
		*curCabinet = cabBuffer;
	}
	else if (curNode->rhs->kind != ND_NUM)
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

	bool isValue(Node *curNode)
	{
		if (curNode->kind == ND_NUM && curNode->lhs == NULL && curNode->rhs == NULL)
		{
			return true;
		}

		return false;
	}

	void genInitializetion(Node* curNode, Cabinet** curCabinet)
	{
		//printf("‰Šú‰»\n");
		printf("	mov [rbp-%d],0\n", curNode->rhs->cabinet->offset * 8);
		return;
	}

	void genAssign(Node* curNode, Cabinet** curCabinet)
	{
		printf("genAssign:curNode->rhs->kind = %s\n", curNode->rhs->kind);
		if (curNode->rhs->kind != ND_NUM)
		{
			genCalculation_s_s(curNode->rhs, curCabinet);
			printf("	pop rax\n");
		}
		else
		{
			//printf("heere\n");
			printf("	mov rax,%d\n", curNode->rhs->val);
		}
		Cabinet* cabBuffer = *curCabinet;
		//printf("error point %s\n", curNode->lhs->str);
		handleCabinet(curCabinet, curNode->lhs->str);
		printf("	mov [rbp-%d],rax\n",(*curCabinet)->offset * 8);
		*curCabinet = cabBuffer;
		return ;
	}