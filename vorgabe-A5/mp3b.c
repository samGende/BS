#include "mp3.h"
#include <dirent.h>

void idTagDir(const char *dirName, char *comment)
{
	DIR *dir = NULL;
	struct dirent *entry = NULL;

	if (!strncmp(".", dirName, 2) || !strncmp("..", dirName, 3))
               	return;

	//Verzeichnis öffnen
	dir = opendir(dirName);
	if(!dir){
		//Fehler
		perror("Könnte Verzeichnis nicht öffnen");
		return;
	}
	printf("%s: Betrete Verzeichnis ...\n", dirName);

	//Liest alle Dateien in Verzeichnis
	while ((entry = readdir(dir))){

		//Prüft das die Datei um ein mp3 handelt.
		if (strncmp(entry->d_name + strlen(entry->d_name) - 4, ".mp3", 4)) {
				//Datei ist kein mp3
				continue;
		}

		//fileName = dirName/file.mp3
		char fileName[1024];
		strncpy(fileName, dirName,1024);
		strncat(fileName, "/", 1);
		strncat(fileName, entry->d_name, strlen(entry->d_name));

		//TAG Information ausgeben
		printf("Datei: %s\n", entry->d_name);
		idTagFile(fileName, NULL);
		printf("\n");	
	}
	

	//Verzeichnis verlassen
	if (closedir(dir) == -1){
		//Fehler
		perror("Könnte Verzeichnis nicht verlassen");
		return;
	}

	printf("%s: Verlasse Verzeichnis ...\n", dirName);
}
