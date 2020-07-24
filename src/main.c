#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sw_info.h"
#include "sw_read_info.h"
#include "sw_start.h"

static int gSwBlockCount = 0;
static struct SwStartInfo swStartInfos[10];

void handler()
{
	int i;
	int status;
	pid_t pid;
	pid = waitpid(-1, &status, WNOHANG);
	if (pid > 0)
	{
		for (i = 0; i < gSwBlockCount; i++) {
			if (pid == swStartInfos[i].swPID) {
				swStartInfos[i].status = status;
				swStartInfos[i].needStart = 1;
				break;
			}
		}
	}
}

int setSignalHandler(void)
{
	struct sigaction act;
	sigemptyset(&(act.sa_mask));
	act.sa_handler = handler;
	sigaction(SIGCHLD, &act, NULL);
	return 0;
}

int swBlockNumCheckAndRestart(int swNum)
{
	if (swStartInfos[swNum].needStart) {
		if (swRestart(swStartInfos[swNum].swInfo, &swStartInfos[swNum]) < 0) {
			return -1;
		}
		swStartInfos[swNum].needStart = 0;
		return 1;
	}
	return 0;
}

void panic(const char* errString)
{
	printf("%s\n", errString);
	exit(-1);
}

int main()
{
	int i, temp;
	struct SwInfo swInfos[10];
	
	setSignalHandler();
	if (readFileList(&gSwBlockCount, swInfos)) 
		panic("READ FAILED\n");

	if(swInitStart(gSwBlockCount, swInfos, swStartInfos)  < 0)
		panic("INIT FAILED\n");
	
	printSwStartInfos(gSwBlockCount, swStartInfos);
	
	while(1) {
		for (i = 0; i < gSwBlockCount; i++) {
			temp = swBlockNumCheckAndRestart(i);
			if (temp < 0)
				panic("RESTART FAILED\n");
			else if (temp == 1)
				printSwStartInfos(gSwBlockCount, swStartInfos);
		}
	}
	
	return 0;
}
