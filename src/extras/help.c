/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 23:37:15 by jdanelon          #+#    #+#             */
/*   Updated: 2021/09/30 20:45:21 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

	i = -1;
	ret = -1;
	if (file)
	{
		while (file[++i])
		{
			tmp = ft_strjoin(file[i], "/");
			tmp = ft_strjoin_free(tmp, shell->splited[0]);
			ret = execve(tmp, shell->splited, envp);
			free(tmp);
			if (ret == 0)
				break ;
		}
	}
	if (ret >= 0)
		return (ret);
	ret = 1;
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