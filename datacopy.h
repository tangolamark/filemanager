#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

struct wndw{
  WINDOW *wnd;
  char** name;
  int numberOfStrings;
  int indexOfAllotedString;
} *left, *right;
