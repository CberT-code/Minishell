#include "minishell.h"

void  init_pipes(int nb_pipes, int *pipes)
{
  int i;

  i = -1;
  while (++i < nb_pipes)
    pipe(pipes +  (2 * i));
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

void do_dup(int j, int nb_cmd, int *pipes, char **redird, char **redirg, int typeredir)
{
  int i;
  int fd;

  i = 0;
  if (j > 0)
    dup2(pipes[j * 2 - 2], 0);
  while(redirg[i])
  {
    if ((fd = open(redirg[i++], O_RDONLY)) < 0)
      return ;
    dup2(fd, 0);
  }
  i = 0;
  if (j < nb_cmd - 1 || redird[i] != NULL)
  {
    while (redird[i])
    {
      if (typeredir== 1 && redird[i] != NULL)
        pipes[j * 2 + 1] = open(redird[i], O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
      else if (typeredir== 2 && redird[i] != NULL)
        pipes[j * 2 + 1] = open(redird[i], O_RDONLY | O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
      i++;
    }
    dup2(pipes[j * 2 + 1], 1);
  }
}


void do_pipe(char **cmd, char ***redird, char ***redirg, int nb_cmd, int *ret)
{
  pid_t   pid[nb_cmd + 1];
  int     pipes[nb_cmd * 2];
  int     j;
  char    **all;

  j = -1; 
  init_pipes(nb_cmd * 2, pipes);
  while (++j < nb_cmd)
  {
    if (!(pid[j] = fork()))
    {
      all = ft_split(cmd[j], ' ');
      do_dup( j, nb_cmd, pipes, redird[j], redirg[j], 1);
      close_pipes(nb_cmd * 2, pipes);
      if (execvp(*all, all))
        exit(-1);
    }
  }
  close_pipes(nb_cmd * 2, pipes);
  wait_pipes(nb_cmd, pid, ret);
}

int main(int argc, char **argv)
{
  int ret;

  char *cmd1 = "echo test";
  char *cmd2 = "grep test";


  char *redird1[] = {"cat.txt", NULL};
  char *redird2[] = {"grep.txt", NULL};



  char *redirg1[] = {NULL};
  char *redirg2[] = {"cat.txt", NULL};


  char *cmds[] = {cmd1, cmd2};
  char **redird[] = {redird1, redird2};
  char **redirg[] = {redirg1, redirg2};

  do_pipe(cmds, redird, redirg, 2, &ret);
  printf("\n\nRET = %d\n", ret);
  return (0);
}