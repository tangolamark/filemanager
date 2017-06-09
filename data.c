#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "data.h"

void sig_winch(int signo){
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
  resizeterm(size.ws_row, size.ws_col);
}

void init(){
  initscr();
  signal(SIGWINCH, sig_winch);
  cbreak();
  curs_set(0);
  refresh();
  noecho();
}

void input(int indCurr, int indHome){
  int i;
  WINDOW *wnd, *left, *right;
  wnd = newwin(50,182,2,5);
  box(wnd,'|','-');
  left = derwin(wnd,43,88,1,2);
  box(left,'|','-');
  right = derwin(wnd,43,88,1,92);
  box(right,'|','-');
  for(i=0;i<indCurr;++i){
    wmove(left, i + 2,2);
    wprintw(left, "%s",nameCurr[i]);
    //wrefresh(left);
    //wrefresh(wnd);
  }
  for(i=0;i<indHome;++i){
    wmove(right,i + 2,2);
    wprintw(right,"%s",nameHome[i]);
  }
  wrefresh(left);
  wrefresh(right);
  wrefresh(wnd);
  getch();
  delwin(left);
  delwin(right);
  delwin(wnd);
  refresh();
  endwin();
}


int main(){
  struct dirent *current;
  init();
  int n;
  DIR* dir = opendir(getenv("PWD"));
  nameCurr = (char**)malloc(sizeof(char*));
  while(current = readdir(dir)){
    n = strlen(current->d_name);
    nameCurr = realloc(nameCurr,(indCurr+1) * sizeof(char*));
    nameCurr[indCurr] = (char*)malloc(200 * sizeof(char));
    strcpy(nameCurr[indCurr],current->d_name);
    ++indCurr;
  }
  dir = opendir(getenv("HOME"));
  nameHome = (char**)malloc(sizeof(char*));
  while(current = readdir(dir)){
    n = strlen(current->d_name);
    nameHome = realloc(nameHome,(indHome+1) * sizeof(char*));
    nameHome[indHome] = (char*)malloc(255 * sizeof(char));
    strcpy(nameHome[indHome],current->d_name);
    ++indHome;
  }
  input(indCurr,indHome);
  return 0;
}
