#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "shell.h"


char* get_next_imput(){
	static char ans[1000];	
	printf("COMMAND:");
	fgets(ans, 1000, stdin);
	return ans;
}

int ready_string ( char *str ){
	int len = strcspn(str, "\n");
	str[len] = 0;
	return len + 1;
}

char ** split_args ( char *line ){
	char *split = " ";
	return parse( line, split);
} 

char ** split_commands ( char *line ){
	char *split = ";";
	return parse( line, split);
} 

char ** split_redirect ( char *line ){
	char *split = ">";
	return parse( line, split);
} 

char ** parse ( char *line, char *split ){
  char ** args = (char **) malloc(sizeof(char *) * 6);
  int i = 0;
  while(line){
    args[i] = strsep(&line, split);
    i++;
  }
  args[i] = NULL;
  return args;
}

int run_command( char **args){
	if(!strcmp("exit", args[0])){
		//ENDS THE PROGRAM
		printf("Was it something I said?\n");
		exit(0);
	}	
	else if(!strcmp("cd", args[0])){
		//WILL RUN CD STUFFS HERE
	}
	else{
		//RUNS THE COMMAND
		int child = fork();
		if(child){
			wait();
		}
		else{
			return execvp(args[0], args);
		}
	}
}

int main(){

	// VARIABLES:
	// imput -> stores user imput as a string
	// args -> stores char ** to put into execvp

	
	//RUN UNTIL USER EXITS
	while(1){
		//get user imput and put it into imput
		char *imput = get_next_imput();

		//gets the string ready to strsep
		ready_string(imput);

		//splits the string into seprate commands
		char **commands = split_commands(imput);
	
		//loop through all the commands and run them
		int i = 0;
		while(commands[i]){
			//split commands into its seprate arguments
			char **args = split_args(commands[i]);
			//run the command
			run_command(args);
			//next command
			i++;
		}
	}
}


