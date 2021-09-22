/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 23:37:15 by jdanelon          #+#    #+#             */
/*   Updated: 2021/09/21 22:37:46 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		rule.i = treat_quotes(line, rule.i);
	}
	return (rule.ret);
}

char	*ft_exec_rm(char **args)
{
	pid_t	pid;

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

char	*ft_remove(void)
{
	char	**args;

	args = ft_split("rm ../tmp", ' ');
	ft_exec_rm(args);
	ft_free_double(args);
	return (NULL);
}

int	iterate_over_path(t_shell *shell, char **envp, char **file, char *msg)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	while (file[i])
	{
		tmp = ft_strjoin(file[i], "/");
		tmp = ft_strjoin(tmp, shell->splited[0]);
		ret = execve(tmp, shell->splited, envp);
		free(tmp);
		if (ret == 0)
			break ;
		i++;
	}
	if (ret < 0)
		printf("%s: %s\n", shell->splited[0], msg);
	return (ret);
}

int	contains_slash(char *str, int *ret)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	*ret = -1;
	return (0);
}
