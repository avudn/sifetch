#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define VERSION "1.5.0"

struct sysinfo modules;


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
	printf(WHT BOLD "%s@%s\n" RESET, user, host);
		
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
	
	fgets(osrelease, sizeof(osrelease), openosrelease);
	fclose(openosrelease);

	char *distro = (osrelease + 6);
	distro[strlen(distro) - 2] = '\0';

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
	
	fgets(osrelease, sizeof(osrelease), f);
	fclose(f);

	char *distro = osrelease + 6;

	return distro;	
}


int showlogo() {

	const char *distro = get_ascii();
	if (distro == NULL) 
		return 1;

	if (strstr(distro, "Exherbo") != NULL) {
		printf(
		"\t        (__) \n"
		"\t`\\------(oo) \n"
		"\t  ||    (__) \n"
		"\t  ||w--||    \n"
		);

	} else if (strstr(get_ascii(), "Arch") != NULL) {
	
		printf(
       	 	"\t      /\\\n"
        	"\t     /  \\\n"
        	"\t    /    \\\n"
        	"\t   /      \\\n"
        	"\t  /   ,,   \\\n"
        	"\t /   |  |   \\\n"
        	"\t/_-''    ''-_\\\n"
		);

		/* printf("%s%s%s%s%s%s%s", line1,line2,line3,line4,line5,line6,line7); */
	} else if (strstr(get_ascii(), "Gentoo") != NULL) {
		printf(RED
        	"\t _-----_ \n"
        	"\t(       \\ \n"
        	"\t\\    0   \\ \n"
        	"\t \\        ) \n"
        	"\t /      _/ \n"
        	"\t(     _- \n"
       	 	"\t\\____- \n"
    		RESET);
	} else if (strstr(get_ascii(), "Nix") != NULL) {
		printf(
    "\t" BLU "  ▗▄   " CYN "▗▄ ▄▖" "\n"
    "\t" BLU " ▄▄🬸█▄▄▄" CYN "🬸█▛ " BLU "▃" "\n"
    "\t" CYN "   ▟▛    " CYN "▜" BLU "▃▟🬕" "\n"
    "\t" CYN "🬋🬋🬫█      " BLU "█🬛🬋🬋" "\n"
    "\t" CYN " 🬷▛🮃" CYN "▙    " BLU "▟▛" "\n"
    "\t" CYN " 🮃 " CYN "▟█🬴" BLU "▀▀▀█🬴▀▀" "\n"
    "\t  " CYN "▝▀ ▀▘   " BLU "▀▘" "\n"
    RESET);	
	} else {
		printf(
        	"\t    .--. \n"
        	"\t   |o_o | \n"
        	"\t   |:_/ | \n"
        	"\t  //   \\ \\ \n"
        	"\t (|     | ) \n"
        	"\t/'\\_   _/`\\ \n"
        	"\t\\___)=(___/ \n"
    		);
	}
	return 0;
}

#endif

