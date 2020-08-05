/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/05 18:57:45 by cbertola         ###   ########.fr       */
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
  if (j < nb_pipes - 1 || pipe->redir_out.simpl != NULL || pipe->redir_out.doubl != NULL)
  {
    redir_out(pipe->redir_out.simpl, 1102, pipes, j);
    redir_out(pipe->redir_out.doubl, 2102, pipes, j);
  }
  dup2(pipes[j * 2 + 1], 1);
}

void do_pipe(t_semicol *semicol, int *ret)
{
  pid_t       pid[semicol->nb_pipes + 1];
  int         pipes[semicol->nb_pipes * 2];
  int         j = -1;
  t_pipes   *first_pipes;
  
  init_pipes(semicol->nb_pipes * 2, pipes);
  first_pipes = semicol->pipes;
  while (semicol->pipes != NULL)
  {
    if (!(pid[++j] = fork()))
    {
      do_dup(j, semicol->nb_pipes, pipes, semicol->pipes);
      close_pipes(semicol->nb_pipes * 2, pipes);
      // if (!(*ret = find_fcts(semicole->pipes)))
        if ((*ret = execvp(*semicol->all[j], semicol->all[j])))
          exit(-1);
    }
    semicol->pipes = semicol->pipes->next;
  }
  semicol->pipes = first_pipes;
  close_pipes(semicol->nb_pipes * 2, pipes);
  wait_pipes(semicol->nb_pipes * 2, pid, ret);
}

int     exec_cmds(t_semicol *semicol)
{
  int       ret;
  t_semicol *first_semicol;

  first_semicol = semicol;
  while (semicol != NULL)
  {
    do_pipe(semicol, &ret);
    semicol = semicol->next;
  }
  semicol = first_semicol;
  return (0);
}
