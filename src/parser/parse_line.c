/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 10:32:35 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/30 10:39:03 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_extras_spaces(char *line)
{
	int	i;
	int	extra;

	i = 0;
	extra = 0;
	while (line[i])
	{
		if (line[i] == '>')
		{
			extra += 2;
			i++;
			while (line[i] == '>')
				i++;
		}
		if (line[i] == '<')
		{
			extra += 2;
			i++;
			while (line[i] == '<')
				i++;
		}
		else
			i = treat_quotes(line, i);
	}
	return (extra);
}

void	do_somethns(char *line, t_correct_args *helper)
{
	char	c;

	c = line[helper->i];
	if (c == '\"' || c == '\'')
	{
		helper->new[helper->j++] = line[helper->i++];
		while (line[helper->i] && line[helper->i] != c)
			helper->new[helper->j++] = line[helper->i++];
		if (line[helper->i] == c)
			helper->new[helper->j++] = line[helper->i++];
	}
	else if (c == '>' || c == '<')
	{
		helper->new[helper->j] = ' ';
		helper->j += 1;
		while (line[helper->i] == c)
		{
			helper->new[helper->j] = line[helper->i];
			helper->i += 1;
			helper->j += 1;
		}
		helper->new[helper->j] = ' ';
		helper->j += 1;
	}
	c = 0;
}

char	*parse_line(char *line)
{
	t_correct_args	helper;
	char			c;

	helper.new = (char *) malloc(sizeof(char)
			* (ft_strlen(line) + count_extras_spaces(line)) + 1);
	helper.j = 0;
	helper.i = 0;
	c = 0;
	while (line[helper.i])
	{
		if (line[helper.i] == '\"' || line[helper.i] == '\''
			|| line[helper.i] == '<' || line[helper.i] == '>')
			do_somethns(line, &helper);
		else
		{
			helper.new[helper.j] = line[helper.i];
			helper.i++;
			helper.j++;
		}
	}
	helper.new[helper.j] = '\0';
	free(line);
	return (helper.new);
}
