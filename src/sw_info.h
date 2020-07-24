#ifndef SW_INFO_H
#define SW_INFO_H

#include <sys/types.h>
#include <time.h>

#define STR_SIZE 256
#define MAX_ARGV_COUNT 4

struct SwInfo
{
	char swName[STR_SIZE];
	char swArgv[MAX_ARGV_COUNT][STR_SIZE];
};

struct SwStartInfo
{
	struct SwInfo swInfo;
	pid_t swPID;
	time_t startTime;
	int status;
	int restartCount;
	int needStart;
};

#endif
