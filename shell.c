#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "shell.h"


char* get_next_imput(){
	static char ans[1000];	
	char path[258];
	getcwd(path, 255);
	printf("%s: ", path);
	fgets(ans, 1000, stdin);
	return ans;
}

char * ready_string ( char *str ){
	int blanks = 0;
	while(str[blanks] == ' '){
		blanks++;
	}
	str = str + blanks;
	int len = strcspn(str, "\n\0");
	while(str[len - 1] == ' ' || str[len - 1] == '0' && len > -1){
		len--;
	}
	str[len] = 0;
	return str;
}

char ** split_args ( char *line ){
	char *split = " ";
	return parse( line, split);
} 

char ** split_commands ( char *line ){
	char *split = ";";
	char **commands = parse( line, split);
	int i = 0;
	while(commands[i]){
		commands[i] = ready_string(commands[i]);
		i++;
	}
	return commands;
} 

char ** split_redirect_out ( char *line ){
	char *split = ">";
	char **commands = parse( line, split);
	int i = 0;
	while(commands[i]){
		commands[i] = ready_string(commands[i]);
		i++;
	}
	return commands;
} 

char ** split_redirect_in ( char *line ){
	char *split = "<";
	char **commands = parse( line, split);
	int i = 0;
	while(commands[i]){
		commands[i] = ready_string(commands[i]);
		i++;
	}
	return commands;
} 

char ** split_pipe ( char *line ){
	char *split = "|";
	char **commands = parse( line, split);
	int i = 0;
	while(commands[i]){
		commands[i] = ready_string(commands[i]);
		i++;
	}
	return commands;
} 

char ** parse ( char *line, char *split ){
  char ** args = (char **) malloc(sizeof(char *) * 10);
  int i = 0;
  while(line){
    args[i] = strsep(&line, split);
    i++;
  }
  args[i] = NULL;
  return args;
}

void my_cd(char * filename){
	char path[258];
	getcwd(path, 255);
	strcat(path, "/");
	strcat(path, filename);
	chdir(path);
}

void re_out(char ** command){
	char path[258];
	getcwd(path, 255);
	strcat(path, "/");
	strcat(path, command[1]);
	char **args = split_args(command[0]);
	redirect(args, path, STDOUT_FILENO);
}

void re_in(char ** command){
	char path[258];
	getcwd(path, 255);
	strcat(path, "/");
	strcat(path, command[1]);
	char **args = split_args(command[0]);
	redirect(args, path, STDIN_FILENO); 
}

void redirect(char ** function, char * destination, int in_out){
	int holder = dup(in_out);
	int asd = open(destination, O_RDWR | O_CREAT, 0644);
	int dest = dup2(asd, in_out);
	run_command(function);
	dup2(holder, dest);
}

void pipe_it( char ** pipeable){
	int holder = dup(STDIN_FILENO);
	FILE* f = popen(pipeable[0], "r");
	int asd = fileno(f);
	int dest = dup2(asd, STDIN_FILENO);
	char **args = split_args(pipeable[1]);
	run_command(args);
	dup2(holder, dest);
	fclose(f);
	
}

int run_command( char **args){
	if(!strcmp("exit", args[0])){
		//ENDS THE PROGRAM
		printf("Was it something I said?\n");
		exit(0);
	}	
	else if(!strcmp("cd", args[0])){
		//CDS THE STUFFS
		my_cd(args[1]);
	}
	else{
		//RUNS THE COMMAND
		int child = fork();
		if(child){
			wait();
		}
		else{
			execvp(args[0], args);
			exit(0);
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
		imput = ready_string(imput);

		//splits the string into seprate commands
		char **commands = split_commands(imput);	

		//loop through all the commands and run them
		int i = 0;
		while(commands[i]){
			//split commands into its seprate arguments
			if(strchr(commands[i], '>')){
				char **split = split_redirect_out(commands[i]);
				re_out(split);
				i++;
			}
			else if(strchr(commands[i], '<')){
				char **split = split_redirect_in(commands[i]);
				re_in(split);
				i++;
			}
			else if(strchr(commands[i], '|')){
				char **split = split_pipe(commands[i]);
				pipe_it(split);
				i++;
			}
			else{
			char **args = split_args(commands[i]);
			//run the command
			run_command(args);
			//next command
			i++;
			}
		}
	}
}


