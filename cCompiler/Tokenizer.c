#include "Compiler.h"

Token* tokenize(FILE* fp)
{
	char* code = calloc(TEXT_SIZE,sizeof(char));
	fp2str(code, fp);

	printf("トークナイズ開始\n");
	Token* curToken = calloc(1,sizeof(Token));
	while (code != NULL)
	{
		skipBlank(&code);
		//数値の場合
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
	free(code);
	fclose(fp);
}