#ifndef __CABINET_H
#define __CABINET_H

typedef struct Cabinet Cabinet;
struct Cabinet
{
	Cabinet* next;
	Cabinet* head;
	int offset;
	char* name;
};

Cabinet* initCabinet(void);
void setCabinet(Cabinet** curCabinet, char* name);
void makeNewCabinet(Cabinet** curCabinet);
bool serchCabinet(Cabinet** curCabinet, char* serchName);
bool handleCabinet(Cabinet** curCab, char* serchName);

#endif
