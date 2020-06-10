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

void  wait_pipes(int nb_cmd, pid_t *pid, int *ret)
{
  int i;

  i = -1;
  while (++i < nb_cmd)
    waitpid(pid[i], ret, 0);
}

void do_dup(int j, int nb_cmd, int *pipes, int redir, char *redir_extern, char *redir_intern)
{

  if (j > 0)
    dup2(pipes[j * 2 - 2], 0);
  if (j < nb_cmd - 1 || redir_extern != NULL)
  {
    if (redir == 1 && redir_extern != NULL)
      pipes[j * 2 + 1] = open(redir_extern, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    if (redir == 2 && redir_extern != NULL)
      pipes[j * 2 + 1] = open(redir_extern, O_RDONLY |O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(pipes[j * 2 + 1], 1);
  }
  if (redir_intern != NULL)
      dup2(open(redir_intern, O_RDONLY), 0);
}

void do_pipe(char ***all, int nb_cmd, int *ret, char **redir_extern, char **redir_intern)
{
  pid_t   pid[nb_cmd + 1];
  int     pipes[nb_cmd * 2];
  int     j = -1;
  int     status;

  init_pipes(nb_cmd * 2, pipes);
  while (++j < nb_cmd)
  {
    if (!(pid[j] = fork()))
    {
      do_dup( j, nb_cmd, pipes, 3, redir_extern[j], redir_intern[j]);
      close_pipes(nb_cmd * 2, pipes);
      if ((*ret = execvp(*all[j], all[j])))
        exit(-1);
    }
  }
  close_pipes(nb_cmd * 2, pipes);
  wait_pipes(nb_cmd * 2, pid, ret);
}

int main(int argc, char **argv)
{
  int ret;

  char *test17[] = {"head", "-n", "5", NULL};
  char *test18[] = {"grep", "d", NULL};
  char *test19[] = {"cut", "-b", "1-10", NULL};
  char *test20[] = {"cut", "-b", "2-5", NULL};
  char **all5[4] = {test17, test18, test19, test20};
  char *redir_extern[] = {NULL, NULL, NULL, NULL};
  char *redir_intern[] = {"test.c", NULL, NULL, NULL};
  do_pipe(all5, 4, &ret, redir_extern, redir_intern);
  printf("\n\nRET = %d\n", ret);
  return (0);
}