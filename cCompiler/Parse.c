#include "Compiler.h"

Node* parse(Token** curToken, Cabinet** curCabinet)
{
	printf("�p�[�X�J�n\n");
	Node* node = NULL;

	while ((*curToken)->kind != TK_END)
	{
		if ((*curToken)->kind == TK_NUM)
		{
			//��ǂ�
			if ((*curToken)->next->kind == TK_SYMBOL)
			{
				//�l�����Z
				node = add(curToken, curCabinet,node);
			}
		}
		if((*curToken)->kind == TK_SYMBOL)
		{
			if (isSameString((*curToken)->str, "("))
			{//(����n�܂鎮�̗�O����
				node = add(curToken, curCabinet, node);
			}
			if (isSameString((*curToken)->str, ";"))
			{
				(*curToken) = (*curToken)->next;
			}		
		}

	}

	
	printf("�p�[�X�I��\n");
	return node;
}

Node* mul(Token** curToken, Cabinet** curCabinet,Node *curNode)
{
	Node* node = primary(curToken,curCabinet,curNode);
	
	while ((*curToken)->kind == TK_SYMBOL)
	{
		if (isSameString((*curToken)->str, "*"))
		{
			(*curToken) = (*curToken)->next;
			Node* rhsNode = primary(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_KAKE);

			continue;
		}
		if (isSameString((*curToken)->str, "/"))
		{
			(*curToken) = (*curToken)->next;
			Node* rhsNode = primary(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_WARI);

			continue;
		}
		
		
		break;
	}
	return node;
}
Node* primary(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = NULL;
	if ((*curToken)->kind == TK_SYMBOL)
	{
		if (isSameString((*curToken)->str, "("))
		{
			(*curToken) = (*curToken)->next;
			node = add(curToken, curCabinet, curNode);
			printf("returned %s\n", (*curToken)->str);
			(*curToken) = (*curToken)->next;
			return node;
		}
		else
		{
			printf("parse error\n");
			exit(1);
		}
	}
	if ((*curToken)->kind == TK_NUM)
	{

		node = createNumNode((*curToken)->val);
		(*curToken) = (*curToken)->next;
		return node;
	}
}
Node* add(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = mul(curToken, curCabinet, curNode);

	while ((*curToken)->kind == TK_SYMBOL)
	{
		if (isSameString((*curToken)->str, "+"))
		{
			(*curToken) = (*curToken)->next;
			Node* rhsNode = mul(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_ADD);

			continue;
		}
		if (isSameString((*curToken)->str, "-"))
		{
			(*curToken) = (*curToken)->next;
			Node* rhsNode = mul(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_SUB);
			continue;
		}
		
		
		break;
		
	}
	//�e���߂��Ȃ��铭��
	Node* ptr = node;
	while (node != NULL)
	{
		if (node->lhs == NULL)
		{
			break;
		}
		node = node->lhs;
	}
	node->lhs = curNode;

	return ptr;
}