#include "sort.h"

char** sort(char** array, int ind){
  int i,j;
  for(i=0;i<ind-1;++i){
    for(j=0;j<ind-i-1;++j){
      if(strcmp(array[j],array[j+1])>-1){
        char *tmp;
        strcpy(array[j],tmp);
        strcpy(array[j+1],array[j]);
        strcpy(tmp,array[j+1]);
      }
    }
  }
}
