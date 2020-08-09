/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbertola <cbertola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 21:49:40 by cbertola          #+#    #+#             */
/*   Updated: 2020/08/09 11:43:56 by cbertola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    condition_do_pipe(t_semicol *semicol, char *str)
{
  t_tab_redir   *redir_in;
  t_tab_redir   *redir_out;

  redir_in = &semicol->pipes->redir_in;
  redir_out = &semicol->pipes->redir_out;
  if (semicol->nb_pipes == 1 && semicol->pipes->redir_in.simpl == NULL &&
  semicol->pipes->redir_in.doubl == NULL && semicol->pipes->redir_out.simpl == NULL &&
  semicol->pipes->redir_out.doubl == NULL && search_mybin(str))
    return (1);
  return (0);
}

void     exec_fork(t_semicol *semicol, int j, t_env **env, int *pipes)
{
    char      *path;
    int       ret;
    
    ret = 0;
    do_dup(j, semicol->nb_pipes, pipes, semicol->pipes);
    close_pipes(semicol->nb_pipes * 2, pipes);
    if ((ret = find_fcts(&semicol->pipes->cmds, env)) != -1)
      exit(ret);
    else
    {
      
      if ((path = check_path(semicol->pipes->cmds.str ,*env)) != NULL)
      {
        if ((ret = execvp(path, semicol->all[j])))
        {
          free(path);
          exit(ret);
        }
      }
      else 
        ft_printf(ERROR_FIND_CMD, semicol->pipes->cmds.str);
      free(path);
    } 
}

void     do_pipe(t_semicol *semicol, int *ret, t_env **env)
{
  int        pipes[semicol->nb_pipes * 2 + 1];
  int        j = -1;
  t_pipes    *first_pipes;
  pid_t      pid[semicol->nb_pipes + 1];

  init_pipes(semicol->nb_pipes * 2, pipes);
  first_pipes = semicol->pipes;
  while (++j < semicol->nb_pipes)
  {
    if (condition_do_pipe(semicol, semicol->pipes->cmds.str))
    {
      printf("Ici on utilise notre fonction\n");
      find_fcts(&semicol->pipes->cmds, env);
    }
    else
    {
      printf("Ici on utilise la fonction du bash\n");
      if (!(pid[j] = fork()))
        exec_fork(semicol, j, env, pipes);
      waitpid(pid[j], ret, 0);
    }
    semicol->pipes = semicol->pipes->next;
  }
  semicol->pipes = first_pipes;
  close_pipes(semicol->nb_pipes * 2, pipes);
  wait_pipes(semicol->nb_pipes * 2, pid, ret);
}

int     exec_cmds(t_semicol *semicol, t_env **env)
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
