#ifndef DISTROS_H
#define DISTROS_H

/* Directories */

#define KERNEL_DIR "/proc/sys/kernel/osrelease"
#define OS_DIR "/etc/os-release"
#define HOST_DIR "/etc/hostname"

/* Hardware Stuff */

const char * os = "OS: ";
const char * uptime = "uppies: ";
const char * kernel = "kernel: ";
const char * shell = "shell: ";
const char * term = "terminal: ";
const char * compositor = "compositor: ";
const char * host = "user: ";
const char * memory = "mem: ";
const char * procs = "procs: ";
const char * cpu = "CPU: ";

#endif
