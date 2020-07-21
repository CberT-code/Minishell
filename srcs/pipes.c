#include "../minishell.h"

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

void do_dup(int j, int nb_cmd, int *pipes, t_tab_redir redir)
{
  int i;
  int fd;

//redir == quotes simple ou double

  i = -1;
  if (j > 0)
    dup2(pipes[j * 2 - 2], 0);
  while(redir.simple_in != NULL)
  {
    if ((fd = open(redir.simple_in->str, O_RDONLY)) < 0)
      return ;
    dup2(fd, 0);
    redir.simple_in = redir.simple_in->next;
  }
  i = -1;
  if (j < nb_cmd - 1 || redir.simple_out != NULL && redir.double_out != NULL)
  {
    while (redir.simple_out != NULL)
    {
        pipes[j * 2 + 1] = open(redir.simple_out->str, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
         redir.simple_out = redir.simple_out->next;
    }
    while (redir.double_out != NULL)
    {
        pipes[j * 2 + 1] = open(redir.double_out->str, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
         redir.double_out = redir.double_out->next;
    }
  }
  dup2(pipes[j * 2 + 1], 1);
}



void do_pipe(t_semicol *semicol, int *ret, t_tab_redir redir)
{
  pid_t   pid[nb_cmd + 1];
  int     pipes[nb_cmd * 2];
  int     j = -1;
  int     status;

  init_pipes(semicol->nb_cmd * 2, pipes);
  while (++j < semicol->nb_cmd)
  {
    if (!(pid[j] = fork()))
    {
      do_dup(j, semicol->nb_cmd, pipes, redir);
      close_pipes(semicol->nb_cmd * 2, pipes);
      if ((*ret = execvp(*all[j], all[j])))
        exit(-1);
    }
  }
  close_pipes(semicol->nb_cmd * 2, pipes);
  wait_pipes(semicol->nb_cmd * 2, pid, ret);
}

// int main(int argc, char **argv)
// {
//   int ret;

//   char *test17[] = {"echo", "test", NULL};
//   char *test18[] = {"grep", "test", NULL};
//   char **all5[2] = {test17, test18};



//   char *redir1[] = {"cat.txt", NULL};
//   char *redir2[] = {"grep.txt", NULL};
//   char **redir_extern[2] = {redir1, redir2};



//   char *redir5[] = {NULL};
//   char *redir6[] = {"cat.txt", NULL};
//   char **redir_intern[2] = {redir5, redir6};


//   do_pipe(all5, 2, &ret, redir_extern, redir_intern);
//   printf("\n\nRET = %d\n", ret);
//   return (0);
// }
