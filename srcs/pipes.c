/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/07/23 11:40:32 by cbertola         ###   ########.fr       */
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

void  wait_pipes(int nb_cmd, pid_t *pid, int *ret)
{
  int i;

  i = -1;
  while (++i < nb_cmd)
    waitpid(pid[i], ret, 0);
}

void do_dup(int j, int nb_cmd, int *pipes, t_pipes *pipe)
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
  if (j < nb_cmd - 1 || pipe->redir_out.simpl != NULL || pipe->redir_out.doubl != NULL)
  {
    while (pipe->redir_out.simpl != NULL)
    {
        pipes[j * 2 + 1] = open(pipe->redir_out.simpl->str, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
         pipe->redir_out.simpl = pipe->redir_out.simpl->next;
    }
    while (pipe->redir_out.doubl != NULL)
    {
        pipes[j * 2 + 1] = open(pipe->redir_out.doubl->str, O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
         pipe->redir_out.doubl = pipe->redir_out.doubl->next;
    }
  }
  dup2(pipes[j * 2 + 1], 1);
}

void do_pipe(t_semicol *semicol, int *ret)
{
  pid_t   pid[semicol->nb_cmd + 1];
  int     pipes[semicol->nb_cmd * 2];
  int     j = -1;
  // int     status;

  
  init_pipes(semicol->nb_cmd * 2, pipes);
  while (semicol->pipes != NULL)
  {
    if (!(pid[++j] = fork()))
    {
      do_dup(j, semicol->nb_cmd, pipes, semicol->pipes);
      close_pipes(semicol->nb_cmd * 2, pipes);
      // if (!(*ret = find_fcts(semicole->pipes)))
        if ((*ret = execvp(*semicol->all[j], semicol->all[j])))
          exit(-1);
    }
    semicol->pipes = semicol->pipes->next;
  }
  close_pipes(semicol->nb_cmd * 2, pipes);
  wait_pipes(semicol->nb_cmd * 2, pid, ret);
}

int     test(t_semicol *semicol)
{
  int ret;

  do_pipe(semicol, &ret);
  return (0);
}
