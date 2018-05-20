#include <fcntl.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.c"


int commandsinline=0;

/*
  Function Declarations for builtin shell commands:
 */
void cdcommand(char *args);
void helpcommand();
int exitcommand();
void redir(char* args);

/*
  List of builtin commands, followed by their corresponding functions.
 */
char* commands[]= {
  "cd",
  "help",
  "QUIT",
  "REDIR",
  "BG"
};

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
void cdcommand(char *args)
{
  if (args == NULL) {
    fprintf(stderr, "Escriba el directorio después de cd\n");
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
int startsh(char *line)
{
  pid_t pid, wpid;
  int status;
  bool m=false;

    m=false;
    char* complete= malloc(strlen(line)*sizeof(char));
    strcpy(complete,line);

    char* command = strsep(&line, " ");

    char* path = malloc(strlen(command)+1+5);
    
    strcpy(path, "/bin/");
    strcat(path, command);

    //Si el comando ingresado es cd
    if(!strcmp(command ,commands[0]) && !m){    
      cdcommand(line);
      m=true;
    }
    //Si el comando ingresado es help
    if(!strcmp(command,commands[1]) && !m){
      helpcommand();
      printf("Ayudando\n");
      m=true;
    }
    //Si el comando ingresado es exit
    if(!strcmp(command,commands[2]) && !m){
      return 0;
    }

    //Si el comando ingresado es REDIR
    if(!strcmp(command,commands[3]) && !m){
      redir(line);
    }

    //Si el comando ingresado es BG
    if(!strcmp(command,commands[4]) && !m){
      
    }    

    pid=fork();

    if(pid==0){
      char *execArgs[] = { command, line, NULL };
      execvp(command, execArgs);
      m=true;
      exit(0);
    }
    else{     
        while ((wpid = wait(&status)) > 0);
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

#define ROWS 100
char** trimcommands(char* cline){
  char **commands;
  commands = (char **)malloc (ROWS*sizeof(char *));
  char* line;

  bool finalcommand=false;
  int cont=0;

  while(!finalcommand){

    commandsinline++;
    switch(whatsfirst(cline)){
        case 1:{
          line=strsep(&cline,"&");
          strsep(&cline,"&");
          strsep(&cline," ");
          break;
        }
        case 2:{
          line=strsep(&cline,"||");
          strsep(&cline,"|");
          strsep(&cline," ");
          break;
        }
        case 3:{
          line=strsep(&cline,"&");
          strsep(&cline," ");
          break;
        }
        default:{
          line=cline;
          finalcommand=true;
          break;
        }
    }
    startsh(line);
    cont++;
  }
}
 
void redir(char* line){
    char* cline = malloc((strlen(line)+1)*sizeof(char));
    strcpy(cline, line);
    
    line=trimfile(line);

    if(whatsfirsttwo(cline) == 1 ){
    }
    else{
      char* command=strsep(&cline,"OUTPUTF");
      char* copycommand = malloc((strlen(command)+1)*sizeof(char));
      strcpy(copycommand, command);
      strsep(&copycommand," ");
      command=strsep(&command," ");
      copycommand=strsep(&copycommand," ");
      int fd = open(line, O_WRONLY|O_CREAT, 0666);        
      dup2(fd, STDOUT_FILENO);
      close(fd);
      char *execArgs[] = { command, copycommand, NULL };
      execvp(command,execArgs);
      dup2(STDOUT_FILENO, fd);
    }


  /*
    int fd[2];
    pid_t childpid;
    pipe(fd);
    if ((childpid = fork()) == 0) {  ls es el hijo 
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(command, execArgs);
        execl("/bin/ls", "ls", "-l", NULL);
        perror("Exec failed");
    }
    else {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execl("/usr/bin/sort", "sort", "-n", "--key=5", NULL);
        perror("...");
    }
 */
}

/**
   @return status code
 */
int main(int argc, char **argv)
{
  // Se realiza un ciclo infinito mientras status determine que el usuario no desea salir .
  char *line;
  int status;
  char** commands;

  do {
    commandsinline=0;
    printf("> ");
    line = readlinesh();
    trimcommands(line);

  } while (status);

  return 1;
}

