/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/06 10:39:01 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void  wait_pipes(int nb_pipes, pid_t *pid, int *ret)
{
  int i;

  i = -1;
  while (++i < nb_pipes)
    waitpid(pid[i], ret, 0);
}

void        redir_out(t_redir *redir, int param, int *pipes, int j)
{
  t_redir   *first_redir;

  first_redir = redir;
  while (redir != NULL)
  {
      pipes[j * 2 + 1] = open(redir->str, param, S_IRUSR | S_IWUSR);
      redir = redir->next;
  }
  redir = first_redir;
}
void        do_dup(int j, int nb_pipes, int *pipes, t_pipes *pipe)
{
  int i;
  int fd;

  i = -1;
  if (j > 0)
    dup2(pipes[j * 2 - 2], 0);
  while(pipe->redir_in.simpl != NULL)
  {
    if ((fd = open(pipe->redir_in.simpl->str, O_RDONLY)) < 0)
      return ;
    dup2(fd, 0);
    pipe->redir_in.simpl = pipe->redir_in.simpl->next;
  }
  i = -1;
  if (j < nb_pipes - 1 && (pipe->redir_out.simpl != NULL || pipe->redir_out.doubl != NULL))
  {
    redir_out(pipe->redir_out.simpl, 1102, pipes, j);
    redir_out(pipe->redir_out.doubl, 2102, pipes, j);
  }
  printf("here we test do dup -> %d\n", j);
  dup2(pipes[j * 2 + 1], 1);
  printf("We are here do_dup\n");
}

void do_pipe(t_semicol *semicol, int *ret, t_env *env)
{
  pid_t       pid[semicol->nb_pipes + 1];
  int         pipes[semicol->nb_pipes * 2 + 1];
  int         j = -1;
  t_pipes   *first_pipes;
  
  printf("here we test do pipe nb pipes -> %d\n", semicol->nb_pipes);
  init_pipes(semicol->nb_pipes * 2, pipes);
  first_pipes = semicol->pipes;
  printf("We are here do_pipe\n");
  while (semicol->pipes != NULL)
  {
    if (!(pid[++j] = fork()))
    {
      do_dup(j, semicol->nb_pipes, pipes, semicol->pipes);
      printf("We are here do_pipe if\n");
      close_pipes(semicol->nb_pipes * 2, pipes);
      if ((*ret = find_fcts(&semicol->pipes->cmds, env)) == -1)
        if ((*ret = execvp(*semicol->all[j], semicol->all[j])))
          exit(*ret);
    }
    semicol->pipes = semicol->pipes->next;
  }
  semicol->pipes = first_pipes;
  close_pipes(semicol->nb_pipes * 2, pipes);
  wait_pipes(semicol->nb_pipes * 2, pid, ret);
}

int     exec_cmds(t_semicol *semicol, t_env *env)
{
  int         ret;
  t_semicol   *first_semicol;

  first_semicol = semicol;
  while (semicol != NULL)
  {
    do_pipe(semicol, &ret, env);
    semicol = semicol->next;
  }
  semicol = first_semicol;
  return (0);
}
