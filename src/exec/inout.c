/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 20:18:16 by maraurel         ###   ########.fr       */
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

char	*get_in_out_file(char **args, char *type1, char *type2, int rule)
{
	char	*filename;
	int		i;

	i = 0;
	filename = NULL;
	while (args[i])
	{
		if (ft_strcmp(args[i], type1) == 0 || ft_strcmp(args[i], type2) == 0)
		{
			i++;
			if (filename != NULL)
				free(filename);
			if (!(args[i]))
			{
				printf("minishell: syntax error\n");
				return (NULL);
			}
			filename = ft_strdup(args[i]);
			if (rule == 0)
				open(filename, O_WRONLY | O_APPEND | O_CREAT, 0777);
		}
		i++;
	}
	return (filename);
}

int	redirections_rules(char *arg, t_shell *shell)
{
	if (ft_strcmp(arg, ">") == 0)
		shell->outfile_rule = 1;
	else if (ft_strcmp(arg, ">>") == 0)
		shell->outfile_rule = 2;
	else if (ft_strcmp(arg, "<") == 0)
		shell->infile_rule = 1;
	else if (ft_strcmp(arg, "<<") == 0)
		shell->infile_rule = 2;
	else
		return (1);
	return (0);
}

char	**remove_redirections(char **args, t_shell *shell)
{
	int		i;
	int		size;
	char	**ret;

	size = 0;
	while (args[size])
		size++;
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	i = 0;
	size = 0;
	while (args[i])
	{
		if (redirections_rules(args[i], shell) == 0)
			i += 2;
		else
		{
			ret[size] = ft_strdup(args[i]);
			i++;
			size++;
		}
	}
	ret[size] = 0;
	ft_free_double(args);
	return (ret);
}

char	**get_in_and_out_file(t_shell *shell, char **args)
{
	shell->infile_rule = 0;
	shell->outfile_rule = 0;
	shell->outfile = get_in_out_file(args, ">", ">>", 0);
	shell->infile = get_in_out_file(args, "<", "<<", 1);
	return (remove_redirections(args, shell));
}
