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

  i = 0;
  while (i < nb_pipes)
  {
    pipe(pipes + i);
    i += 2;
  }
}

void  close_pipes(int nb_pipes, int *pipes)
{
  while (nb_pipes--)
    close(pipes[nb_pipes]);
}

void  wait_pipes(int nb_cmd, pid_t *pid, int *ret)
{
  int i;

  i = 0;
  while (i < nb_cmd)
  {
    waitpid(pid[i], ret, 0);
    i++;
  }
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
void do_pipe(char ***all, int nb_cmd, int *ret)
{
  pid_t *pid;
  int   pipes[nb_cmd * 2 - 2];
  int   j = -1;

  if (!(pid = (pid_t *)malloc(sizeof(int) * nb_cmd + 1)))
    return ;
  init_pipes(nb_cmd * 2 - 2, pipes);
  while (j < nb_cmd)
  {
    j += 1;
    if (!(pid[j] = fork()))
    {
      do_dup( j, nb_cmd, pipes);
      close_pipes(nb_cmd * 2 - 2, pipes);
      *ret = execvp(*all[j], all[j]);
    }
  }
  close_pipes(nb_cmd * 2 - 2, pipes);
  wait_pipes(nb_cmd, pid, ret);
  free(pid);
}

int main(int argc, char **argv)
{
  int ret;


  // cat Makefile | grep pipe | cut -b 1-10 | cd bonjour
  char *test17[] = {"cat", "pipe.c", NULL};
  char *test18[] = {"grep", "grep", NULL};
  char *test19[] = {"cut", "-b", "1-10", NULL};
  char *test20[] = {"cd", "bonjour", NULL};
  char **all5[4] = {test17, test18, test19, test20};
  //do_pipe(all5, &ret);
  do_pipe(all5, 4, &ret);
  printf("NO FILE : %d\tEXPECTED : 1\n\n", ret);
  return (0);
}