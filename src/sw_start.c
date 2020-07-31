#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "sw_info.h"
#include "sw_log.h"
#include "convert_to_string.h"

static int swForkAndExec(const char* swName, char argv[MAX_ARGV_COUNT][STR_SIZE])
{
	pid_t pid;
	char temp[BUFSIZ];
	getcwd(temp, BUFSIZ);
	
	pid = fork();
	if (pid == 0) {
		strcat(temp, "/bin/");
		strcat(temp, swName);
		execl(temp, argv[0], argv[1], argv[2], argv[3], NULL);
		printf("swForkAndExec(): ERROR\n");
		return -1;
	} else if (pid > 0) {
		return pid;
	}
	return -1;
}

static void swStartInfoSet(pid_t pid, struct SwStartInfo* swStartInfo)
{
	swStartInfo -> swPID = pid;
	swStartInfo -> startTime = time(NULL);
}

int swInitStart(int swBlockCount, struct SwInfo* swInfos, struct SwStartInfo* swStartInfos)
{
	int i;

	pid_t pid;
	for(i = 0; i < swBlockCount; i++) {
		pid = swForkAndExec(swInfos[i].swName,swInfos[i].swArgv);
		if (pid < 0) return -1;
		memcpy(&swStartInfos[i], &swInfos[i], sizeof(struct SwInfo));
		swStartInfoSet(pid, &swStartInfos[i]);
		swStartInfos[i].status = -9999;
		swStartInfos[i].restartCount = 1;
		writeSwStartLog(swStartInfos[i]);
	} 
	return 0;
}

int swRestart(struct SwInfo swInfo, struct SwStartInfo* swStartInfo)
{
	pid_t pid = swForkAndExec(swInfo.swName, swInfo.swArgv);
	if (pid < 0) return -1;
	swStartInfoSet(pid, swStartInfo);
	(swStartInfo -> restartCount)++;
	writeSwStartLog(*swStartInfo);
	return 0;
}

int printSwStartInfos(int swBlockCount, struct SwStartInfo* swStartInfo)
{
	int i;

	printf("S/W Block Name\t\tRestart Count\t\tStart Time\t\t\tReason\n");
	for (i = 0; i < swBlockCount; i++) {
		printf("%s\t\t%d\t\t\t%s\t\t%s\n",
				swStartInfo[i].swInfo.swName,
				swStartInfo[i].restartCount,
				convertTimeToString(swStartInfo[i].startTime),
				convertStatusToString(swStartInfo[i].status));
	}
	return 0;
}
