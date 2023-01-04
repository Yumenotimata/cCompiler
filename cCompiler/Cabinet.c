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
			exit(1);
			return false;
		}
		(*curCabinet) = (*curCabinet)->next;
	}
	printf("サーチエラー：'%s'は見つかりませんでした\n");
	exit(1);
	(*curCabinet) = bufCabinet;
	return false;
}

bool handleCabinet(Cabinet** curCab, char* serchName)
{
	(*curCab) = (*curCab)->head;
	while ((*curCab) != NULL)
	{
		if ((*curCab)->name != NULL)
		{
			if (!memcmp((*curCab)->name, serchName, strlen(serchName)))
			{
				//printf("serch was successeful\n");
				return true;
			}
		}
		else
		{
			printf("\n\nserch error\n\n");
			exit(1);
		}
		(*curCab) = (*curCab)->next;
	}
	printf("serch failed:'%s' was not found", serchName);
	exit(1);

	return false;
}