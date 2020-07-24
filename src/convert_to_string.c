#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

char* convertStatusToString(int status)
{
	static char buf[BUFSIZ];

	if (status == -9999) {
		strcpy(buf, "Init");
		return buf;
	}
	if (WIFEXITED(status)) {
		sprintf(buf, "Exit(%d)", WEXITSTATUS(status));
		return buf;
	}

	if (WIFSIGNALED(status)) {
		sprintf(buf, "Signal(%d, %s)", 
				WTERMSIG(status), 
				strsignal(WTERMSIG(status)));
		return buf;
	}

	return NULL;
}

char* convertTimeToString(time_t startTime)
{
	static char buf[BUFSIZ];
	struct tm* t = localtime(&startTime);
	sprintf(buf, "%04d.%02d.%02d. %02d:%02d:%02d",
			t->tm_year + 1900,
			t->tm_mon + 1,
			t->tm_mday,
			t->tm_hour,
			t->tm_min,
			t->tm_sec
		   );
	return buf;
}
