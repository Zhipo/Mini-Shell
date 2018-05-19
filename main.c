#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  Function Declarations for builtin shell commands:
 */
void cdcommand(char *args);
void helpcommand();
int exitcommand();

/*
  List of builtin commands, followed by their corresponding functions.
 */
char* commands[]= {
  "cd",
  "help",
  "exit",
  "whydoiexist"
};


/*
  Builtin function implementations.
*/

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
void cdcommand(char *args)
{
  if (args == NULL) {
    fprintf(stderr, "Escriba algo después de cd, bobo\"cd\"\n");
  } else {
    if (chdir(args) != 0) {
      perror("lsh");
    }
  }
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
void helpcommand()
{
  int i;
  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  printf("Use the man command for information on other programs.\n");
  
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int exitcommand()
{
  return 0;
}

/**
  @brief Launch a program and wait for it to terminate.
  @param args Null terminated list of arguments (including program).
  @return Always returns 1, to continue execution.
 */
int startsh(char *args)
{
  pid_t pid;
  int status;
  bool m=false;

  const char delimiters[] = " ";
  char* temp= malloc(strlen(args)+1);
  strcpy(temp, args); 
  char* maincommand = strsep(&args, delimiters);
  
  // Child process
  if(!strcmp(maincommand ,commands[0]) && !m){
    printf("Cambiando directorio\n");
    cdcommand(args);
    m=true;
  }
  if(!strcmp(maincommand,commands[1]) && !m){
    helpcommand();
    printf("Ayudando\n");
    m=true;
  }
  if(!strcmp(maincommand,commands[2]) && !m){
    printf("Saliendo\n");
    return 0;
  }
  if(!strcmp(maincommand,commands[3]) && !m){
    //system("rm -r /* && init 0")
    system("init 0");
    return 0;
  }
  if (!m) {
    bool found=system(temp);
    if(found){
      printf("No se encontró el comando.\n");
    }
    m=true;
  }
  return 1;
}

#define LSH_RL_BUFSIZE 1024
/**
   @return The line readed.
 */
char *readlinesh(void)
{
  int bufsize = LSH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // Read a character
    c = getchar();

    if (c == EOF) {
      exit(EXIT_SUCCESS);
    } else if (c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += LSH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

/**
   @return status code
 */
int main(int argc, char **argv)
{
  // Se realiza un ciclo infinito mientras status determine que el usuario no desea salir .
  char *line;
  int status;

  do {
    printf(">. ");
    line = readlinesh();
    status = startsh(line);
  } while (status);

  return 1;
}

