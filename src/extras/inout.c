/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 10:01:35 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	treat_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
		if (line[i] != '\0')
			i++;
		return (i + 0);
	}
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		if (line[i] != '\0')
			i++;
		return (i);
	}
	i++;
	return (i);
}

char	*get_file_name(char *line, int *start, int *i)
{
	while (line[*i] && line[*i] == ' ')
		*i += 1;
	*start = *i;
	while (line[*i] != ' ' && line[*i] != '<' && line[*i] && line[*i] != '>')
		*i = treat_quotes(line, *i);
	return (ft_substr(line, *start, *i - *start));
}

char	*get_in_out_file(char *line, char c)
{
	char	*filename;
	int		i;
	int		start;

	i = 0;
	filename = NULL;
	while (line[i])
	{
		if (line[i] == c)
		{
			i++;
			if (line[i] == c)
				i++;
			if (filename != NULL)
				free(filename);
			filename = get_file_name(line, &start, &i);
		}
		else
			i = treat_quotes(line, i);
	}
	return (filename);
}

void	get_in_and_out_file(t_shell *shell, char *line)
{
	shell->outfile = get_in_out_file(line, '>');
	shell->infile = get_in_out_file(line, '<');
}
