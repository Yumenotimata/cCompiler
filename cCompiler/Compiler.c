#include "Compiler.h"

int main(void)
{
	FILE* text;
	fopen_s(&text,"Code.c","r");

	Cabinet* cabinet = initCabinet();
	Token* token = tokenize(text);
	Token* ptr = token;
	while (token != NULL)
	{
		if (token->kind == TK_SYMBOL ||token->kind == TK_STR)
		{
			printf("%s\n", token->str);
		}
		else
		{
			printf("%d\n", token->val);
		}
		token = token->next;
	}
	token = ptr;
	Node* node = parse(&token,&cabinet);
	printf("gen code\n");
	GenerateCode(node, &cabinet);
	return 0;
}