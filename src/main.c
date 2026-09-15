#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "config.h"
#include "functions.h"

/* Functions are defined in functions.h file, if you want to take a look at them. */

int main(int argc, char *argv[]) {

	/* Arguments */

	if (argc >= 2) {
		handleargs(argv);
	} else {

	/* printf("\e[1;1H\e[2J"); very secret scary killer DANGEROUS PRINTF DONT UNCOMMENT (i warned....) */
	printf("\n");

	get_module("user");

	printf("%s", os);
	checkdistro();

	printf("%s", term);
	get_module("term");

	printf("%s", shell);
	get_module("shell");


	printf("%s", kernel);
	checkfile(KERNEL_DIR);

	printf("%s", memory);
	get_memory();
	
	printf("%s", compositor);
	get_module("compositor");

	printf("\n");
/*
	printf("%s", uptime);
	get_module("uptime");

	printf("%s", term);
	get_module("term");

	

	printf("%s", host);
	get_module("host");	

	printf("%s", procs);
	get_module("procs"); */

	}
	return 0;
}
