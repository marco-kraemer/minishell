/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maraurel <maraurel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 09:23:20 by maraurel          #+#    #+#             */
/*   Updated: 2021/09/29 13:41:55 by maraurel         ###   ########.fr       */
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
	int		start;

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
				open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		}
		i++;
	}
	return (filename);
}

char	**remove_redirections(char **args)
{
	int	i;
	int	size;
	char	**ret;

	i = 0;
	size = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<<") == 0 || ft_strcmp(args[i], "<") == 0)
			size -= 2;
		size++;
		i++;
	}
	
	ret = (char **)malloc(sizeof(char *) * size);
		
	i = 0;
	size = 0;
	while (args[i])
	{
	
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0
			|| ft_strcmp(args[i], "<<") == 0 || ft_strcmp(args[i], "<") == 0)
			i += 2;
	//	if (args[i])
	//		break;
		printf("aaa\n");
		ret[size] = ft_strdup(args[i]);
		i++;
		size++;
	}
	ret[i] = 0;
	ft_free_double(args);

	for (int i=0; ret[i]; i++)
		printf("%s\n", ret[i]);

	return (ret);
}

char	**get_in_and_out_file(t_shell *shell, char **args)
{
	shell->outfile = get_in_out_file(args, ">", ">>", 0);
	shell->infile = get_in_out_file(args, "<", "<<", 1);
	return (remove_redirections(args));
}
