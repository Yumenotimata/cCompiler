#include "Compiler.h"

Token* tokenize(FILE* fp)
{
	char* code = calloc(TEXT_SIZE,sizeof(char));
	fp2str(code, fp);

	printf("�g�[�N�i�C�Y�J�n\n");
	Token* curToken = calloc(1,sizeof(Token));
	while (code != NULL)
	{
		skipBlank(&code);
		//���l�̏ꍇ
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
	printf("�g�[�N�i�C�Y�I��\n");
	free(code);
	fclose(fp);
}