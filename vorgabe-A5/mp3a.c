#include "mp3.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void idTagFile(const char *fileName,char *comment)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	struct stat fileInfo;

	if(stat(fileName, &fileInfo) != 0){
		//Fehler mit stat
		perror("Fehler mit stat anruf");
		return;
	}


	long size = fileInfo.st_size;
	if(S_ISREG(fileInfo.st_mode) != 0){
		printf("is regular file\n");
	}else {
		printf("Invalid File type %s\n", fileName);
		return;
	}
	printf("%li\n", size);



	if (!strncmp(".", fileName, 2) || !strncmp("..", fileName, 3))
               	return;

	/* HIER MUESST IHR EUREN CODE EINFUEGEN */

	//Prüft das die Datei um ein mp3 handelt.
	if (strncmp(fileName + strlen(fileName) - 4, ".mp3", 4)) {
			printf("%s: ausgelassen\n", fileName);
			return;
 	}

	//open file
	FILE* file;
	file = fopen(fileName, 'r');
	if(file == NULL){
		perror("Fehler mit fopen");
		return;
	}

	//move to datasegment in File
	if(fseek(file, size - 128, SEEK_SET) != 0){
		//Fehler fseek
		perror("Fehler mit fseek");
		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}


	char buffer[128];
	if(fread(buffer, 1, 128, file) != 128){
		//Fehler, denn nicht alle Bytes werden gelesen.
		printf("Error beim lesen\n");

		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}

	printf("%s\n", buffer);

	if(strncmp(buffer, "TAG",3) != 0){
		printf("TAG not found in %s\n", fileName);

		if(fclose(file) != 0){
			perror("Error mit fclose");
		}
		return;
	}

	struct mp3file mp3;

	int i = 3;

	while (i < 33){
		printf("%c\n", buffer[i]);
		mp3.titel[i] = buffer[i];
		mp3.titel[i] ='a';
		printf("%c\n", mp3.titel[i]);
		i++;
	}

	while (i < 63){
		mp3.interpret[i] = buffer[i];
		i++;
	}

	while (i < 93){
		mp3.album[i] = buffer[i];
		i++;
	}

	while (i < 97){
		mp3.jahr[i] = buffer[i];
		i++;
	}

	while (i < 127){
		mp3.kommentar[i] = buffer[i];
		i++;
	}

	mp3.genre = buffer[i];

	printTag(&mp3);


	
	if(fclose(file) != 0){
		perror("Error mit fclose");
		return;
	}

	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
}

/* Die Informationen im Puffer, auf den buffer verweist, *
 * wird in einem struct abgelegt.			 */
struct mp3file* bytesToIdTag(char *buffer)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	return NULL;
}
/*				       *
 * Es werden die in dem struct mp3file *
 * abgelegten Informationen ausgegeben *
 *				       */
void printTag(struct mp3file *mp3)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	printf("Titel  %s\n", mp3->titel);
	printf("Album  %s\n", mp3->album);
	printf("Kommentar  %s\n", mp3->kommentar);
	printf("interpret  %s\n", mp3->interpret);

}
