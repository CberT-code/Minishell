/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcts_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 10:58:27 by cbertola          #+#    #+#             */
/*   Updated: 2020/09/09 11:07:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_space_end(char *str, t_gbl *gbl)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		free_exit2(gbl, ERROR_SYNTAX);
}

void			tab_all(t_semi *semi)
{
	t_pipes		*first_pipe;
	int			j;

	j = -1;
	if (!(semi->all = ft_calloc(sizeof(char **), semi->nb_pipes + 1)))
		return ;
	first_pipe = semi->pipes;
	while (semi->pipes)
	{
		if (semi->pipes->cmds.str != NULL)
			semi->all[++j] = new_tab(semi->pipes);
		semi->pipes = semi->pipes->next;
	}
	semi->pipes = first_pipe;
}

void		suppr_maillon(t_env **list, t_env *ptr)
{
	t_env	*start;

	start = *list;
	if (*list == NULL)
	{
		*list = ptr->next;
		return ;
	}
	while (*list != NULL)
	{
		if ((*list)->next == ptr)
		{
			(*list)->next = ptr->next;
			ft_strdel(&ptr->var);
			ft_strdel(&ptr->valeur);
			free(ptr);
			*list = start;
			return ;
		}
		*list = (*list)->next;
	}
	*list = start;
}

void	ft_free_env(t_env *env)
{
	t_env	*b_last;
	int		i;

	i = 0;
	while (env)
	{
		free(env->var);
		free(env->valeur);
		b_last = env;
		i++;
		env = env->next;
		free(b_last);
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}
