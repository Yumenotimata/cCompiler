#ifndef __PARSE_TOOLS_H
#define __PARSE_TOOLS_H

bool isSameString(char* string, char* cmpString);
bool isVariableType(Token **curToken);
Node* createNumNode(int val);
Node* createNewNode(Node* lhs, Node* rhs, char* kind);
char* getTypeName(Token** curToken);
Node* createNewTypeNode(Node* lhs, Node* rhs, char* typeName);
Node* createVariableNode(Token** opToken, Cabinet** curCab);
Node* createStrNode(char* str, char* kind);

#endif
