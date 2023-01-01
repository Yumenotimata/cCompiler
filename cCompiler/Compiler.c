#include "Compiler.h"

int main(void)
{
	FILE* text;
	fopen_s(&text,"Code.txt","r");

	Cabinet* cabinet = initCabinet();
	Token* token = tokenize(text);
	Token* ptr = token;
	while (token != NULL)
	{
		if (token->kind == TK_SYMBOL)
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
	GenerateCode(node, &cabinet);
	return 0;
}