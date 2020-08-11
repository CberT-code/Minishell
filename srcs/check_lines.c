/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:01:15 by user42            #+#    #+#             */
/*   Updated: 2020/08/10 15:50:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_isulsign(char c)
{
	if ((c == '<' || c == '>'))
		return (1);
	return (0);
}

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f'
		|| c == '\r');
}

char	quote_inside(char *quote, char new, char prev)
{
	if (!*quote && prev != '\\' && (new == '\'' || new == '"'))
	{
		*quote = new;
		return (1);
	}
	else if ((new == '\'' || (new == '"' && prev != '\\')) && *quote == new)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

int		count_signs(char quote, char *line, int *i, int *s)
{
	while (!quote && (line[*i] == '<' || line[*i] == '>') && line[*i + 1])
	{
		(*s)++;
		(*i)++;
	}
	if (*s > 2)
	{
		ft_printf(SYNTHERRC, line[*i - 1]);
		free(line);
		return (1);
	}
	return (0);
}

int		ft_checkredir(char *line, int i, int *s, char prev)
{
	while (ft_isspace(line[i]) && line[i])
		i++;
	if ((line[i] == 0 || ft_isulsign(line[i])) && prev != '\\')
	{
		if (ft_isulsign(line[i]))
			ft_printf(SYNTHERRC, line[i]);
		else if (line[i] == 0)
			ft_printf(SYNTHERRS, "newline");
		free(line);
		return (1);
	}
	else
		*s = 0;
	return (0);
}

int		ft_checkpipe(char quote, char *line, int i, char prev)
{
	int j;

	j = i - 1;
	if (line[i] == '|' && !quote && prev != '\\')
	{
		while (j >= 0 && ft_isspace(line[j]))
			j--;
		if (j <= 0 || line[j] == ';' || line[j] == '|')
		{
			ft_printf(SYNTHERRC, '|');
			free(line);
			return (1);
		}
		j = i + 1;
		while (line[j] && ft_isspace(line[j]))
			j++;
		if (line[j] == ';')
		{
			ft_printf(SYNTHERRC, line[j]);
			free(line);
			return (1);
		}
	}
	return (0);
}

int		ft_checkparent(char quote, char *line, int i, char prev)
{
	if ((line[i] == '(' || line[i] == ')') && (!quote && prev != '\\'))
	{
		ft_printf(SYNTHERRC, line[i]);
		free(line);
		return (1);
	}
	return (0);
}

int		ft_checkline(char *line)
{
	int		i;
	int		s;
	char	prev;
	char	quote;

	i = 0;
	s = 0;
	prev = '\0';
	quote = '\0';
	while (line && line[i])
	{
		quote_inside(&quote, line[i], prev);
		if (count_signs(quote, line, &i, &s))
			return (0);
		else if (s > 0 && ft_checkredir(line, i, &s, prev))
			return (0);
		if (ft_checkpipe(quote, line, i, prev))
			return (0);
		if (ft_checkparent(quote, line, i, prev))
			return (0);
		prev = line[i];
		i++;
	}
	return (1);
}
