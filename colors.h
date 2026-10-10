#ifndef COLORS_H
#define COLORS_H

#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)

#define RESET     "\x1B[0m" // reset to normal
#define BOLD      "\x1B[1m" // bolded text
#define DIM       "\x1B[2m" // dimmed text
#define UNDER     "\x1B[4m" // on monochrome display adapter only
#define BLINK     "\x1B[5m" // doesn't work
#define REVERSE   "\x1B[7m" // reverse background and roreground colors
#define CONCEALED "\x1B[8m" // transparent text

// Foreground (text) colors
#define BLK       "\x1B[30m"  // black
#define RED       "\x1B[31m"  // red
#define GRN       "\x1B[32m"  // green
#define YEL       "\x1B[33m"  // yellow
#define BLU       "\x1B[34m"  // blue
#define MAG       "\x1B[35m"  // magenta
#define CYN       "\x1B[36m"  // cyan
#define PNK       "\x1B[38;5;197m" // whatever
#define WHT       "\x1B[37m"  // white

// Backgroung colors
#define BGBLK     "\x1B[40m"
#define BGRED     "\x1B[41m"
#define BGGRN     "\x1B[42m"
#define BGYEL     "\x1B[43m"
#define BGBLU     "\x1B[44m"
#define BGMAG     "\x1B[45m"
#define BGCYN     "\x1B[46m"
#define BGWHT     "\x1B[47m"

#endif // linux | unix | apple


#endif
