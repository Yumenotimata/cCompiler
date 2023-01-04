#ifndef __CODE_GENERATOR_TOOLS_H
#define __CODE_GENERATOR_TOOLS_H
#include "Compiler.h"

void genCalculation(Node* curNode);
void genCalculation_s(Node* curNode);
void genInitializetion(Node* curNode, Cabinet** curCabinet);
void genAssign(Node* curNode, Cabinet** curCabinet);
bool ifCalculation(Node* curNode);
bool isValue(Node* curNode);

#endif
