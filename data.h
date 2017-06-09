#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <stdio.h>
struct curr{
  char** nameCurr;
  int numberOfCurrentStrings = 0;
  int indexOfCurrentAllotedString = 0;
};

struct home{
  char** nameHome;
  int numberOfHomeStrings = 0;
  int indexOfHomeAllotedString = 0;
  
};
/*char** nameCurr, **nameHome;
int indCurr = 0, indHome = 0;*/
void input(int,int);
void init();
