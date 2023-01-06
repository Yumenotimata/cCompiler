#include "Compiler.h"

Token* tokenize(FILE* fp)
{
	char* code = calloc(TEXT_SIZE, sizeof(char));
	char* ptr = code;
	fp2str(code, fp);

	printf("�g�[�N�i�C�Y�J�n\n");
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
	printf("�g�[�N�i�C�Y�I��\n");
	free(ptr);
	fclose(fp);

	return head;
}