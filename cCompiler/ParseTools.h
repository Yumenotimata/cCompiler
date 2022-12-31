#ifndef __PARSE_TOOLS_H
#define __PARSE_TOOLS_H

bool isSameString(char* string, char* cmpString);
Node* createNumNode(int val);
Node* createNewNode(Node* lhs, Node* rhs, char* kind);
#endif
