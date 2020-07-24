#ifndef SW_START_H
#define SW_START_H

#include "sw_info.h"

int swInitStart(int swBlockCount,
		struct SwInfo* swInfos, 
		struct SwStartInfo* swStartInfos);
int swRestart(struct SwInfo swInfo, struct SwStartInfo* swStartInfo);
int printSwStartInfos(int swBlockCount, 
		struct SwStartInfo* swStartInfo);

#endif
