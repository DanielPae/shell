char* get_next_imput();
	// No imputs
	// Returns a string of the users imput 

char* ready_string(char *);
	// Takes a mutable string
	// Removes \n chars from the end of a string and blank space from front and end and returns it

char** split_args(char*);
	// Takes a mutable string
	// Splits a string on its white spaces and returns a char ** of the new strings

char** split_commands(char*);
	// Takes a mutable string
	// Splits a string on ; and returns a char ** of the new strings

char** split_redirect_out(char*);
	// Takes a mutable string
	// Splits a string on > and returns a char ** of the new strings

char** split_redirect_in(char*);
	// Takes a mutable string
	// Splits a string on < and returns a char ** of the new strings

char** parse(char *, char *);
	// Helper function for all of the splits. Splits first argument on second argument 

void my_cd(char * filename);
	// Takes a string
	// Changes directory 

void re_out(char **);
	//redirects the output of the fuction contained in the char ** to stdout

void re_in(char **);
	//redirects the output of the fuction contained in the char ** to stdin

void redirect(char **, char *, int);
	// Takes a char *[2], a file name as a string, and the fd of the place to redirect it to 
	// Redirects the output of a given function into the second argument. Helper function for re_out and re_in

void pipe_it(char **);
	// Takes a char *[2] with char[0] and char[1] being commands. Redirects the output of char[0] into the imput of char[1]

int run_command(char**);
	// Forks of a child process and runs execvp. Returns 1 if there is a problem

