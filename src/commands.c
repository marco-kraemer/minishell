/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/06/17 08:35:38 by maraurel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_directory(char **args)
{
	if (args[1] == NULL)
		chdir("");
	else
	{
		if (chdir(args[1]) != 0)
			printf("shell: No such file or directory\n");
	}
	return (NULL);
}

char	*echo(char **args)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 1;
	//   CHECK IF -n
	if (ft_strcmp(args[1], "-n") == 0)
		i++;
	k = 0;
	// GET LINE LEN TO ALLOCATE MEMORY
	while (args[i])
	{
		k += ft_strlen(args[i]);
		i++;
	}
	ret = malloc((sizeof(char) * k) + i);
	i = 1;
	// CHECK IF -n
	if (ft_strcmp(args[1], "-n") == 0)
		i++;
	k = 0;
	while (args[i])
	{
		j = 0;
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0)
			return (ret) ;
		while (args[i][j])
			ret[k++] = args[i][j++];
		ret[k++] = ' ';
		i++;
	}
	ret[k - 1] = '\0';
	ft_putstr_fd(ret, 1);
	if (ft_strcmp(args[1], "-n") != 0)
		printf("\n");
	return (ret);
}

char	*pwd()
{
	char	cwd[FILENAME_MAX];
	char	*ret;
	int	i;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("getcwd() error\n");
	ret = ft_strdup(cwd);	
	i = 0;
	ft_putstr_fd(ret, 1);
	write (1, "\n", 1);
	return (ret);
}

char	*env(char **args, char **env)
{
	int		i;
	int		j;
	int		k;
	int		size;
	char	*ret;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		printf("env: invalid number of arguments\n");
		return (NULL);
	}
	i = 0;
	size = 0;
	while (env[i + 1])
		size += ft_strlen(env[i++]);
	ret = malloc(sizeof(char) * size);
	i = 0;
	j = 0;
	while (env[i + 1])
	{
		k = 0;
		while (env[i][k])
			*(ret + j++) = env[i][k++];
		*(ret + j++) = '\n';
		i++;
	}
	*(ret + (j - 2)) = '\0';
	printf("%s\n", ret);
	return (ret);
}
