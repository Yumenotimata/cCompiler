#include "Compiler.h"

Cabinet* initCabinet(void)
{
	Cabinet* cabinet = calloc(1, sizeof(Cabinet));
	cabinet->head = cabinet;
	cabinet->offset = 1;
	cabinet->next = NULL;

	return cabinet;
}

void setCabinet(Cabinet** curCabinet, char* name)
{
	(*curCabinet)->name = name;
}

void makeNewCabinet(Cabinet** curCabinet)
{
	Cabinet* newCabinet = calloc(1, sizeof(Cabinet));
	
	(*curCabinet)->next = newCabinet;
	newCabinet->head = (*curCabinet)->head;
	newCabinet->offset = ((*curCabinet)->offset) + 1;
	(*curCabinet) = newCabinet;
}
bool serchCabinet(Cabinet** curCabinet, char* serchName)
{
	//エントリポイントの保持
	Cabinet* bufCabinet = calloc(1, sizeof(Cabinet));
	bufCabinet = *curCabinet;

	(*curCabinet) = (*curCabinet)->head;
	while ((*curCabinet) != NULL)
	{
		if ((*curCabinet)->name != NULL)
		{
			if (!memcmp((*curCabinet)->name, serchName, strlen(serchName)))
			{
				//エントリポイントの復元
				(*curCabinet) = bufCabinet;
				return true;
			}
		}
		else
		{
			printf("Cabinetの値が(null)です。\n");
			(*curCabinet) = bufCabinet;
			return false;
		}
		(*curCabinet) = (*curCabinet)->next;
	}
	printf("サーチエラー：'%s'は見つかりませんでした\n");
	(*curCabinet) = bufCabinet;
	return false;
}