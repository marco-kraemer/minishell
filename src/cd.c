/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/28 00:41:47 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*join_new_argument(char *first_part, char *second_part)
{
	int		i;
	int		j;
	char	*home;
	char	*new_arg;

	i = -1;
	j = -1;
	home = getenv("HOME");
	new_arg = (char *)malloc(ft_strlen(first_part) + ft_strlen(home)
			+ ft_strlen(second_part) + 1);
	while (first_part[++i])
		new_arg[i] = first_part[i];
	while (home[++j])
		new_arg[i + j] = home[j];
	i = i + j;
	j = -1;
	while (second_part[++j])
		new_arg[i + j] = second_part[j];
	new_arg[i + j] = '\0';
	free(first_part);
	free(second_part);
	return (new_arg);
}

static	char	*handle_tilde(char **args)
{
	int		i;
	char	*first_part;
	char	*second_part;
	char	*new_arg;

	i = 0;
	new_arg = ft_strdup(args[1]);
	while (args[1][i])
	{
		if (args[1][i] == '~')
			break ;
		i++;
	}
	if (i != (int)ft_strlen(args[1]))
	{
		first_part = ft_substr(args[1], 0, i);
		second_part = ft_substr(args[1], i + 1, ft_strlen(args[1]) - i - 1);
		free(new_arg);
		new_arg = join_new_argument(first_part, second_part);
	}
	return (new_arg);
}

static	int	num_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

char	*change_directory(char **args)
{
	char	*new_arg;

	if (args[1] == NULL)
		chdir(getenv("HOME"));
	else
	{
		if (num_args(args) > 2)
		{
			printf("shell: cd: Too many arguments\n");
			return (NULL);
		}
		new_arg = handle_tilde(args);
		if (chdir(new_arg) != 0)
		{
			g_status = 1;
			printf("shell: cd: %s: No such file or directory\n", args[1]);
		}
		free(new_arg);
	}
	return (NULL);
}
