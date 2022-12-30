#include "Compiler.h"

void fp2str(char* str, FILE* fp)
{
	printf("�t�@�C���̓ǂݍ��݊J�n\n");
	char c;
	while ((c = fgetc(fp))!=EOF)
	{
		if (str == NULL)
		{
			printf("�A�N�Z�X�ᔽ:�t�@�C���̓ǂݍ��݃T�C�Y��ύX���Ă�������\n");
			exit(1);
		}
		*str = c;
		str++;
	}
	*str = '\0';
	printf("�t�@�C���̓ǂݍ��ݏI��\n");
}

void setNumToken(Token** curToken, char** code)
{
	(*curToken)->kind = TK_NUM;
	(*curToken)->val = strtol(*code, code, 10);
}
void makeNewToken(Token** curToken)
{
	Token* nextToken = calloc(1, sizeof(Token));
	(*curToken)->next = nextToken;
	(*curToken) = nextToken;
}
void skipBlank(char** code)
{
	while (isspace(**code))
	{
		(*code)++;
	}
}
bool isSymbol(char** input)
{
	if ((**input) == '+')
	{
		return true;
	}
	else if ((**input) == '*')
	{
		return true;
	}
	else if ((**input) == '-')
	{
		return true;
	}
	else if ((**input) == '/')
	{
		return true;
	}
	else if ((**input) == '=')
	{
		return true;
	}

	return false;
}
void setStrToken(Token** curToken, char** code)
{
	
}
void setSymToken(Token** curToken, char** code)
{
	(*curToken)->kind = TK_SYMBOL;
	(*curToken)->str = getSymbol(code);
}
char* getSymbol(char** code)
{
	char* str = calloc(1, sizeof(MAX_SYMBOL_SIZE + 1));
	char* head = str;

	while (isSymbol(code))
	{
		(*str) = (**code);
		str++;
		(*code)++;
	}

	*str = '\0';
	return head;
}