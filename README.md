# shell
by Daniel Pae

FEATURES:
  - Runs shell commands
  - Reads multiple commands on the same line, separated by ;
  - Redirects stdin and stdout with < and > respectivly 
  - Simple pipes use the output of ome function as imput for the other
  - Fairly loose with requrements for commands spacing. Flags for individual commands must be one space apart, other than that you can use as many spaces as you like (as long as you use at least one).
  - Desplays working directory 
  
ATTEMPTED;
  - I did not leave several of these things in my code, some of these things are not commented out but do not work in every situation.
  - Putting as many spaces as you like between anything. It works for everything execpt things that have to be split on spaces.
  
BUGS:
  - After you use | in any command, every future command requres you to hit entre when it finishes to imput your next command
  
FILES AND FUNCTIONS:
 (I might have put it all in one file)
 
 ---------------shell.h---------------------
 
 contains function headers for shell.c
 
 has some nice comments, that I did not keep up with throught the entire project
 
 ---------------shell.c---------------------

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

So none of these splits have to be seprate functions. I could have just used parse and it probably would have been more effiecnt. This did help me keep it straight in my head and at some point in this project there was a point for all of this.

char** parse(char *, char *);

	// Helper function for all of the splits. Splits first argument on second argument 

void my_cd(char * filename);

	// Takes a string
  
	// Changes directory 
  
void re_out(char **);

	//redirects the output of the fuction contained in the char ** to stdout

void re_in(char **);

	//redirects the output of the fuction contained in the char ** to stdin

So this also isn't necessary but I like it don't judge me

void redirect(char **, char *, int);

	// Takes a char *[2], a file name as a string, and the fd of the place to redirect it to 
  
	// Redirects the output of a given function into the second argument. Helper function for re_out and re_in

void pipe_it(char **);

	// Takes a char *[2] with char[0] and char[1] being commands. Redirects the output of char[0] into the imput of char[1]

int run_command(char**);

	// Forks of a child process and runs execvp. Returns 1 if there is a problem
