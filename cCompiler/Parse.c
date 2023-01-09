#include "Compiler.h"



Node* parse(Token** curToken, Cabinet** curCabinet)
{
	printf("パース開始\n");
	Node* node = NULL;


	while ((*curToken)->kind != TK_END)
	{
		if ((*curToken)->kind == TK_SYMBOL)
		{
			if (isSameString((*curToken)->str, "}"))
			{
				printf("parse:}\n");
				break;
			}
		}

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
			if (isSameString((*curToken)->str, "if"))
			{
				printf("this okenomi\n");
				node = ifStatement(curToken, curCabinet, node);
				printf("if ended\n");
				printf("node kind is %s\n", node->kind);
				continue;
			}
			if (isSameString((*curToken)->str, "return"))
			{
				printf("parse return\n");
				node = retStatement(curToken, curCabinet, node);
				continue;
			}
			//変数の初期化の処理
			if (isVariableType(curToken))
			{
				node = initializetion(curToken, curCabinet, node);
				continue;
			}
			//変数の代入の処理
			if (serchCabinet(curCabinet,(*curToken)->str))
			{
				printf("assignState\n");
				node = assign(curToken, curCabinet, node);
				
				printf("parse:assign returned\n");printf("%s\n", (*curToken)->str);
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
	if ((*curToken)->kind == TK_STR)
	{
		printf("primary:%s\n", (*curToken)->str);
		node = createStrNode((*curToken)->str, ND_VAL);
		(*curToken) = (*curToken)->next;
		printf("primary:return\n");
		return node;
	}
}
Node* add(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = mul(curToken, curCabinet, curNode);
	printf("add:mul returned\n");
	while ((*curToken)->kind == TK_SYMBOL)
	{
		printf("add:(*curToken)->kind = TK_SYMBOL\n");
		if (isSameString((*curToken)->str, "+"))
		{
			printf("add:+\n");
			(*curToken) = (*curToken)->next;
			Node* rhsNode = mul(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_ADD);

			continue;
		}
		if (isSameString((*curToken)->str, "-"))
		{
			printf("add:-\n");
			(*curToken) = (*curToken)->next;
			Node* rhsNode = mul(curToken, curCabinet, curNode);
			node = createNewNode(node, rhsNode, ND_SUB);
			continue;
		}
		
		printf("add:while:break\n");
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
	printf("add:return\n");
	return ptr;
}

int hierarchyStep = 0;

Node* retStatement(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* node = calloc(1, sizeof(Node));
	(*curToken) = (*curToken)->next;
	node->kind = ND_RETURN;
	node->rhs = NULL;
	node->lhs = add(curToken, curCabinet, NULL);
	node->lhs->lhs = curNode;
	node->lhs->rhs = NULL;
	return node;
}

Node* ifStatement(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	(*curToken) = (*curToken)->next;
	(*curToken) = (*curToken)->next;
	Node* conditionNode = condition(curToken, curCabinet, NULL);
	(*curToken) = (*curToken)->next;
	(*curToken) = (*curToken)->next;
	Node* syntaxNode = parse(curToken, curCabinet, NULL);
	Node* jointNode = calloc(1, sizeof(Node));
	jointNode->lhs = syntaxNode;
	jointNode->kind = ND_IGNORE;

	printf("parse returned here\n");
	Node* ifNode = createNewNode(conditionNode, jointNode, ND_IF);
	ifNode->hierarchy = hierarchyStep;
	hierarchyStep += 2;
	//elseの探索
	if (((*curToken)->next->kind == TK_STR))
	{
		if (isSameString((*curToken)->next->str, "else"))
		{
			(*curToken) = (*curToken)->next;
				(*curToken) = (*curToken)->next;
				(*curToken) = (*curToken)->next;
				Node* elseSyntaxNode = parse(curToken, curCabinet, NULL);
				jointNode->rhs = elseSyntaxNode;
				(*curToken) = (*curToken)->next;
				Node* ptr = conditionNode;

				while (conditionNode != NULL)
				{
					if (conditionNode->lhs == NULL)
					{
						break;
					}
					conditionNode = conditionNode->lhs;
				}
			conditionNode->lhs = curNode;
			printf("%s\n", ifNode->kind);
			return ifNode;
		}
		else
		{
			printf("hereherehre\n");
			(*curToken) = (*curToken)->next;
			jointNode->rhs = NULL;
			return ifNode;
		}
	}
	else
	{
		printf("hereherehre\n");
		(*curToken) = (*curToken)->next;
		jointNode->rhs = NULL;
		return ifNode;
	}


	printf("else statement was not exist\n");
	exit(1);

}

Node* condition(Token** curToken, Cabinet** curCabinet, Node* curNode)
{
	Node* conditionNode = NULL;

	//先読み
	if (isSameString((*curToken)->next->str, "=="))
	{
		printf("condition:==\n");
		conditionNode = createConditionNode(curToken, curCabinet, curNode,ND_EQU);
	}
	else if (isSameString((*curToken)->next->str, ">"))
	{
		conditionNode = createConditionNode(curToken, curCabinet, curNode,ND_BS);
		printf("condition:>\n");
	}
	else if (isSameString((*curToken)->next->str, "<"))
	{
		printf("condition:<\n");
		conditionNode = createConditionNode(curToken, curCabinet, curNode, ND_SB);
	}
	else
	{
		printf("例外\n");
	}
	
	return conditionNode;
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
	printf("assign:%s\n", (*curToken)->str);
	node->rhs = add(curToken, curCabinet, NULL);
	
	return node;
}