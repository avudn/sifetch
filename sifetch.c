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
#define VERSION "1.6.0"

/* Config */

/* Colors are defined in colors.h, refer to them if you want to change colors. */
#define COLOR BLU
#define logos_enable 1
#define hide_term 1

#define LOGO_WIDTH 20
#define INFO_LINES 10 /* number of info lines printed in main() */

/* Hardware Stuff */

const char * os = "os: ";
const char * uptime = "up: ";
const char * kernel = "kern: ";
const char * wm = "wm: ";
const char * shell = "sh: ";
const char * term = "term: ";
const char * compositor = "entity: ";
const char * host = "user: ";
const char * memory = "mem: ";
const char * procs = "procs: ";
const char * cpu = "cpu: ";

/* Functions */
struct sysinfo modules;
int logo_lines = 0; /* how many lines the logo took, set by showlogo() */

void showhelp() {
	printf("sifetch 1.3.0\n");
	printf("Usage: sifetch [Option] \n");
	printf("-v — Check current version\n");
	printf("-h — Show Help\n");
}

void handleargs(char *argv[]) {
	if (strncmp("-v", argv[1], 3) == 0) {
		printf("Version: %s\n", VERSION);
	} else if (strncmp("-h", argv[1], 3) == 0) {
		showhelp();
	}
}

void info_col(void) {
	if (logos_enable == 1)
		printf("\e[%dG", LOGO_WIDTH + 1);
}

unsigned long long get_meminfo_value(const char *key) {
    char buffer[1024];
    unsigned long long value = 0;

    FILE *fl = fopen("/proc/meminfo", "r");
    if (fl == NULL)
        return 0;

    while (fgets(buffer, sizeof buffer, fl) != NULL) {
        if (strncmp(buffer, key, strlen(key)) == 0) {
            sscanf(buffer, "%*s %llu", &value);
            break;
        }
    }

    fclose(fl);
    return value;
}



void get_kernel(void) {
	struct utsname kernelget;
	uname(&kernelget);

	printf("%s\n", kernelget.release);
}

void get_memory(void) {
    unsigned long long total = get_meminfo_value("MemTotal:") / 1024;
    unsigned long long avail = get_meminfo_value("MemAvailable:") / 1024;
    unsigned long long used  = total - avail;

    printf("%lluM/%lluM\n", used, total);
}

void get_uptime() {
	sysinfo(&modules);

	long seconds = modules.uptime;
	long minutes = seconds/60;
	long hours = minutes/60;

	minutes %= 60;

	printf("%ld hours, %ld mins\n", hours, minutes);

}

int get_wmde() {
  char *wmde = getenv("XDG_CURRENT_DESKTOP");
  if (wmde == NULL)
    return 1;
  printf("%s\n", wmde);
  return 0;
}

void get_procs() {
	sysinfo(&modules);

	printf("%d\n", modules.procs);
}

int get_user() {
	sysinfo(&modules);

	char nbuf[64];
	char hbuf[64];

	int userget = getlogin_r(nbuf, sizeof(nbuf));
		
	if (userget != 0) {
		printf("Login not found.");
		return 1;
	}

	char *user = nbuf;	
	int hostn = gethostname(hbuf,sizeof(hbuf));
		
	if (hostn != 0) {
		printf("Hostname not found.");
		return 1;
	}

	char *host = hbuf;
	printf(COLOR BOLD "%s@%s\n" RESET, user, host);
		
	return 0;

}

int get_term() {
	sysinfo(&modules);

	char *term = getenv("TERM");
	if (term == NULL)
		return 1;
	printf("%s\n", term);

	return 0;
}

int get_compositor() {
	sysinfo(&modules);

	char *compositor = getenv("XDG_SESSION_TYPE");
		if (compositor == NULL)
			return 1;
	printf("%s\n", compositor);

	return 0;
}

int get_shell() {
	sysinfo(&modules);

	char *shell = getenv("SHELL");
		if (shell == NULL)
			return 1;
	printf("%s\n", shell);

	return 0;
}

