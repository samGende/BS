#include "mp3.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void idTagFile(const char *fileName,char *comment)
{
	if (!strncmp(".", fileName, 2) || !strncmp("..", fileName, 3))
               	return;

	//Prüft das die Datei um ein mp3 handelt.
	if (strncmp(fileName + strlen(fileName) - 4, ".mp3", 4)) {
			printf("%s: ausgelassen\n", fileName);
			return;
 	}

	struct stat fileInfo;

	if(stat(fileName, &fileInfo) != 0){
		//Fehler mit stat
		perror("Fehler mit stat anruf");
		return;
	}

	if(S_ISREG(fileInfo.st_mode) == 0){
		printf("Invalid File type %s\n", fileName);
		return;
	}

	//open file
	FILE* file;
	file = fopen(fileName, "r");
	if(file == NULL){
		perror("Fehler mit fopen");
		return;
	}

	//move to datasegment in File
	if(fseek(file, -128L, SEEK_END) != 0){
		//Fehler fseek
		perror("Fehler mit fseek");
		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}

	char buffer[128];
	if(fread(buffer, 1, 128, file) != ID3_SIZE){
		//Fehler, denn nicht alle Bytes werden gelesen.
		printf("Error beim lesen\n");

		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}

	if(strncmp(buffer, "TAG",3) != 0){
		printf("TAG not found in %s\n", fileName);

		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}

	//Speichern buffer in mp3/////
	struct mp3file *mp3;
	mp3 = bytesToIdTag(buffer);

	printTag(mp3);

	//Datei und Speicher frei geben
	free(mp3);
	if(fclose(file) != 0){
		perror("Error mit fclose");
		return;
	}
}

/* Die Informationen im Puffer, auf den buffer verweist, *
 * wird in einem struct abgelegt.			 */
struct mp3file* bytesToIdTag(char *buffer)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	struct mp3file *mp3;
	mp3 = malloc(sizeof(struct mp3file));
	if (mp3 == NULL){
		//malloc Fehler
		printf("malloc Fehler\n");
		return NULL;
	}	

	int i = 3;
	int j = 0;

	//title 3-32
	while (i < 33){
		mp3->titel[j] = buffer[i];
		i++;
		j++;
	}

	//interpret 33-62
	j = 0;
	while (i < 63){
		mp3->interpret[j] = buffer[i];
		i++;
		j++;
	}

	//album 63-92
	j = 0;
	while (i < 93){
		mp3->album[j] = buffer[i];
		i++;
		j++;
	}

	//jahr 93-96
	j = 0;
	while (i < 97){
		mp3->jahr[j] = buffer[i];
		i++;
		j++;
	}

	//kommentar 97-126
	j = 0;
	while (i < 127){
		mp3->kommentar[j] = buffer[i];
		i++;
		j++;
	}
	
	//genere 127-128
	mp3->genre = buffer[i];

	return mp3;
}
/*				       *
 * Es werden die in dem struct mp3file *
 * abgelegten Informationen ausgegeben *
 *				       */
void printTag(struct mp3file *mp3)
{
	printf("Titel: %s\n", mp3->titel);
	printf("Album: %s\n", mp3->album);
	printf("Kommentar: %s\n", mp3->kommentar);
	printf("Jahr: %s\n", mp3->jahr);
	printf("interpret: %s\n", mp3->interpret);
	printf("Genre: %s\n", translateGenre(mp3->genre));

}
