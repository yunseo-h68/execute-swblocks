#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "sw_info.h"
#include "convert_to_string.h"

int writeSwStartLog(struct SwStartInfo swStartInfo)
{
	int fd;
	char buf[BUFSIZ];
	sprintf(buf, "%s %s %s %d\n", 
			swStartInfo.swInfo.swName,
			convertTimeToString(swStartInfo.startTime),
			convertStatusToString(swStartInfo.status),
			swStartInfo.restartCount);
	mkdir("log", 0755);
	fd = open("./log/restart.txt",
			O_WRONLY | O_CREAT | O_APPEND,
			S_IRWXU | S_IRWXG);
	
	if (fd == -1) {
		printf("writeSwStartLog() : ERROR\n");
		close(fd);
		return -1;
	}

	write(fd, buf, strlen(buf));
	close(fd);
	return 0;
}
