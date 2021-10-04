/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdanelon <jdanelon@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:34:10 by maraurel          #+#    #+#             */
/*   Updated: 2021/10/01 18:17:12 by jdanelon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	char	*join_new_argument(char *first_part, char *second_part,
	char *home)
{
	int		i;
	int		j;
	char	*new_arg;

	i = -1;
	j = -1;
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

static	char	*select_which_home(char *home1, char *new_arg)
{
	char	*home2;

	free(new_arg);
	home2 = getenv("HOME");
	if (home1)
		return (home1);
	else if (home2)
		return (home2);
	else
		return (NULL);
}

static	char	*handle_tilde(char **args, char *home_space)
{
	int		i;
	char	*home;
	char	*first_part;
	char	*second_part;
	char	*new_arg;

	i = -1;
	new_arg = ft_strdup(args[1]);
	while (args[1][++i])
	{
		if (args[1][i] == '~')
			break ;
	}
	if (i != (int)ft_strlen(args[1]))
	{
		home = select_which_home(home_space, new_arg);
		if (!home)
			return (NULL);
		first_part = ft_substr(args[1], 0, i);
		second_part = ft_substr(args[1], i + 1, ft_strlen(args[1]) - i - 1);
		new_arg = join_new_argument(first_part, second_part, home);
	}
	if (home_space)
		free(home_space);
	return (new_arg);
}

static	char	*find_home_value(char **env)
{
	int		i;
	int		num_args;
	char	*home;

	i = 0;
	num_args = 0;
	while (env[num_args])
		num_args++;
	home = NULL;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "HOME=", 5))
			break ;
		i++;
	}
	if (i != num_args)
		home = ft_substr(env[i], 5, ft_strlen(env[i]));
	return (home);
}

char	*change_directory(char **args, char **env)
{
	char	*home;
	char	*new_arg;

	home = find_home_value(env);
	if (args[1] == NULL)
		cd_empty_argument(home);
	else
	{
		if (number_args(args) > 2)
		{
			g_status = 1;
			printf("shell: cd: Too many arguments\n");
			return (NULL);
		}
		new_arg = handle_tilde(args, home);
		if (new_arg == NULL)
			cd_empty_argument(new_arg);
		else if (chdir(new_arg) != 0)
		{
			g_status = 1;
			printf("shell: cd: %s: No such file or directory\n", args[1]);
		}
		free(new_arg);
	}
	return (NULL);
}
