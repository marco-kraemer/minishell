/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by maraurel          #+#    #+#             */
/*   Updated: 2021/07/06 12:18:42 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_outfile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while (line[i] != '>' && line[i])
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
	t_rule	rule;

	rule.i = 0;
	rule.ret = 0;
	rule.check1 = 0;
	rule.check2 = 0;
	while (line[rule.i])
	{
		if (line[rule.i] == '>' && rule.check1 == 0)
		{
			rule.ret += 1;
			rule.check1++;
			if (line[rule.i + 1] == '>')
				rule.ret += 6;
		}
		if (line[rule.i] == '<' && rule.check2 == 0)
		{
			rule.ret += 4;
			rule.check2++;
			if (line[rule.i + 1] == '<')
				rule.ret += 6;
		}
		rule.i++;
	}
	return (rule.ret);
}

char	*readinput(void)
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
