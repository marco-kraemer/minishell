/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/20 22:43:11 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	treat_quotes(char *line, int i)
{
	if (line[i] == '\"')
	{
		i++;
		while (line[i] != '\"' && line[i])
			i++;
		return (i + 1);
	}
	if (line[i] == '\'')
	{
		i++;
		while (line[i] != '\'' && line[i])
			i++;
		return (i + 1);
	}
	i++;
	return (i);
}

char	*get_infile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while (line[i] != '<' && line[i])
		i = treat_quotes(line, i);
	if ((int)ft_strlen(line) <= i)
		return (NULL);
	i++;
	if (line[i] == '<')
		i++;
	while (line[i] == ' ')
		i++;
	ret = ft_substr(line, i, ft_strlen(line) - i);
	i = 0;
	while (ret[i] && ret[i] != ' ')
		i++;
	ret[i] = '\0';
	return (ret);
}

char	*get_outfile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while (line[i] != '>' && line[i])
		i = treat_quotes(line, i);
	if ((int)ft_strlen(line) <= i)
		return (NULL);
	i++;
	if (line[i] == '>')
		i++;
	while (line[i] == ' ')
		i++;
	ret = ft_substr(line, i, ft_strlen(line) - i);
	return (ret);
}
