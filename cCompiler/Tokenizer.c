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
			printf("%d\n",curToken->val);
			continue;
		}
		if (isSymbol(&code))
		{
			setSymToken(&curToken, &code);
			printf("isSymbol:%s\n", curToken->str);
			makeNewToken(&curToken);
			continue;
		}
		if (isString(&code))
		{
			setStrToken(&curToken, &code);
			printf("isString:%s\n", curToken->str);
			makeNewToken(&curToken);
			
			continue;
		}
		//(code)++;
	}
	curToken->kind = TK_END;
	printf("トークナイズ終了\n");
	free(ptr);
	fclose(fp);

	return head;
}