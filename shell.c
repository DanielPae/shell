#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "shell.h"


char* getNextImput(){
	char* ans = malloc(1000);	
	fgets(ans, 1000, stdin);
	return ans;
}

char ** parse_args ( char * line ){
  char ** args = (char **) malloc(sizeof(char *) * 6);
  int i = 0;
  while(line){
    args[i] = strsep(&line, " ");
    i++;
  }
  args[i] = NULL;
  return args;
}

int main(){
	char *run = getNextImput();
	char mutable[50];
	int len = strcspn(run, "\n");
	strncpy(mutable, run, len);
	mutable[len] = 0;
	char **args = parse_args(mutable);
	execvp(args[0], args);
	printf("%s\n", mutable);
	printf("%d\n", len);
	printf("%s\n", strerror(errno));
}


