#include <sys/types.h>
#include "datacopy.h"

void sig_winch(int signo){
  struct winsize size;
  ioctl(fileno(stdout), TIOCGWINSZ, (char*)&size);
  resizeterm(size.ws_row, size.ws_col);
}

void init(){
  initscr();
  start_color();
  init_pair(1,COLOR_WHITE,COLOR_BLUE);
  init_pair(2,COLOR_WHITE,COLOR_BLACK);
  signal(SIGWINCH, sig_winch);
  cbreak();
  curs_set(0);
  refresh();
  noecho();
  left = malloc(sizeof(*left));
  right = malloc(sizeof(*right));
  left->wnd = newwin(50,91,2,5);
  box(left->wnd,'|','-');
  right->wnd = newwin(50,91,2,105);
  box(right->wnd,'|','-');
  left->numberOfStrings = 0, left->indexOfAllotedString = 0;
  right->numberOfStrings = 0, right->indexOfAllotedString = 0;
  wrefresh(left->wnd);
  wrefresh(right->wnd);
  getch();
}

void changeValue(struct wndw *curr){
  int i;
  WINDOW* tmp = derwin(curr->wnd,48,88,1,2);
  for(i=0;i< curr->numberOfStrings; ++i){
    if(i == curr->indexOfAllotedString){
      wattron(curr->wnd,COLOR_PAIR(1));
      wprintw(tmp,"%s\n",(curr->name)[i]);
      wattroff(curr->wnd,COLOR_PAIR(1));
    }else{
      wattron(curr->wnd,COLOR_PAIR(1));
      wprintw(tmp,"%s\n",(curr->name)[i]);
      wattroff(curr->wnd,COLOR_PAIR(1));
    }
  }
  wrefresh(tmp);
  delwin(tmp);
//  getch();
}

void getDataOfDirectory(struct wndw *curr, char* path){
  //free(curr->name);
  struct dirent *current;
  DIR* dir = opendir(path);
  curr->name = (char**)malloc(sizeof(char*));
  while(current = readdir(dir)){
    curr->name = realloc(curr->name,(curr->numberOfStrings + 1) * sizeof(char*));
    (curr->name)[curr->numberOfStrings] = (char*)malloc(255 * sizeof(char));
    strcpy(curr->name[curr->numberOfStrings],current->d_name);
    curr->numberOfStrings += 1;
  }
}

void menu(){
  struct wndw* curr = left;
  curr->indexOfAllotedString = 5;
  while(1){
    int code = getch();
    switch(code){
      case 10:
        return;
      case KEY_UP:
	if(curr->indexOfAllotedString)
	  curr->indexOfAllotedString -= 1;
	changeValue(curr);
	break;
      case KEY_DOWN:
	if(curr->indexOfAllotedString < curr->numberOfStrings - 1)
	  curr->indexOfAllotedString += 1;
	changeValue(curr);
	break;
      case KEY_LEFT:
	curr = left;
	break;
      case KEY_RIGHT:
	curr = right;
	break;
/*      default:
	printf("asd");
        return;*/
    }
  }
//  switch(
}

int main(){
  init();
//  char* st = getenv("PWD");
  getDataOfDirectory(left,getenv("PWD")); 
  changeValue(left);
  getDataOfDirectory(right,getenv("HOME"));
  changeValue(right);
  menu();
  endwin();
  printf("%d\n",left->indexOfAllotedString);
//  printf("%d",left->numberOfStrings);
/*  int n;
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
  input(indCurr,indHome);*/
  return 0;
}
