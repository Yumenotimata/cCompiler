#include "Compiler.h"

Token* tokenize(FILE* fp)
{
	char* code = calloc(TEXT_SIZE, sizeof(char));
	char* ptr = code;
	fp2str(code, fp);

	printf("トークナイズ開始\n");
	Token* curToken = calloc(1,sizeof(Token));
	Token* head = curToken;
	while ((*code) != '\0')
	{
		skipBlank(&code);

		if (isdigit(*code))
		{
			setNumToken(&curToken,&code);
			makeNewToken(&curToken);
			continue;
		}
		if (isSymbol(&code))
		{
			setSymToken(&curToken, &code);
			makeNewToken(&curToken);
			continue;
		}
	}
	printf("トークナイズ終了\n");
	free(ptr);
	fclose(fp);

	return head;
}