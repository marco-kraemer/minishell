/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:02:04 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_outfile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while(line[i] != '>' && line[i])
		i++;
	if ((int)ft_strlen(line) == i)
		return (NULL);
	i++;
	if (line[i] == '>')
		i++;
	while (line[i] == ' ')
		i++;
	ret = ft_substr(line, i, ft_strlen(line) - i);
	return (ret);
}

int	check_rule(char *line)
{
	int	i;
	int	ret;
	int	check1;
	int	check2;

	i = 0;
	ret = 0;
	check1 = 0;
	check2 = 0;
	while (line[i])
	{
		if (line[i] == '>' && check1 == 0)
		{
			ret += 1;
			check1++;
			if (line[i + 1] == '>')
				ret += 6;
		}
		if (line[i] == '<' && check2 == 0)
		{
			ret += 4;
			check2++;
			if (line[i + 1] == '<')
				ret += 6;
		}
		i++;
	}
	return (ret);
}

char	*readinput()
{
	char	*line;
	int		i;

	i = 0;
	line = readline(PROMPT_MSG);
	if (!line)
	{
		printf("exit\n");
		exit (0);
	}
	if (ft_strlen(line) != 0)
		add_history(line);
	return (line);
}
