#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

void  init_pipes(int nb_pipes, int *pipes)
{
  int i;
  int j;

  i = -1;
  j = 0;
  while (++i < nb_pipes)
  {
    pipe(pipes + j);
    j += 2;
  }
}

void  close_pipes(int nb_pipes, int *pipes)
{
  int i;

  i = -1;
  while (++i < nb_pipes)
    close(pipes[i]);
}

void  wait_pipes(int *status, int nb_cmd)
{
  int i;

  i = -1;
  while (++i < nb_cmd - 1)
    wait(status);
}

//V2 - functions
void do_dup(int j, int nb_cmd, int *pipes)
{
  if (j > 0)
    dup2(pipes[j * 2 - 2], 0);
  if (j < nb_cmd - 1)
    dup2(pipes[j * 2 + 1], 1);
}


//V2 - N CMDS
void do_pipe(char ***all, int nb_cmd)
{
  int     pipes[nb_cmd * 2];
  int     j = -1;
  int     status;

  init_pipes(nb_cmd * 2, pipes);
  while (++j < nb_cmd)
  {
    if (fork() == 0)
    {
      do_dup( j, nb_cmd, pipes);
      close_pipes(nb_cmd * 2, pipes);
      if (execvp(*all[j], all[j]))
        exit(-1);
    }
  }
  close_pipes(nb_cmd * 2, pipes);
  wait_pipes(&status, nb_cmd * 2);
}

int main(int argc, char **argv)
{
  int ret;


  // cat Makefile | grep pipe | cut -b 1-10 | cd bonjour
  char *test17[] = {"cat", "pipes.c", NULL};
  char *test18[] = {"grep", "grep", NULL};
  char *test19[] = {"cut", "-b", "1-10", NULL};
  char *test20[] = {"cut", "-b", "2-5", NULL};
  char **all5[4] = {test17, test18, test19, test20};
  //do_pipe(all5, &ret);
  do_pipe(all5, 4);
  return (0);
}