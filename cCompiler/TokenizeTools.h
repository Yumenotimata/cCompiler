#ifndef __TOKENIZE_TOOLS_H
#define __TOKENIZE_TOOLS_H

void fp2str(char* str, FILE* fp);
void skipBlank(char** code);
void setNumToken(Token** curToken, char** code);
void setStrToken(Token** curToken, char** code);
void setSymToken(Token** curToken, char** code);
void makeNewToken(Token** curToken);
bool isSymbol(char** input);
char* getSymbol(char** code);
bool isString(char** input);
char* getString(char** code);

#endif