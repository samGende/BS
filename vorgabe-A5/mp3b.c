#include "mp3.h"

void idTagDir(const char *dirName, char *comment)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */

	if (!strncmp(".", dirName, 2) || !strncmp("..", dirName, 3))
               	return;
	
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */

	printf("%s: Betrete Verzeichnis ...\n", dirName);

	/* HIER MUESST IHR EUREN CODE EINFUEGEN */

	printf("%s: Verlasse Verzeichnis ...\n", dirName);
}
