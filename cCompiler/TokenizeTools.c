#include "Compiler.h"

void fp2str(char* str, FILE* fp)
{
	printf("ファイルの読み込み開始\n");
	char c;
	while ((c = fgetc(fp))!=EOF)
	{
		if (str == NULL)
		{
			printf("アクセス違反:ファイルの読み込みサイズを変更してください\n");
			exit(1);
		}
		*str = c;
		str++;
	}
	*str = '\0';
	printf("ファイルの読み込み終了\n");
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