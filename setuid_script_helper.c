/*
 * This program is release under GPLv3!!!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>

int main(int argc, char ** argv)
{
	struct stat stat_buf;
	char *ident = "automationHelper";
	
	char message[512] = {0};

	int logopt = LOG_PID | LOG_CONS;
	int facility = LOG_USER;
	int priority = LOG_ERR | LOG_USER;

	int result=0;

	openlog(ident, logopt, facility);
//	int mask = LOG_MASK (LOG_ERR);
//	result = setlogmask(mask);

	if (argc!=2) {
		snprintf(message,512,"Usage: setuid_script_helper \"[arguments]\"");
		printf("%s\n", message);
		syslog(priority,"%s",message);
		return -1;
	}

	if (stat(argv[1],&stat_buf)!=0) {
		snprintf(message,512,"Shell scripte file does not exist!");
		printf("%s\n", message);
		syslog(priority,"%s",message);
		return -1;
	}

	/* "owner" has X permission */
	if (((stat_buf.st_mode & S_IXUSR) \
			/* "group" has X, and "group" is equal to current "group" */
		       	&& ((stat_buf.st_mode & S_IXGRP) && stat_buf.st_gid == getgid()))
			/* if the current user is root, let *him* pass */
			|| ((stat_buf.st_mode & S_IXUSR) && stat_buf.st_uid == getuid())) \
	{
		snprintf(message,512,"Run script:[%s]",argv[1]);
		printf("%s\n", message);
		syslog(priority,"%s",message);

		/* check setuid bit */
		if (stat_buf.st_mode & S_ISUID) {
			printf("my uid: %d\n", stat_buf.st_uid);
			result=setuid(stat_buf.st_uid);
			snprintf(message,512,"Set uid to %d , return code is %d!",stat_buf.st_uid,result);
		printf("%s\n", message);
			syslog(priority,"%s",message);	
		} else {
		/* do nothing */
		}

		result=system(argv[1]);
		snprintf(message,512,"Script executed, return code is %d!",result);
		printf("%s\n", message);
		syslog(priority,"%s",message);
	} else {
		snprintf(message,512,"Permission denied to run script:[%s]",argv[1]);
		printf("%s\n", message);
		syslog(priority,"%s",message);
	}
}
