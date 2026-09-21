#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>

#ifdef __linux__
	#include <unistd.h>
	#include <sys/sysinfo.h>
#endif

#include "colors.h"
#include "config.h"
#include "functions.h"

/* Functions are defined in functions.h file, if you want to ake a look at them. */

int main(int argc, char *argv[]) {

	/* Arguments */

	if (argc >= 2) {
		handleargs(argv);
	} else {

	if (hide_term == 1) {	
		printf("\e[1;1H\e[2J");
	}

	if (logos_enable == 1) {
		showlogo();	
		printf("\n");
	}

	get_user();
	printf(MAG BOLD "%s" RESET, os);
	checkdistro();

	printf(MAG BOLD "%s" RESET,term);
	get_term();	

	printf(MAG BOLD "%s" RESET,kernel);
	get_kernel();

	printf(MAG BOLD "%s" RESET, uptime);
	get_uptime();

  printf(MAG BOLD "%s" RESET, wm);
  get_wmde();

	printf(MAG BOLD "%s" RESET, shell);
	get_shell();

	printf(MAG BOLD "%s" RESET, memory);
	get_memory();
	
	printf(MAG BOLD "%s" RESET, compositor);
	get_compositor();
		
	printf(MAG BOLD "%s" RESET, procs);
	get_procs();	

	printf("\n");
	}

	if (hide_term == 1) {
		getchar();
	}
		
	return 0;
}
