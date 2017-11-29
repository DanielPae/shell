// uses fgets to get the next user imput
char* get_next_imput();

// removes \n chars from the end of a string
int ready_string(char *);

// splits a string on its white spaces and returns a char ** of the new strings
char** split_args(char*);

// splits a string on ; and returns a char ** of the new strings
char** split_commands(char*);

// splits a string on > and returns a char ** of the new strings
char** split_redirect(char*);

// helper function for all of the splits. Splits first argument on second argument 
char** parse(char *, char *);

// forks of a child process and runs execvp. Returns 1 if there is a problem
int run_command(char**);
