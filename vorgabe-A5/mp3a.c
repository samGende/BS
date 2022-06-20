#include "mp3.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

void idTagFile(const char *fileName,char *comment)
{
	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	struct stat fileInfo;

	stat(fileName, &fileInfo);
	long size = fileInfo.st_size;
	if(S_ISREG(fileInfo.st_mode)){
		printf("is regular file\n");
	}else {
		printf("Invalid File type %s\n", fileName);
		return;
	}
	printf("%li\n", size);

	if (!strncmp(".", fileName, 2) || !strncmp("..", fileName, 3))
               	return;

	/* HIER MUESST IHR EUREN CODE EINFUEGEN */
	if (strncmp(fileName + strlen(fileName) - 4, ".mp3", 4)) {
			printf("%s: ausgelassen\n", fileName);
			return;
 	}

	FILE* file;
	char read = 'r';

//open file and move to data section
	file = fopen(fileName, &read);
	fseek(file, size - 128, 0);

	char buffer[128];
	fread(buffer, 1, 128, file);

	printf("%s\n", buffer);

	if(strncmp(buffer, "TAG",3)){
		printf("TAG not found in %s\n", fileName);
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
