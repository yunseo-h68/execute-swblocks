#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "sw_info.h"

static char* ltrim(char *s)
{
	char* begin;
	begin = s;

	while(*begin != '\0') {
		if (isspace(*begin))
			begin++;
		else {
			s = begin;
			break;
		}
	}

	return s;
}

static char* rtrim(char *s)
{
	static char t[STR_SIZE];
	char *end;
	strcpy(t, s);
	end = t + strlen(t) - 1;
	while(end != t && isspace(*end))
		end--;
	*(end + 1) = '\0';
	s = t;
	return s;
}

static char* trim(char *s)
{
	return rtrim(ltrim(s));
}

int readFileList(int* swBlockCount, struct SwInfo* swInfos)
{
	int n = 0;
	char *result = NULL;
	FILE *fp = fopen("FileList.txt", "r");
	char str[BUFSIZ];
	
	if (fp == NULL) {
		printf("\'../FileList.txt\' is not found\n");
		return -1;
	}

	while (fgets(str, STR_SIZE, fp)) {
		if (*swBlockCount > 10) return -1;
		result = strtok(str, ";");

		strcpy(swInfos[*swBlockCount].swName, result);
		strcpy(swInfos[*swBlockCount].swName, 
				trim(swInfos[*swBlockCount].swName));

		strcpy(swInfos[*swBlockCount].swArgv[n], swInfos[*swBlockCount].swName);
		n++;

		while ( result != NULL && n < 4) {
			result = strtok(NULL, ";");

			if (result != NULL) {
				strcpy(swInfos[*swBlockCount].swArgv[n], result);
				strcpy(swInfos[*swBlockCount].swArgv[n],
						trim(swInfos[*swBlockCount].swArgv[n]));
			} else {
				break;
			}

			n++;
		}
		swInfos[*swBlockCount].swArgv[n][0] = '\0';
		(*swBlockCount)++;
	}
	fclose(fp);
	return 0;
}
