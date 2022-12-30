#include "Compiler.h"

int main(void)
{
	FILE* text;
	fopen_s(&text,"Code.txt","r");

	Token* token = tokenize(text);

	return 0;
}