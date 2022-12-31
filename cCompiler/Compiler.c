#include "Compiler.h"

int main(void)
{
	FILE* text;
	fopen_s(&text,"Code.txt","r");

	Cabinet* cabinet = initCabinet();
	Token* token = tokenize(text);
	Node* node = parse(&token,&cabinet);
	return 0;
}