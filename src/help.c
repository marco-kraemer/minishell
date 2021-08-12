/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:35:21 by maraurel          #+#    #+#             */
/*   Updated: 2021/08/12 09:43:42 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_infile(char *line)
{
	char	*ret;
	int		i;

	i = 0;
	while (line[i] != '<' && line[i])
		i++;
	if ((int)ft_strlen(line) == i)
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
				rule.ret += 8;
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

char	*ft_remove(char **envp)
{
	pid_t	pid;
	char	**args;

	if (envp[0][0] == 'a')
		printf("oi\n");
	args = ft_split("rm ../tmp", ' ');
	pid = fork();
	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return (NULL);
	}
	else if (pid == 0)
	{
		if (execve("/bin/rm", args, NULL) < 0)
			printf("rm: No such file or directory\n");
		exit(0);
	}
	else
	{
		wait(NULL);
		return (NULL);
	}
	return (NULL);
}
