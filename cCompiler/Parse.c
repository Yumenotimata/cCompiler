#include "Compiler.h"

Node* parse(Token** curToken, Cabinet** curCabinet)
{
	printf("パース開始\n");
	Node* node = NULL;

	//プロローグ

	while ((*curToken)->kind != TK_END)
	{
		if ((*curToken)->kind == TK_NUM)
		{
			//先読み
			if ((*curToken)->next->kind == TK_SYMBOL)
			{
				//四則演算
				node = add(curToken, curCabinet,node);
			}
		}


		if((*curToken)->kind == TK_SYMBOL)
		{
			if (isSameString((*curToken)->str, "("))
			{//(から始まる式の例外処理
				node = add(curToken, curCabinet, node);
				
			}
			if (isSameString((*curToken)->str, ";"))
			{
				(*curToken) = (*curToken)->next;
			}		
		}


		if ((*curToken)->kind == TK_STR)
		{
			//変数の初期化の処理
			if (isVariableType(curToken))
			{
				node = initializetion(curToken, curCabinet, node);
				continue;
			}
			//変数の代入の処理
			if (serchCabinet(curCabinet,(*curToken)->str))
			{
				printf("ok\n");
				node = assign(curToken, curCabinet, node);
				continue;
			}

		}

	}

	
	printf("パース終了\n");
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
	//各分節をつなげる働き
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

Node* initializetion(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = calloc(1, sizeof(Node));
	node->kind = ND_INIT;
	node->lhs = createNewTypeNode(curNode, NULL, getTypeName(curToken));

	(*curToken) = (*curToken)->next;
	node->rhs = createVariableNode(curToken,curCabinet);
	(*curToken) = (*curToken)->next;
	
	
	return node;
}

Node* assign(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = calloc(1, sizeof(Node));	
	node->kind = ND_ASSIGN;
	node->lhs = createStrNode((*curToken)->str,ND_VAL);
	node->lhs->lhs = curNode;
	node->lhs->rhs = NULL;
	(*curToken) = (*curToken)->next;
	(*curToken) = (*curToken)->next;
	node->rhs = add(curToken, curCabinet, NULL);
	
	return node;
}