int checkdistro() {
	char osrelease[40];
	FILE *openosrelease = fopen("/etc/os-release", "r");

	if (openosrelease == NULL)
		return 1;
	
	if (fgets(osrelease, sizeof(osrelease), openosrelease) == NULL)
    return 1;

	char *distro = (osrelease + 6);
	distro[strlen(distro) - 2] = '\0';

	fclose(openosrelease);
	if (strstr(distro, "Linux") != NULL) {
		printf("%s\n", distro);

	} else {
		printf("%s Linux\n", distro);

	}
	return 0;
}

const char *get_ascii() {
	static char osrelease[40];
	FILE *f = fopen("/etc/os-release", "r");

	if (f == NULL)
		return "1";

	if (fgets(osrelease, sizeof(osrelease), f) == NULL)
    return "1";

	fclose(f);

	char *distro = osrelease + 6;

	return distro;	
}

/* Prints the logo in COLOR and leaves the cursor on the line below it.
   main() then moves the cursor back up so the info is drawn next to it. */
int showlogo() {

	const char *distro = get_ascii();
	if (distro == NULL) 
		return 1;

	if (strstr(distro, "Exherbo") != NULL) {
		logo_lines = 4;
		printf(COLOR
		"        (__) \n"
		"`\\------(oo) \n"
		"  ||    (__) \n"
		"  ||w--||    \n"
		RESET);

	} else if (strstr(distro, "Arch") != NULL) {
		logo_lines = 7;
		printf(COLOR
       	 	"      /\\\n"
        	"     /  \\\n"
        	"    /    \\\n"
        	"   /      \\\n"
        	"  /   ,,   \\\n"
        	" /   |  |   \\\n"
        	"/_-''    ''-_\\\n"
		RESET);

	} else if (strstr(distro, "Gentoo") != NULL) {
		logo_lines = 7;
		printf(COLOR
        	" _-----_ \n"
        	"(       \\ \n"
        	"\\    0   \\ \n"
        	" \\        ) \n"
        	" /      _/ \n"
        	"(     _- \n"
       	 	"\\____- \n"
    		RESET);
	} else if (strstr(distro, "Nix") != NULL) {
		logo_lines = 7;
		printf(COLOR
    "  ▗▄   ▗▄ ▄▖\n"
    " ▄▄🬸█▄▄▄🬸█▛ ▃\n"
    "   ▟▛    ▜▃▟🬕\n"
    "🬋🬋🬫█      █🬛🬋🬋\n"
    " 🬷▛🮃▙    ▟▛\n"
    " 🮃 ▟█🬴▀▀▀█🬴▀▀\n"
    "  ▝▀ ▀▘   ▀▘\n"
    RESET);
	} else {
		logo_lines = 7;
		printf(COLOR
        	"    .--. \n"
        	"   |o_o | \n"
        	"   |:_/ | \n"
        	"  //   \\ \\ \n"
        	" (|     | ) \n"
        	"/'\\_   _/`\\ \n"
        	"\\___)=(___/ \n"
    		RESET);
	}
	return 0;
}

/* Launch */

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
		/* jump back up to the top of the logo so info is printed beside it */
		printf("\e[%dA", logo_lines);
	}

	info_col();
	get_user();

	info_col();
	printf(COLOR BOLD "%s" RESET, os);
	checkdistro();

	info_col();
	printf(COLOR BOLD "%s" RESET,term);
	get_term();	

	info_col();
	printf(COLOR BOLD "%s" RESET,kernel);
	get_kernel();

	info_col();
	printf(COLOR BOLD "%s" RESET, uptime);
	get_uptime();

	info_col();
	printf(COLOR BOLD "%s" RESET, wm);
	get_wmde();

	info_col();
	printf(COLOR BOLD "%s" RESET, shell);
	get_shell();

	info_col();
	printf(COLOR BOLD "%s" RESET, memory);
	get_memory();
	
	info_col();
	printf(COLOR BOLD "%s" RESET, compositor);
	get_compositor();
		
	info_col();
	printf(COLOR BOLD "%s" RESET, procs);
	get_procs();	

	/* if the logo is taller than the info, skip down past it */
	if (logos_enable == 1 && logo_lines > INFO_LINES)
		printf("\e[%dB", logo_lines - INFO_LINES);

	printf("\e[1G\n");
	}

	if (hide_term == 1) {
		getchar();
	}
		
	return 0;
}
